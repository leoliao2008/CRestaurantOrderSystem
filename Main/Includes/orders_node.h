#ifndef _ORDERS_NODE_HEAD
#define _ORDERS_NODE_HEAD
#include "base_includes.h"
#include "types.h"

extern orders_node_t* orders_node_init_head();
extern void orders_node_add_order(orders_node_t *head,order_t *order);
extern void orders_node_remove_order(orders_node_t *head,order_t *order);
extern void orders_node_print_orders(orders_node_t *head);
extern void orders_node_free_all_nodes(orders_node_t *head);
extern bool orders_node_update_serve_time(orders_node_t *head,int order_id,long serve_time);



#endif


