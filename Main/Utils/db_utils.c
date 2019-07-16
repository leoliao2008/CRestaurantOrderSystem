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
void db_utils_query_dishes(dishes_node_t *head){
	const char* cmd="select * from foods";
	char **errmsg=NULL;
	if(sqlite3_exec(db,cmd,dishes_query_callback,(void*)head,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
}

