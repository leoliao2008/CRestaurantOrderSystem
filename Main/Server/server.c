#include "server.h"
#include "net_utils.h"
#include "response.h"
#include "request.h"
#include "customer.h"
#include "order.h"
#include "orders_node.h"
#include "cookqueue.h"
#include "base_includes.h"
#include "db_utils.h"

static int msg_queue_id=-1;
static const char* IP;
static const int PORT;
static becustomer_t becust;
static int client_sid;


void on_order_complete(int signum){
	if(SIG_USR1==signum){
		msg_buff_t buff;
		msgrcv(msg_queue_id,&buff,sizeof(buff.order),2,0);
		printf("server is informed of finished order:");
		printf("%s\n",json_object_order_to_json_string(&(buff.order));
		//send order info back to customer
		order_t order=buff.order;
		orders_node_update_serve_time(becust.orders_node, order.order_id, order.serve_time);
		const char* json_response=response_dish_ready(&order);
		send(client_sid,json_response,strlen(json_response),0);
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

	int key=ftok("./",9527);
	if(key==-1){
		perror("server ftok");
		exit(1);
	}

	msg_queue_id=msgget(key,IPC_CREAT|0666);
	if(msg_queue_id==-1){
		perror("serve msg get");
		exit(1);
	}
	
	start_cooking_queue(msg_queue_id);

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
		if(signal(SIG_USR1,on_order_complete)==SIG_ERR){
		     perror("server signal regist");
		     exit(1);
	    }
		
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
	if(obj==NULL) return false;
	struct json_object *jsnobj_type=json_object_object_get(obj,"request_type");
	if(jsnobj_type==NULL) return false;
	int request_type=json_object_get_int(jsnobj_type);
	switch (request_type){
		case REQUEST_TYPE_SHOW_MENU:
			{
				dishes_node_t *head=dishes_node_init_head();
				db_utils_query_dishes(head);
				int size=head->size;
				const char* json_response;
				if(size>0){
					dish_t arr[size];
				    dishes_node_t *next=NULL;
					int i;
					for(i=0;i<size;i++){
						next=head->next;
						arr[i]=*(next->dish);
					}
					json_response=response_show_menu(arr,size);
				}else if(size==0){
					json_response=response_show_menu(NULL,0);
				}
				send(client_sid,json_response,strlen(json_response),0);
			}
			break;
		case REQUEST_TYPE_PLACE_ORDER:
			{
			    struct json_object *data=json_object_object_get(obj,"data");
				if(data==NULL) return false;
				const char *order_jstr=json_object_get_string(data);
				if(order_jstr==NULL) return false;
				order_t order=json_object_json_string_to_order(order_jstr);
				if(order==NULL) return false;
				//check if dish avail
				bool is_avail;
				if(db_utils_place_order(order)){
					is_avail=true;
					orders_node_add_order(becust.orders_node,&order);
					cookqueue_order_add(&order);
				}else{
					is_avail=false;
				}
				char *json_response=response_place_order(&order,is_avail);
				send(client_sid,json_response,strlen(json_response),0);
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



