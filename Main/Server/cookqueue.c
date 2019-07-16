#include "cookqueue.h"
#include "orders_node.h"
#include "dish_order.h"

static orders_node_t *cookqueue_head_node;

void *run(void*arg)
{
	orders_node_t *next=NULL;
	int queue_id=(int)arg;
	while (true){
		next=cookqueue_head_node->next;
		if(next!=cookqueue_head_node){
			printf("new order! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			sleep(5);
			printf("dish is read! %s's %s.\n",next->order->cust.name,next->order->dish->name);
			const char *json_str=json_object_order_to_json_string(next->order);
			order_t order=json_object_json_string_to_order(json_str);
			msg_buff_t buff={2,order};
			msgsnd(queue_id,&buff,sizeof(order_t),0);
			kill(order->pid,SIG_USR1);
			orders_node_remove_order(cookqueue_head_node, next->order);
			free(next);
		}else{
			sleep(1);
		}
	}
}

void start_cooking_queue(int msg_queue_id)
{
	cookqueue_head_node=orders_node_init_head();
	pthread_t thread;
	pthread_create(&thread,run,(void*)msg_queue_id);
}

void cookqueue_order_add(order_t *order)
{
	orders_node_add_order(cookqueue_head_node, order);
}


