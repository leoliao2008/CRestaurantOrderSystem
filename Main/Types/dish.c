#include "dish.h"

const char *json_object_dish_to_json_string(dish_t *dish)
{
	return json_object_to_json_string(json_object_dish_to_json_object(dish));
}


dish_t json_object_json_string_to_dish(const char *json_str)
{
	dish_t dish;
	struct json_object *obj=json_tokener_parse(json_str);
	struct json_object *dish_id=json_object_object_get(obj,"dish_id");
	struct json_object *name=json_object_object_get(obj,"name");
	struct json_object *price=json_object_object_get(obj,"price");
	struct json_object *num_avail=json_object_object_get(obj,"num_avail");
	dish.dish_id=json_object_get_int(dish_id);
	strcpy(dish.name,json_object_get_string(name));
	dish.price=json_object_get_double(price);
	dish.num_avail=json_object_get_int(num_avail);
	return dish;
}


struct json_object* json_object_dish_to_json_object(dish_t *dish)
{
	struct json_object *obj=json_object_new_object();
	struct json_object *dish_id=json_object_new_int(dish->dish_id);
	struct json_object *name=json_object_new_string(dish->name);
	struct json_object *price=json_object_new_double(dish->price);
	struct json_object *num_avail=json_object_new_int(dish->num_avail);
	json_object_object_add(obj,"dish_id",dish_id);
	json_object_object_add(obj,"name",name);
	json_object_object_add(obj,"price",price);
	json_object_object_add(obj,"num_avail",num_avail);

	return obj;

}

