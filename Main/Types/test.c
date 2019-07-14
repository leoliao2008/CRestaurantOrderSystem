#include "customer.h"
#include "dish.h"
#include "order.h"
#include "orders_node.h"

void main()
{
	customer_t cust={123,456,78,"John"};
	const char *temp=json_object_customer_to_json_string(&cust);
	customer_t cust2=json_object_json_string_to_customer(temp);
	printf("customer id=%d table_id=%d fd=%d,name=%s\n",
			cust2.customer_id,cust2.table_id,cust2.fd,cust2.name);
	printf("%s\n",temp);

	printf("------------------------------------\n");
	dish_t dish={345,"roast beef",15.f,56};
	const char *temp2=json_object_dish_to_json_string(&dish);
	printf("%s\n",temp2);
	dish_t dish2=json_object_json_string_to_dish(temp2);
	printf("dishi id=%d name=%s,price=%f,num of avail=%d\n",dish2.dish_id,dish2.name,dish2.price,dish2.num_avail);

	printf("--------------------------------\n");
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

	printf("------------------------------------------\n");
	orders_node_t *head=orders_node_init_head();
	int i;
	for(i=0;i<10;i++){
		orders_node_add_order(head, &order);
	}
	orders_node_print_orders(head);
	orders_node_free_all_nodes(head);

}
