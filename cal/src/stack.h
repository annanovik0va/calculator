
#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

//Инициализация стека
void
init_stack (struct Stack *stack);


//Записать данные в стек
void
push_stack (struct Stack *stack,
            double element);

//Забрать данные стека
double
pop_stack (struct Stack *stack);


//Очистить стек
void
delete_stack (struct Stack *stack);

double
calculator (double first_number,
            char operation,
            double second_number);


#endif /* STACK_H_ */
