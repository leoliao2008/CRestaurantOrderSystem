#ifndef _PAYMENT_H
#define _PAYMENT_H

#include "base_includes.h"
#include "types.h"


extern struct json_object* json_object_payment_to_json_object(payment_t *p);
extern const char* json_object_payment_to_jason_string(payment_t *p);
extern payment_t json_object_json_string_to_payment(const char *json_str);


#endif
