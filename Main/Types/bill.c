#include "bill.h"
#include "payment.h"
#include "customer.h"

struct json_object* json_object_bill_to_json_object(bill_t *bill)
{
	struct json_object* obj=json_object_new_object();

	struct json_object* pays=json_object_new_array();
	int i;
	payment_t *p=NULL;
	for(i=0;i<(bill->pays_len);i++){
		p=&(bill->pays[i]);
		struct json_object *jo=json_object_payment_to_json_object(p);
		json_object_array_add(pays,jo);
	}
	struct json_object* cust=json_object_customer_to_json_object(&(bill->cust));
	struct json_object* pays_len=json_object_new_int(bill->pays_len);
	struct json_object* total_price=json_object_new_double(bill->total_price);
	struct json_object* settle_time=json_object_new_int(bill->settle_time);			
	json_object_object_add(obj,"pays",pays);
	json_object_object_add(obj,"pays_len",pays_len);
	json_object_object_add(obj,"cust",cust);
	json_object_object_add(obj,"total_price",total_price);
	json_object_object_add(obj,"settle_time",settle_time);
	return obj;
}

const char* json_object_bill_to_json_string(bill_t *bill)
{
	return json_object_to_json_string(json_object_bill_to_json_object(bill));
}

bill_t json_object_json_string_to_bill(const char *json_str)
{
	bill_t bill;
	struct json_object* obj=json_tokener_parse(json_str);
	struct json_object* pays=json_object_object_get(obj,"pays");
	struct json_object* pays_len=json_object_object_get(obj,"pays_len");
	struct json_object* cust=json_object_object_get(obj,"cust");
	struct json_object* total_price=json_object_object_get(obj,"total_price");
	struct json_object* settle_time=json_object_object_get(obj,"settle_time");

	int i;
	int len=json_object_get_int(pays_len);
	bill.pays=(payment_t*)malloc(sizeof(payment_t)*len);
	
	struct json_object* temp=NULL;
	for(i=0;i<len;i++){
			temp=json_object_array_get_idx(pays,i);
			const char *str=json_object_to_json_string(temp);
			bill.pays[i]=json_object_json_string_to_payment(str);
	}
	bill.pays_len=len;
	bill.cust=json_object_json_string_to_customer(json_object_to_json_string(cust));
	
	bill.total_price=json_object_get_double(total_price);
	bill.settle_time=json_object_get_int(settle_time);	
	return bill;
}


