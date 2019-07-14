#include "order.h"
#include "dish.h"
#include "customer.h"

const char *json_object_order_to_json_string(order_t *order)
{
	
	return json_object_to_json_string(json_object_order_to_json_object(order));

}

order_t json_object_json_string_to_order(const char *json_str)
{
	order_t order;
	json_object *obj=json_tokener_parse(json_str);
	
	json_object *dish=json_object_object_get(obj,"dish");
	json_object *dish_id=json_object_object_get(dish,"dish_id");
	json_object *name=json_object_object_get(dish,"name");
	json_object *price=json_object_object_get(dish,"price");
	json_object *num_vail=json_object_object_get(dish,"num_avail");
	order.dish.dish_id=json_object_get_int(dish_id);
	order.dish.num_avail=json_object_get_int(num_vail);
	order.dish.price=json_object_get_double(price);
	strcpy(order.dish.name,json_object_get_string(name));

	json_object *cust=json_object_object_get(obj,"cust");
	json_object *customer_id=json_object_object_get(cust,"customer_id");
	json_object *table_id=json_object_object_get(cust,"table_id");
	json_object *fd=json_object_object_get(cust,"fd");
	json_object *c_name=json_object_object_get(cust,"name");
	order.cust.customer_id=json_object_get_int(customer_id);
	order.cust.fd=json_object_get_int(fd);
	order.cust.table_id=json_object_get_int(table_id);
	strcpy(order.cust.name,json_object_get_string(c_name));
	
	
	json_object *shares=json_object_object_get(obj,"shares");
	json_object *total_price=json_object_object_get(obj,"total_price");
	json_object *place_time=json_object_object_get(obj,"place_time");
	json_object *serve_time=json_object_object_get(obj,"serve_time");
	json_object *pid=json_object_object_get(obj,"pid");
	json_object *order_id=json_object_object_get(obj,"order_id");

	order.shares=json_object_get_int(shares);
	order.total_price=json_object_get_double(total_price);
	order.place_time=json_object_get_int(place_time);
	order.serve_time=json_object_get_int(serve_time);
	order.pid=json_object_get_int(pid);
	order.order_id=json_object_get_int(order_id);

	return order;
}

struct json_object* json_object_order_to_json_object(order_t *order)
{
    struct json_object *obj=json_object_new_object();
	struct json_object *dish=json_object_dish_to_json_object(&(order->dish));
	struct json_object *shares=json_object_new_int(order->shares);
	struct json_object *total_price=json_object_new_double(order->total_price);
	struct json_object *cust=json_object_customer_to_json_object(&(order->cust));
	struct json_object *place_time=json_object_new_int(order->place_time);
	struct json_object *serve_time=json_object_new_int(order->serve_time);
	struct json_object *pid=json_object_new_int(order->pid);
	struct json_object *order_id=json_object_new_int(order->order_id);

	json_object_object_add(obj,"dish",dish);
	json_object_object_add(obj,"shares",shares);
	json_object_object_add(obj,"total_price",total_price);
	json_object_object_add(obj,"cust",cust);
	json_object_object_add(obj,"place_time",place_time);
	json_object_object_add(obj,"serve_time",serve_time);
	json_object_object_add(obj,"pid",pid);
	json_object_object_add(obj,"order_id",order_id);

	return obj;

}
