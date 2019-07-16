#ifndef _DISHES_NODE_H
#define _DISHES_NODE_H

#include "base_includes.h"
#include "types.h"

extern dishes_node_t* dishes_node_init_head();
extern void dishes_node_add_dish(dishes_node_t *head,dish_t dish);
extern void dishes_node_free(dishes_node_t *head);


#endif