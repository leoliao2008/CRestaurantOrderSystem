#ifndef _RESPONSE_H
#define _RESPONSE_H

#include "base_includes.h"
#include "types.h"
#include "enums.h"

extern const char* response_update_customer_data(customer_t *cust);
extern const char* reponse_show_menu(dish_t *dish_arr,int arr_size);
extern const char* response_dish_ready(order_t *order);
extern const char* response_check_out(bill_t *bill);
extern const char* build_response(int type,int result_code,const char *data,int data_len);
extern struct json_object* decode_response(const char *json_str);

#endif