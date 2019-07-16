#include "db_utils.h"
#include "dish.h"
#include "payment.h"
#include "dishes_node.h"

static sqlite3 *db;

void db_utils_init_restaurant_db_tables(){
	if(sqlite3_open("RestaurantDb.db",&db)!=SQLITE_OK){
		perror("open sql");
		exit(1);
	}	
	char **errmsg=NULL;
	char *cmd_create_food_table="create table if not exists foods(dish_id Integer primary key,name char[20],price double,num_avail int);";
	if(sqlite3_exec(db,cmd_create_food_table,NULL,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
	char *cmd_create_sales_table="create table if not exists sales(dish_name char[20],dish_id int,price double,served_time long,table_id int);";
	if(sqlite3_exec(db,cmd_create_sales_table,NULL,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
	
}

//int(*callback)(void*,int nCount,char** pValue,char** pName)
int dishes_query_callback(void* arg,int col_cnt,char **col_text,char **col_name)
{
	dishes_node_t *head=(dishes_node_t*)arg;
	dish_t dish;
	dish.dish_id=atoi(col_text[0]);
	strcpy(dish.name,col_text[1]);
	dish.price=atof(col_text[2]);
	dish.num_avail=atoi(col_text[3]);
	dishes_node_add_dish(head,dish);
	return 0;
}

void db_utils_add_dish(const char*name,float price,int num_avail)
{
	printf("add dish start...\n");
	char buf[1024];
	bzero(buf,sizeof(buf));
	snprintf(buf,sizeof(buf),"insert into foods values(NULL,\"%s\",%f,%d);\n",name,price,num_avail);
	printf("%s\n",buf);
	char **errmsg=NULL;
	if(sqlite3_exec(db,buf,NULL,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		//perror("db_utils_add_dish error.\n");
	}
	printf("add dish ends...\n");
}


int db_utils_dish_get_number_avail(int dish_id)
{
	int result=-1;
	dish_t *temp_dish=NULL;
	dishes_node_t *head=dishes_node_init_head();
	db_utils_query_dishes(head);
	dishes_node_t *next=head->next;
	while(next!=head){
		temp_dish=next->dish;
		if(temp_dish->dish_id==dish_id){
			result=temp_dish->num_avail;
			break;
		}
		next=next->next;
	}
	return result;

}

bool db_utils_place_order(order_t order)
{
	bool is_success=false;
	dish_t order_dish=order.dish;
	dish_t *temp_dish=NULL;
	dishes_node_t *head=dishes_node_init_head();
	db_utils_query_dishes(head);
	dishes_node_t *next=head->next;
	while(next!=head){
		temp_dish=next->dish;
		if(temp_dish->dish_id==dish_id){
			if(temp_dish->num_avail>=order.shares){
				char cmd[1024];
				snprintf(cmd,sizeof(cmd),"update foods set num_avail=%d where dish_id=%d;",
				(temp_dish->num_avail-order.shares),order_dish.dish_id);
				char **errmsg=NULL;
				if(sqlite3_exec(db,cmd,NULL,NULL,errmsg)!=SQLITE_OK){
					perror("db_utils_place_order:%s\n",*errmsg);
					sqlite3_free(errmsg);
				}
				is_success=true;
			}
			break;
		}
		next=next->next;
	}
	return is_success;
}



void db_utils_query_dishes(dishes_node_t *head){
	const char* cmd="select * from foods";
	char **errmsg=NULL;
	if(sqlite3_exec(db,cmd,dishes_query_callback,(void*)head,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
}

