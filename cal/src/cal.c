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

#include <stdio.h>
#include <stdlib.h>

// Структура для описания элемента очереди
typedef struct element{
	char op, mod;
	int size;
	float *result;
	float *x, *y;
	unsigned long long res;
	struct element *next;
} element;

// Структура для описания очереди
typedef struct queue{
	element *head;
	element *tail;
} queue;

void init_queue(queue *l) {
	l->head = NULL;
	l->tail = NULL;
}

void pushElement(queue *l, element *data) {
	element* tmp = malloc(sizeof(element));
	tmp->op = data->op;
	tmp->mod = data->mod;
	tmp->result = data->result;
	tmp->res = data->res;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->size = data->size;
	tmp->next = NULL;
	if (l->tail != NULL) {
			l->tail->next = tmp;
		}

		l->tail = tmp;

		if(l->head == NULL) {
			l->head = tmp;
		}
}
element* withdrawal(queue *q) {
	element *result;
	result = malloc(sizeof(element));

	if (q->head == NULL){
		result = NULL;
		return result;
	}

	element *tmp = q->head;

	result->mod = tmp->mod;
	result->op = tmp->op;
	result->size = tmp->size;
	result->x = tmp->x;
	result->y = tmp->y;
	result->result = tmp->result;
	result->res = tmp->res;

	//take it off.
	q->head = q->head->next;
	if (q->head == NULL) {
		q->tail = NULL;
	}
	free(tmp);

	return result;
}

int main(int argc, char *argv[]){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
   FILE *input, *output;
   char ys;
   char input_name[259],output_name[259];
   element *tmp;
   queue l1, l2;
   do{
	   init_queue(&l1);
	   init_queue(&l2);

	   //Имя файла, из которого будут читаться операции в данном случае "input.txt".
   	   printf("Введите имя файла, из которого будут читаться операции.\n");
   	   scanf("%s", input_name);
   	   //Имя файла, в который будут записываться результаты в данном случае "output.txt".
   	   printf("Введите имя файла, в который будут записываться результаты.\n");
   	   scanf("%s", output_name);
   	   input = fopen(input_name,"r");
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
   		   pushElement(&l1, tmp);
   	   }
   	   fclose(input);
   	   free(tmp);
   	   while ((tmp = withdrawal(&l1)) != NULL){
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
   	   }
   	   free(tmp);
   	   if ((output = fopen(output_name, "a")) == NULL) {
   		   output = fopen(output_name, "w");
   	   }
		while ((tmp = withdrawal(&l2)) != NULL){
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
	   fclose(output);
	   printf("Работа с файлом завершена!\n");
	   printf("Хотите продолжить работу?(y/n)\n");
	   scanf(" %c",&ys);
   }while(ys=='y');
   return 0;
}
