
#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void init_list(list *l);

void pushElement(list *l, element *data);

void deleteElement(list *l);

element* nextElement(list *l);


#endif /* LISTS_H_ */
