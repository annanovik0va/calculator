
#include "struct.h"
#include <stdlib.h>
#include <stdio.h>

//Инициализация стека
void
init_stack (struct Stack *stack)
{
  stack->tail = NULL;
}

//Записать данные в стек
void
push_stack (struct Stack *stack,
            double element)
{
  struct StackElement *temp_tail = malloc (sizeof (struct StackElement));
  temp_tail->next = stack->tail;
  stack->tail = temp_tail;
  stack->tail->element = element;
}

//Забрать данные стека
double
pop_stack (struct Stack *stack)
{
  if (stack->tail == NULL)
  {
    fprintf (stderr, "Stack is already empty");
    return;
  }

  double return_data = stack->tail->element;
  struct StackElement *ref_tail = stack->tail;
  stack->tail = stack->tail->next;
  free (ref_tail);
  return return_data;
}

//Очистить стек
void
delete_stack (struct Stack *stack)
{
  while (stack->tail != NULL)
  {
    pop_stack (stack);
  }
}

double
calculator (double first_number,
            char operation,
            double second_number)
{
  switch (operation)
    {
    case '+': return first_number + second_number;
    case '-': return first_number - second_number;
    case '/': return first_number / second_number;
    case '*': return first_number * second_number;
    }
}
