#include "cookqueue.h"
#include "orders_node.h"
#include "dish_order.h"

static orders_node_t *cookqueue_head_node;

void *run(void*arg)
{
	orders_node_t *next=NULL;
	int pipe_fd=(int)arg;
	while (true){
		next=cookqueue_head_node->next;
		if(next!=cookqueue_head_node){
			printf("new order! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			sleep(5);
			printf("dish is read! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			const char *json_str=json_object_order_to_json_string(next->order);
			write(pipe_fd,json_str,strlen(json_str));
			kill(order->pid,SIG_USR1);
			orders_node_remove_order(cookqueue_head_node, next->order);
			free(next);
		}
		sleep(1);
	}
}

void start_cooking_queue(int pipe_fd)
{
	cookqueue_head_node=orders_node_init_head();
	pthread_t thread;
	pthread_create(&thread,run,(void*)pipe_fd);
}

void cookqueue_order_add(order_t *order)
{
	orders_node_add_order(cookqueue_head_node, order);
}


