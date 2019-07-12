#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "/usr/local/include/json/json.h"

int main(void)
{

	json_object *ojb=json_object_new_object();

	sqlite3 *db;
	sqlite3_open("./mydb.db",&db);
	sqlite3_close(db);





	return EXIT_SUCCESS;
}
