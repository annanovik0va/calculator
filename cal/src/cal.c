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
#include "struct.h"
#include "lists.h"
#include "queue.h"
#include "stack.h"


#define TRUE 1
#define FALSE 0


int
main (int   argc,
      char *argv[])
{
  setvbuf (stdout, NULL, _IONBF, 0);
  setvbuf (stderr, NULL, _IONBF, 0);

  char ys,vi;
  FILE *input, *output;
  char input_name[259],output_name[259];
  char temp[64];
  int t = FALSE, i = 0;
  double num, x, y;
  struct Stack *stack = malloc( sizeof (struct Stack));
  init_stack (stack);
  element *tmp;
  list l1, l2;
  queue q1, q2;

  do
  {   //input.txt для стека, input1.txt для списков и очереди
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
	//l-списки,q-очередь,s-стек.
    printf ("Выберите: списки, очередь,(обычная нотация),стек(обратная польская)");
    scanf ("%s", &vi);
    switch(vi){
    case 'l':
    	       init_list(&l1);
    	       init_list(&l2);
    	   	   tmp = malloc(sizeof(element));
    	   	   while (feof(input) == 0){
    	   		   	fscanf(input," %c %c", &tmp->op, &tmp->mod);
    	   			switch (tmp->mod){
    	   				case 'n':
    	   					tmp->size = 1;
    	   					if (tmp->op == '!'){
    	   						tmp->x = malloc(sizeof(float));
    	   						for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			            tmp->y = NULL;
    	   			        }
    	   			        else{
    	   			        	tmp->x = malloc(sizeof(float));
    	   			            tmp->y = malloc(sizeof(float));
    	   			            for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			            for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->y[i]);
    	   			        }
    	   			        break;
    	   			    case 'v':
    	   			    	fscanf(input, "%i", &tmp->size);
    	   			    	tmp->x = malloc(tmp->size*sizeof(float));
    	   			        tmp->y = malloc(tmp->size*sizeof(float));
    	   			        for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			        for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->y[i]);
    	   			        break;
    	   			    }
    	   			tmp->next = NULL;
    	   		   pushElement(&l1, tmp);
    	   	   }
    	   	   l1.current = l1.head;
    	   	   while (l1.current != NULL){
    	   		   tmp->x = l1.current->x;
    	   		   tmp->y = l1.current->y;
    	   		   tmp->size = l1.current->size;
    	   		   tmp->mod = l1.current->mod;
    	   		   tmp->op = l1.current->op;
    	   		   float *result;
    	   		   int p;
    	   		   unsigned long int res = 1;
    	   		   switch (tmp->mod){
    	   		   	   case 'v':
    	   		   		   switch (tmp->op){
    	   						case '+':
    	   							result = malloc(tmp->size*sizeof(float));
    	   							for (int i = 0; i < tmp->size; i++) result[i] = tmp->x[i] + tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   						case '-':
    	   							result = malloc(tmp->size*sizeof(float));
    	   							for (int i = 0; i < tmp->size; i++) result[i] = tmp->x[i] - tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   						case '*':
    	   							result = malloc(sizeof(float));
    	   							*result = 0;
    	   							for (int i = 0; i < tmp->size; i++) *result += tmp->x[i] * tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   					}
    	   					break;
    	   				case 'n':
    	   					switch (tmp->op){
    	   						case '+':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x + *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '-':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x - *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '*':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x * *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '/':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x / *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '!':
    	   							if (*tmp->x > 0) {
    	   								for (int  i = 1; i <= *tmp->x; i++) {
    	   									res *=i;
    	   								}
    	   							}
    	   							tmp->res = res;
    	   							break;
    	   						case '^':
    								p = *tmp->x;
    	   							if (p < 0)	{
    	   								p = -p;
    	   								for (int i=1; i<=*tmp->y; i++) {
    	   									res *= p;
    	   								}
    	   							res = (1/(*result));
    	   							}
    	   							else {
    	   								for (int i=1; i<=*tmp->y; i++) {
    	   									res *= p;
    	   								}
    	   							}
    	   							tmp->res = res;
    	   						break;
    	   					}
    	   					break;
    	   				}
    	   		   pushElement(&l2, tmp);
    	   		   nextElement(&l1);
    	   	   }
    	   	   free(tmp);
    	   	   l1.current = l1.head;
    	   	   l2.current = l2.head;
    	   	   if ((output = fopen(output_name, "a")) == NULL) {
    	   		   output = fopen(output_name, "w");
    	   	   }
    			while (l2.current != NULL){
    					switch (l2.current->mod){
    						case 'v':
    							fprintf(output, "( ");
    							for (int i = 0; i < l2.current->size; i++){
    								if (i == l2.current->size - 1){
    									fprintf(output, "%lf", l2.current->x[i]);
    								}
    								else fprintf(output, "%lf ", l2.current->x[i]);
    							}
    							fprintf(output, " ) %c ( ", l2.current->op);
    							for (int i = 0; i < l2.current->size; i++){
    								if (i == l2.current->size - 1){
    									fprintf(output, "%lf", l2.current->y[i]);
    								}
    								else fprintf(output, "%lf ", l2.current->y[i]);
    							}
    							if (l2.current->op == '+' || l2.current->op == '-'){
    								fprintf(output, " ) = ( ");
    								for (int i = 0; i < l2.current->size; i++){
    									if (i == l2.current->size - 1){
    										fprintf(output, "%lf", l2.current->result[i]);
    									}
    									else fprintf(output, "%lf ", l2.current->result[i]);
    								}
    								fprintf(output, " )\n");
    							}
    							else{
    								fprintf(output, " ) = %lf\n", *l2.current->result);
    							}
    							break;
    						case 'n':
    							switch (l2.current->op){
    								case '+':
    									fprintf(output, "%lf + %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
    									break;
    								case '-':
    									fprintf(output, "%lf - %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
    									break;
    								case '*':
    									fprintf(output, "%lf * %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
    									break;
    								case '/':
    									fprintf(output, "%lf / %lf = %lf\n", *l2.current->x, *l2.current->y, *l2.current->result);
    									break;
    								case '!':
    									fprintf(output, "%lf! = %llu\n", *l2.current->x, l2.current->res);
    									break;
    								case '^':
    									fprintf(output, "%lf^%lf = %llu\n", *l2.current->x, *l2.current->y, l2.current->res);
    									break;
    							}
    					}
    				nextElement(&l2);
    			}
    		   while (l1.head != NULL){
    			   deleteElement(&l1);
    		   }
    		   while (l2.head != NULL){
    			   deleteElement(&l2);
    		   };
    		   break;
    case 'q':
    		   init_queue(&q1);
    		   init_queue(&q2);
    	   	   tmp = malloc(sizeof(element));
    	   	   while (feof(input) == 0){
    	   		   	fscanf(input," %c %c", &tmp->op, &tmp->mod);
    	   			switch (tmp->mod){
    	   				case 'n':
    	   					tmp->size = 1;
    	   					if (tmp->op == '!'){
    	   						tmp->x = malloc(sizeof(float));
    	   						for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			            tmp->y = NULL;
    	   			        }
    	   			        else{
    	   			        	tmp->x = malloc(sizeof(float));
    	   			            tmp->y = malloc(sizeof(float));
    	   			            for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			            for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->y[i]);
    	   			        }
    	   			        break;
    	   			    case 'v':
    	   			    	fscanf(input, "%i", &tmp->size);
    	   			    	tmp->x = malloc(tmp->size*sizeof(float));
    	   			        tmp->y = malloc(tmp->size*sizeof(float));
    	   			        for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->x[i]);
    	   			        for (int i = 0; i < tmp->size; i++) fscanf(input, "%f", &tmp->y[i]);
    	   			        break;
    	   			    }
    	   			enqueue(&q1, tmp);
    	   	   }
    	   	   free(tmp);
    	   	   while ((tmp = withdrawal(&q1)) != NULL){
    	   		   tmp->x = q1.tail->x;
    	   		   tmp->y = q1.tail->y;
    	   		   tmp->size = q1.tail->size;
    	   		   tmp->mod = q1.tail->mod;
    	   		   tmp->op = q1.tail->op;
    	   		   float *result;
    	   		   int p;
    	   		   unsigned long int res = 1;
    	   		   switch (tmp->mod){
    	   		   	   case 'v':
    	   		   		   switch (tmp->op){
    	   						case '+':
    	   							result = malloc(tmp->size*sizeof(float));
    	   							for (int i = 0; i < tmp->size; i++) result[i] = tmp->x[i] + tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   						case '-':
    	   							result = malloc(tmp->size*sizeof(float));
    	   							for (int i = 0; i < tmp->size; i++) result[i] = tmp->x[i] - tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   						case '*':
    	   							result = malloc(sizeof(float));
    	   							*result = 0;
    	   							for (int i = 0; i < tmp->size; i++) *result += tmp->x[i] * tmp->y[i];
    	   							tmp->result = result;
    	   							break;
    	   					}
    	   					break;
    	   				case 'n':
    	   					switch (tmp->op){
    	   						case '+':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x + *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '-':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x - *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '*':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x * *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '/':
    	   							result = malloc(1*sizeof(double));
    	   							*result = *tmp->x / *tmp->y;
    	   							tmp->result = result;
    	   							break;
    	   						case '!':
    	   							if (*tmp->x > 0) {
    	   								for (int  i = 1; i <= *tmp->x; i++) {
    	   									res *=i;
    	   								}
    	   							}
    	   							tmp->res = res;
    	   							break;
    	   						case '^':
    								p = *tmp->x;
    	   							if (p < 0)	{
    	   								p = -p;
    	   								for (int i=1; i<=*tmp->y; i++) {
    	   									res *= p;
    	   								}
    	   							res = (1/(*result));
    	   							}
    	   							else {
    	   								for (int i=1; i<=*tmp->y; i++) {
    	   									res *= p;
    	   								}
    	   							}
    	   							tmp->res = res;
    	   							break;
    	   					}
    	   					break;
    	   				}
    	   		   enqueue(&q2, tmp);
    	   	   }
    	   	   free(tmp);
    	   	   if ((output = fopen(output_name, "a")) == NULL) {
    	   		   output = fopen(output_name, "w");
    	   	   }
    			while ((tmp = withdrawal(&q2)) != NULL){
    					switch (tmp->mod){
    						case 'v':
    							fprintf(output, "( ");
    							for (int i = 0; i < tmp->size; i++){
    								if (i == tmp->size - 1){
    									fprintf(output, "%lf", tmp->x[i]);
    								}
    								else fprintf(output, "%lf ", tmp->x[i]);
    							}
    							fprintf(output, " ) %c ( ", tmp->op);
    							for (int i = 0; i < tmp->size; i++){
    								if (i == tmp->size - 1){
    									fprintf(output, "%lf", tmp->y[i]);
    								}
    								else fprintf(output, "%lf ", tmp->y[i]);
    							}
    							if (tmp->op == '+' || tmp->op == '-'){
    								fprintf(output, " ) = ( ");
    								for (int i = 0; i < tmp->size; i++){
    									if (i == tmp->size - 1){
    										fprintf(output, "%lf", tmp->result[i]);
    									}
    									else fprintf(output, "%lf ", tmp->result[i]);
    								}
    								fprintf(output, " )\n");
    							}
    							else{
    								fprintf(output, " ) = %lf\n", *tmp->result);
    							}
    							break;
    						case 'n':
    							switch (tmp->op){
    								case '+':
    									fprintf(output, "%lf + %lf = %lf\n", *tmp->x, *tmp->y, *tmp->result);
    									break;
    								case '-':
    									fprintf(output, "%lf - %lf = %lf\n", *tmp->x, *tmp->y, *tmp->result);
    									break;
    								case '*':
    									fprintf(output, "%lf * %lf = %lf\n", *tmp->x, *tmp->y, *tmp->result);
    									break;
    								case '/':
    									fprintf(output, "%lf / %lf = %lf\n", *tmp->x, *tmp->y, *tmp->result);
    									break;
    								case '!':
    									fprintf(output, "%lf! = %llu\n", *tmp->x, tmp->res);
    									break;
    								case '^':
    									fprintf(output, "%lf^%lf = %llu\n", *tmp->x, *tmp->y, tmp->res);
    									break;
    							}
    					}
    			}
    		   break;
    case 's':
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
    	          free (stack);
    	          break;
    	    }

    fclose (input);
    fclose (output);
    printf ("Работа с файлом завершена!\n");
    printf ("Хотите продолжить работу?(y/n)\n");
    scanf (" %c",&ys);
  }while (ys == 'y');

  return 0;
}
