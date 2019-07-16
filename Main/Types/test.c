#include "customer.h"
#include "dish.h"
#include "order.h"
#include "orders_node.h"
#include "payment.h"
#include "bill.h"
#include "request.h"
#include "response.h"
#include "dishes_node.h"

void main()
{
	printf("--------------Customer--------------");
	customer_t cust={123,456,78,"John"};
	const char *temp=json_object_customer_to_json_string(&cust);
	customer_t cust2=json_object_json_string_to_customer(temp);
	printf("customer id=%d table_id=%d fd=%d,name=%s\n",
			cust2.customer_id,cust2.table_id,cust2.fd,cust2.name);
	printf("%s\n",temp);

	printf("-----------Dish-------------\n");
	dish_t dish={345,"roast beef",15.f,56};
	const char *temp2=json_object_dish_to_json_string(&dish);
	printf("%s\n",temp2);
	dish_t dish2=json_object_json_string_to_dish(temp2);
	printf("dishi id=%d name=%s,price=%f,num of avail=%d\n",dish2.dish_id,dish2.name,dish2.price,dish2.num_avail);

	printf("----------Order----------------\n");
	order_t order;
	order.cust=cust;
	order.dish=dish;
	order.order_id=123456;
	order.pid=7;
	order.place_time=431431;
	order.serve_time=342343;
	order.shares=2;
	order.total_price=10000;
	const char *temp3=json_object_order_to_json_string(&order);
	printf("%s\n",temp3);
	order_t order2=json_object_json_string_to_order(temp3);
	printf("%s\n",json_object_order_to_json_string(&order2));

	printf("------------orders node---------------------\n");
	orders_node_t *head=orders_node_init_head();
	int i;
	for(i=0;i<10;i++){
		orders_node_add_order(head, &order);
	}
	orders_node_print_orders(head);
	orders_node_free_all_nodes(head);

	printf("------------payment--------------\n");
	payment_t payment;
	strcpy(payment.dish_name,"fried chichen wing");
	payment.dish_id=999;
	payment.price=50;
	payment.served_time=14523;
	payment.table_id=3;
	const char* temp4=json_object_payment_to_jason_string(&payment);
	printf("%s\n",temp4);
	payment_t payment2=json_object_json_string_to_payment(temp4);
	printf("%s\n",json_object_payment_to_jason_string(&payment2));

	printf("---------------Bill-------------\n");

	bill_t bill;
	bill.pays=(payment_t*)malloc(sizeof(payment_t)*3);
	bill.cust=cust;
	bill.pays_len=3;
	bill.pays[0]=payment;
	bill.pays[1]=payment2;
	bill.pays[2]=payment;
	bill.settle_time=123456;
	bill.total_price=9999;
	const char* temp5=json_object_bill_to_json_string(&bill);
	printf("%s\n",temp5);
	bill_t bill2=json_object_json_string_to_bill(temp5);
	printf("%s\n",json_object_bill_to_json_string(&bill2));

	printf("-----------------request--------------------\n");
	printf("%s\n",request_place_order(&order));

	printf("-----------------response-------------------\n");
	printf("%s\n",response_check_out(&bill));

	printf("-----------------dishes_node-----------------\n");
	dishes_node_t* dnode=dishes_node_init_head();
	dishes_node_add_dish(dnode, dish);
	dishes_node_add_dish(dnode, dish2);
	dishes_node_print_all(dnode);
	dishes_node_free(dnode);

	
}
