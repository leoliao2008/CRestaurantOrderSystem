#include "db_utils.h"
#include "dish.h"
#include "payment.h"

static sqlite3 *db;

void db_utils_init_restaurant_db_tables(){
	if(sqlite3_open(name,&db)!=SQLITE_OK){
		perror("open sql");
		eixt(1);
	}	
	char **errmsg;
	char *cmd_create_food_table="create table if not exists foods(dish_id Integer primary key 
	auto increment,name char[20],price double,num_avail int);";
	if(sqlite3_exec(db,cmd_create_food_table,NULL,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
	char *cmd_create_sales_table="create table if not exist sales(dish_name char[20],dish_id int,
	price double,served_time long,table_id int);";
	if(sqlite3_exec(db,cmd_create_sales_table,NULL,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}
	
}

void db_utils_query_dishes(int(*callback)(void*,int nCount,char** pValue,char** pName)){
	const char* cmd="select * from foods";
	char **errmsg;
	if(sqlite3_exec(db,cmd,callback,NULL,errmsg)!=SQLITE_OK){
		perror(*errmsg);
		exit(1);
	}

}

