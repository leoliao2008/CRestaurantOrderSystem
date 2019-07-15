#include "payment.h"

struct json_object* json_object_payment_to_json_object(payment_t *p){
	struct json_object *obj=json_object_new_object();
	struct json_object *dish_name=json_object_new_string(p->dish_name);
	struct json_object *dish_id=json_object_new_int(p->dish_id);
	struct json_object *price=json_object_new_double(p->price);
	struct json_object *served_time=json_object_new_int(p->served_time);
	struct json_object *table_id=json_object_new_int(p->table_id);

	json_object_object_add(obj,"dish_name",dish_name);
	json_object_object_add(obj,"dish_id",dish_id);
	json_object_object_add(obj,"price",price);
	json_object_object_add(obj,"served_time",served_time);
	json_object_object_add(obj,"table_id",table_id);

	return obj;
}

const char* json_object_payment_to_jason_string(payment_t *p){
	return json_object_to_json_string(json_object_payment_to_json_object(p));
}

payment_t json_object_json_string_to_payment(const char *json_str){
	payment_t payment;
	struct json_object *obj=json_tokener_parse(json_str);
	struct json_object *dish_name=json_object_object_get(obj,"dish_name");
	struct json_object *dish_id=json_object_object_get(obj,"dish_id");
	struct json_object *price=json_object_object_get(obj,"price");
	struct json_object *served_time=json_object_object_get(obj,"served_time");
	struct json_object *table_id=json_object_object_get(obj,"table_id");

	payment.dish_id=json_object_get_int(dish_id);
	payment.price=json_object_get_double(price);
	payment.served_time=json_object_get_int(served_time);
	payment.table_id=json_object_get_int(table_id);
	strcpy(payment.dish_name,json_object_get_string(dish_name));

	return payment;
	
}





