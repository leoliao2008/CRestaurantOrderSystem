#ifndef _BILL_H
#define _BILL_H

#include "base_includes.h"
#include "types.h"

extern struct json_object* json_object_bill_to_json_object(bill_t *bill);
extern const char* json_object_bill_to_json_string(bill_t *bill);
extern bill_t json_object_json_string_to_bill(const char *json_str);

#endif
