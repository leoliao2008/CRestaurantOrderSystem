#ifndef _DISH_HEAD
#define _DISH_HEAD

#include "../Includes/types.h"
#include "../Includes/base_includes.h"

const char* json_object_dish_to_json_string(dish_t *dish);
dish_t json_object_json_string_to_dish(const char *json_str);
struct json_object* json_object_dish_to_json_object(dish_t *dish);


#endif
