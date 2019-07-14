#include "customer.h"

const char* json_object_customer_to_json_string(customer_t *cust)
{
	return json_object_to_json_string(json_object_customer_to_json_object(cust));
}

customer_t json_object_json_string_to_customer(const char *obj_str)
{
	customer_t cust;
	struct json_object *obj=json_tokener_parse(obj_str);
	struct json_object *cid=json_object_object_get(obj,"customer_id");
	struct json_object *tid=json_object_object_get(obj,"table_id");
	struct json_object *fid=json_object_object_get(obj,"fd");
	struct json_object *name=json_object_object_get(obj,"name");
	cust.customer_id=json_object_get_int(cid);
	cust.table_id=json_object_get_int(tid);
	cust.fd=json_object_get_int(fid);
	strcpy(cust.name,json_object_get_string(name));
	return cust;
}

struct json_object* json_object_customer_to_json_object(customer_t *cust)
{
	struct json_object *obj=json_object_new_object();
	struct json_object *customer_id=json_object_new_int(cust->customer_id);
	struct json_object *table_id=json_object_new_int(cust->table_id);
	struct json_object *fd=json_object_new_int(cust->fd);
	struct json_object *name=json_object_new_string(cust->name);

	json_object_object_add(obj,"customer_id",customer_id);
	json_object_object_add(obj,"table_id",table_id);
	json_object_object_add(obj,"fd",fd);
	json_object_object_add(obj,"name",name);
	
	return obj;
}


