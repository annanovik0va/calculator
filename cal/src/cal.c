/*
 ===============================================================================
 Name        : cal.c
 Author      : Novikova Anna
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Данная программа реализует арифметические операции(+(сложение),
             |-(вычитание), /(деление), *(произведение), !(факториал числа),
             |p(возведение числа в степень p))над двумя числами, введеными пользователем,
             |+(сложение векторов), -(разность векторов), *(скалярное произведение
             |векторов)),то есть мы получаем мини-калькулятор!
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

//Элемент стека
struct StackElement{
  double element;
  struct StackElement *next;
};

struct Stack
{
  struct StackElement *tail;
};

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

int
main (int   argc,
      char *argv[])
{
  setvbuf (stdout, NULL, _IONBF, 0);
  setvbuf (stderr, NULL, _IONBF, 0);

  char ys;
  FILE *input, *output;
  char input_name[259],output_name[259];
  char temp[64];
  int t = FALSE, i = 0;
  double num, x, y;
  struct Stack *stack = malloc( sizeof (struct Stack));
  init_stack (stack);

  do
  {
    printf ("Введите имя файла, из которого будут читаться операции.\n");
    scanf ("%s", input_name);
    input = fopen (input_name,"r");

    while (input == NULL || feof (input))
			{
				if (feof (input))
					printf ("Фаил пустой.\n");
				else
					printf ("Неверное название файла.\n");

				scanf (" %s", input_name);
				input = fopen (input_name, "r");
			}

    printf ("Введите имя файла, в который будут записываться результаты.\n");
    scanf ("%s", output_name);

    if ((output = fopen (output_name, "a")) == NULL) {
      output = fopen (output_name, "w");
    }

    while (feof (input) == 0)
    {
      fscanf (input, "%c", &temp[i]);
			if (temp[i] == ' ')
      {
				if (t == FALSE)
        {
					num = strtof (temp, NULL);
					push_stack (stack, num);
					i = 0;
				}
			} else if (temp[i] == '*' ||
                 temp[i] == '+' ||
                 temp[i] == '-' ||
                 temp[i] == '/')
      {
				y = pop_stack (stack);
				x = pop_stack (stack);
				push_stack (stack, calculator (x, temp[i], y));
				fprintf (output, "%.2f %c %.2f = %.2f\n", x, temp[i], y, calculator (x, temp[i], y));
				t = TRUE;
			} else if (temp[i] == 'n')
      {
				delete_stack (stack);
				fprintf (output, "---------------------------------\n");
			} else
      {
				t = FALSE;
				i = i + 1;
			}
    }

    fclose (input);
    fclose (output);
    free (stack);

    printf ("Работа с файлом завершена!\n");
    printf ("Хотите продолжить работу?(y/n)\n");
    scanf (" %c",&ys);
  } while (ys == 'y');

  return 0;
}
