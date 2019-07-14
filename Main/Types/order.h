#ifndef _ORDER_H
#define _ORDER_H

#include "../Includes/base_includes.h"
#include "../Includes/types.h"

const char *json_object_order_to_json_string(order_t *order);
order_t json_object_json_string_to_order(const char *json_str);

struct json_object* json_object_order_to_json_object(order_t *order);



#endif
