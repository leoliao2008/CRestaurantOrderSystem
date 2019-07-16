#include "base_includes.h"
#include "types.h"
#include "db_utils.h"
#include "dish.h"
#include "dishes_node.h"

void main()
{
	printf("--------------test db-------------\n");
	db_utils_init_restaurant_db_tables();
	db_utils_add_dish("Fried Chicken Wing", 12, 50);
	printf("add cusine Fried Chicken Wing.\n");
	db_utils_add_dish("Roast Duck", 88, 30);
	printf("add cusine Roast Duck.\n");
	db_utils_add_dish("Beef Steak 80%", 25, 120);
	printf("add cusine Beef Steak.\n");
	db_utils_add_dish("Coke", 5, 500);
	printf("add cusine complete.\n");
	dishes_node_t *head=dishes_node_init_head();
	db_utils_query_dishes(head);
	dishes_node_print_all(head);

}

