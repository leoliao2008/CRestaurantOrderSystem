#ifndef _DB_UTILS_HEAD
#define _DB_UTILS_HEAD

#include "base_includes.h"
#include "types.h"

extern void db_utils_init_restaurant_db_tables();
int dishes_query_callback(void* arg,int col_cnt,char **col_text,char **col_name);
extern void db_utils_query_dishes(dishes_node_t *head);
extern void db_utils_add_dish(const char*name,float price,int num_avail);
extern int db_utils_dish_get_number_avail(int dish_id);
extern bool db_utils_place_order(order_t order);

#endif