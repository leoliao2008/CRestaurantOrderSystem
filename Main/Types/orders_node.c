#include "orders_node.h"

orders_node_t* orders_node_init_head()
{
	orders_node_t *head=(orders_node_t*)malloc(sizeof(orders_node_t));
	head->order=NULL;
	head->next=head;
	head->pre=head;
	return head;
}

void orders_node_add_order(orders_node_t *head,order_t *order)
{
	orders_node_t *new_node=orders_node_init_head();
	new_node->order=order;
	new_node->next=head;
	new_node->pre=head->pre;
	head->pre->next=new_node;
	head->pre=new_node;
}

void orders_node_remove_order(orders_node_t *head,order_t *order)
{
	orders_node_t *temp=head->next;
	bool is_found=false;
	while(temp!=head){
		if(temp->order->order_id==order->order_id)
		{
		 is_found=true;
         break;
		}
	}
	if(is_found){
		temp->next->pre=temp->pre;
		temp->pre->next=temp->next;
		free(temp);
	}
}

void orders_node_print_orders(orders_node_t *head){
	orders_node_t *temp=head->next;
	order_t *order;
	if(temp==head){
		printf("order node is empty.\n");
		return;
	}
	while(temp!=head){
		order=temp->order;
		printf("order of customer:%s,order id=%d,place time=%ld\n",order->cust.name,order->order_id,order->place_time);
		temp=temp->next;
	}
}

void orders_node_free_all_nodes(orders_node_t *head){
	orders_node_t *temp=head->next;
	orders_node_t *node;
	while(temp!=head){
		node=temp;
		temp=temp->next;
		free(node);
	}
	free(temp);
}




