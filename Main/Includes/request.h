#ifndef _BASE_REQUEST_H
#define _BASE_REQUEST_H

#include "base_includes.h"
#include "enums.h"
#include "types.h"

extern const char* request_update_customer();
extern const char* request_show_menu();
extern const char* request_place_order(order_t *order);
extern const char* request_check_out();
const char* build_request(int type,const char*param,int params_len,const char*data,int data_len);
extern struct json_object* decode_request(const char *json_str);
#endif