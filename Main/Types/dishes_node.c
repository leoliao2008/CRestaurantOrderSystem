#include "dishes_node.h"
#include "dish.h"

dishes_node_t* dishes_node_init_head()
{
	dishes_node_t *head=(dishes_node_t*)malloc(sizeof(dishes_node_t));
	head->dish=NULL;
	head->pre=head;
	head->next=head;
	return head;
}

void dishes_node_add_dish(dishes_node_t *head,dish_t dish)
{
	dish_t *new_dish=(dish_t*)malloc(sizeof(dish_t));
	new_dish->dish_id=dish.dish_id;
	new_dish->num_avail=dish.num_avail;
	new_dish->price=dish.price;
	strcpy(new_dish->name,dish.name);

	dishes_node_t *new_node=dishes_node_init_head();
	new_node->dish=new_dish;
	new_node->next=head;
	new_node->pre=head->pre;
	head->pre->next=new_node;
	head->pre=new_node;
}

void dishes_node_free(dishes_node_t *head)
{
	dishes_node_t *next=head->next;
	dishes_node_t *temp=NULL;
	while(next!=head){
		temp=next;
		next=next->next;
		free(temp);
	}
	free(head);
}

void dishes_node_print_all(dishes_node_t *head)
{
	dishes_node_t *next=head->next;
	while(next!=head){
		printf("%s\n",json_object_dish_to_json_string(next->dish));
		next=next->next;
	}
	free(head);
}



