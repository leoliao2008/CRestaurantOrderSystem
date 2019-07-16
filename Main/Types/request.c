#include "request.h"
#include "order.h"


const char* request_update_customer()
{
	return build_request(REQUEST_TYPE_UPDATE_CUSTOMER, "", strlen(""), "", strlen(""));
}

const char* request_show_menu()
{
	return build_request(REQUEST_TYPE_SHOW_MENU, "", strlen(""), "", strlen(""));
}

const char* request_place_order(order_t *order)
{
	const char* order_str=json_object_order_to_json_string(order);
	return build_request(REQUEST_TYPE_PLACE_ORDER, "", strlen(""), order_str, strlen(order_str));
}

const char* request_check_out()
{
	return build_request(REQUEST_TYPE_CHECK_OUT, "", strlen(""), "", strlen(""));
}


const char* build_request(int type,const char*param,int params_len,const char*data,int data_len)
{
	struct json_object* obj=json_object_new_object();
	json_object_object_add(obj,"request_type",json_object_new_int(type));
	json_object_object_add(obj,"params",json_object_new_string(param));
	json_object_object_add(obj,"params_len",json_object_new_int(params_len));
	json_object_object_add(obj,"data",json_object_new_string(data));
	json_object_object_add(obj,"data_len",json_object_new_int(data_len));
	
	return json_object_to_json_string(obj);
}

struct json_object* decode_request(const char *json_str)
{
	return json_tokener_parse(json_str);
}