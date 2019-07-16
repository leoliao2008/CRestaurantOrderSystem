#include "net_utils.h"


int init_server(char *ip,int port)
{
	int sock_id=socket(AF_INET,SOCK_STREAM,0);
	if(sock_id==-1){
		perror("server init_server");
		exit(1);
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	if(bind(sock_id,(struct sockaddr*)(&addr),sizeof(struct sockaddr))==-1){
		perror("serve bind");
		exit(1);
	}
	return sock_id;
}

