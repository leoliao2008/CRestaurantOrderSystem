#ifnedf _COOK_QUEUE_H
#define _COOK_QUEUE_H

#include "../Includes/base_includes.h"
#include "../Includes/types.h"

extern void start_cooking_queue(int pipe_fd);
extern void cookqueue_order_add(order_t *order);

#endif