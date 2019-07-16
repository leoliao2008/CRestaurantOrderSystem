#include "cookqueue.h"
#include "orders_node.h"
#include "dish_order.h"

orders_node_t *head_node;

static void *run(void*arg)
{
	orders_node_t *next=NULL;
	int pipe_fd=(int)arg;
	while (true){
		next=head_node->next;
		if(next!=head_node){
			printf("new order! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			sleep(5);
			printf("dish is read! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			const char *json_str=json_object_order_to_json_string(next->order);
			write(pipe_fd,json_str,strlen(json_str));
			kill(order->pid,SIG_USR1);
			orders_node_remove_order(head_node, next->order);
			free(next);
		}
		sleep(1);
	}
}

void start_cooking_queue(int pipe_fd)
{
	head_node=orders_node_init_head();
	pthread_t thread;
	pthread_create(&thread,run,(void*)pipe_fd);
}


