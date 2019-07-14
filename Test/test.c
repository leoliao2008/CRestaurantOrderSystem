#include "../Main/Includes/base_includes.h"


int main(void)
{

	struct json_object *ojb=json_object_new_object();
	struct json_object *name=json_object_new_string("leo");
	json_object_object_add(ojb,"name",name);
	printf("%s\n",json_object_to_json_string(ojb));
	sqlite3 *db;
	sqlite3_open("./mydb.db",&db);
	sqlite3_close(db);





	return EXIT_SUCCESS;
}
