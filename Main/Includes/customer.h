#ifndef _CUSTOMER_H
#define _CUSTOMER_H

#include "base_includes.h"
#include "types.h"

const char* json_object_customer_to_json_string(customer_t *cust);

customer_t json_object_json_string_to_customer(const char *obj_str);

struct json_object* json_object_customer_to_json_object(customer_t *cust);



#endif
