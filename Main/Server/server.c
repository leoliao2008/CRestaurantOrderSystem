#include "server.h"
#include "net_utils.h"
#include "response.h"
#include "request.h"
#include "customer.h"
#include "order.h"
#include "orders_node.h"
#include "cookqueue.h"
#include "db"

const char* FIFO_PIPE_NAME="FIFO_PIPE_NAME.p";
static int pfd=-1;
static const char* IP;
static const int PORT;
becustomer_t becust;
int client_sid;


void on_order_complete(int signum){
	char *buff[1024];
	if(SIG_USR1==signum){
		b_zero(buff,sizeof(buff));
		read(pfd,buff,sizeof(buff));
		printf("server is informed of finished order:");
		printf("%s\n",buff);
		//send order info back to customer
		order_t order=json_object_json_string_to_order(buff);
		orders_node_update_serve_time(becust.orders_node, order.order_id, order.serve_time);
		const char* dish_ready_str=response_dish_ready(&order);
		send(client_sid,dish_ready_str,strlen(dish_ready_str),0);
	}
}
int main(int argcnt,char **args)
{
	if (argcnt!=3){
		printf("Usage: %s <IP> <Port>",args[0]);
		exit(1);
	}
	IP=args[1];
	PORT=atoi(args[2]);
	
	if(mkfifo(FIFO_PIPE_NAME,O_RDWR|0666)!=0){
		perror("server mkfifo");
		exit(1);
	}

	pfd=open(FIFO_PIPE_NAME,O_RDWR);
	if(pfd==-1){
		perror("serve open fifo");
		exit(1);
	}
	
	if(signal(SIG_USR1,on_order_complete)==SIG_ERR){
		perror("server signal regist");
		exit(1);
	}

	start_cooking_queue(pfd);

	int sock_id=init_server(IP,PORT);
	int fork_id=-1;
	while(true){
		client_sid=accept(sock_id,NULL,NULL);
		for_id=fork();
		if(fork_id==0){
			break;
		}
	}
	char *buf[1024];
	int rb=-1;
	if(fork_id==0){
		const char *temp=request_update_customer();
		send(client_sid,temp,strlen(temp),0);
		while(true){
			bzero(buf,sizeof(buf));
			rb=recv(client_id,buf,sizeof(buf));
			if(rb>0){
				if(!decipher_request(buf, strlen(buf))){
					decipher_response(buf,strlen(buf));
				}
			}
			sleep(1);
		}			
	}
	return 0;
}

bool decipher_request(const char *buffer,int buf_len){
	bool is_consumed=true;
	struct json_object *obj=decode_request(buffer);
	int request_type=json_object_get_int(json_object_object_get(obj,"request_type"));
	switch (request_type){
		case REQUEST_TYPE_SHOW_MENU:
			break;
		case REQUEST_TYPE_PLACE_ORDER:
			{
				order_t order=json_object_get_string(json_object_object_get(obj,"data"));
				orders_node_add_order(becust.orders_node,&order);
				cookqueue_order_add(&order);
			}
			break;
		case REQUEST_TYPE_CHECK_OUT:
			break;
		default:
			is_consumed=false;
			break;
	}
	return is_consumed;
}

bool decipher_response(const char *buffer,int buf_len){
	bool is_consumed=true;
	struct json_object *obj=decode_response(buffer);
	int response_type=json_object_get_int(json_object_object_get(obj,"response_type"));
	switch (response_type){
		case RESPONSE_TYPE_UPDATE_CUSTOMER:
			{
				const char* cust_jstr=json_object_get_string(json_object_object_get(obj,"data"));
				customer_t cust=json_object_json_string_to_customer(cust_jstr);
				upate_customer(cust);
			}
			break;
		default:
			is_consumed=false;
		    break;
	}
}

void upate_customer(customer_t cust){
	becust.customer=(customer_t*)malloc(sizeof(customer_t));
	becust.customer->customer_id=cust.customer_id;
	becust.customer->fd=cust.fd;
	strcpy(becust.customer->name,cust.name);
	becust.customer->table_id=cust.table_id;
	becust.orders_node=orders_node_init_head();
}



