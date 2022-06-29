
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void init_queue(queue *l);

void enqueue(queue *l, element *data);

element* withdrawal(queue *q);


#endif /* QUEUE_H_ */
