#include "server.h"
#include "net_utils.h"

extern orders_node_t *head_node;
const char* FIFO_PIPE_NAME="FIFO_PIPE_NAME.p";
static int pfd=-1;
static const char* IP;
static const int PORT:

void on_order_complete(int signum){
	char *buff[1024];
	if(SIG_USR1==signum){
		b_zero(buff,sizeof(buff));
		read(pfd,buff,sizeof(buff));
		printf("server is informed of finished order:");
		printf("%s\n",buff);
		//todo send order info back to customer

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
	int client_sid;
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
		bzero(buf,sizeof(buf));
		rb=recv(client_id,buf,sizeof(buf));
		if(rb>0){
			//todo dicipher client request.
		}

	}
	return 0;
}


