#include "response.h"
#include "customer.h"
#include "dish.h"
#include "order.h"
#include "bill.h"

const char* response_update_customer_data(customer_t *cust)
{
	const char* data=json_object_customer_to_json_string(cust);
	return build_response(RESPONSE_TYPE_UPDATE_CUSTOMER, RESPONSE_RESULT_CODE_OK, data, strlen(data));
}

const char* reponse_show_menu(dish_t *dish_arr,int arr_size)
{
	struct json_object* arr=json_object_new_array();
	int i;
	for(i=0;i<arr_size;i++){
		json_object_array_add(arr,json_object_dish_to_json_object(&(dish_arr[i])));
	}
	const char* data=json_object_to_json_string(arr);
	return build_response(RESPONSE_TYPE_SHOW_MENU, RESPONSE_RESULT_CODE_OK, data, strlen(data));

}

const char* response_dish_ready(order_t *order)
{
	const char* data=json_object_order_to_json_string(order);
    return build_response(RESPONSE_TYPE_DISH_READY, RESPONSE_RESULT_CODE_OK, data, strlen(data));
}

const char* response_check_out(bill_t *bill)
{
    const char* data=json_object_bill_to_json_string(bill);
    return build_response(RESPONSE_TYPE_CHECK_OUT, RESPONSE_RESULT_CODE_OK, data, strlen(data));
}

const char* build_response(int type,int result_code,const char *data,int data_len)
{
	struct json_object *obj=json_object_new_object();
	json_object_object_add(obj,"response_type",json_object_new_int(type));
	json_object_object_add(obj,"result_code",json_object_new_int(result_code));
	json_object_object_add(obj,"data",json_object_new_string(data));
	json_object_object_add(obj,"data_len",json_object_new_int(data_len));
	
	return json_object_to_json_string(obj);
}

struct json_object* decode_response(const char *json_str)
{
	return json_tokener_parse(json_str);
}

