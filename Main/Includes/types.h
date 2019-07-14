#ifndef _RST_TYPES_HEAD
#define _RST_TYPES_HEAD

typedef struct customer{
	int customer_id;
	int table_id;
	int fd;
	char name[20];
}customer_t;

typedef struct dish{
	int dish_id;
	char name[20];
	float price;
	int num_avail;
}dish_t;

typedef struct order{
	struct dish dish;
	int shares;
	float total_price;
	struct customer cust;
	long place_time;
	long serve_time;
	int pid;
	int order_id;
}order_t;

typedef struct orders_node{
	struct order *order;
	struct orders_node *pre;
	struct orders_node *next;
}orders_node_t;

typedef struct backend_customer{
	struct customer customer;
	struct orders_node *orders_node;
}becustomer_t;


typedef struct payment{
	char dish_name[20];
	int dish_id;
	float price;
	long served_time;
	int table_id;
}payment_t;

typedef struct bill{
	struct payment *pay_list;
	int list_len;
	struct customer cust;
	float total_price;
	long settle_time;
}bill_t;

#endif
