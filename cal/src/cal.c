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

// Структура для описания элемента списка
typedef struct element{
	char op, mod;
	int size;
	float *result;
	float *x, *y;
	unsigned long long res;
	struct element *next;
} element;

// Структура для описания списка
typedef struct list{
	element *head;
	element *current;
} list;

void init_list(list *l) {
	l->head = NULL;
	l->current = NULL;
}

void pushElement(list *l, element *data) {
	element* tmp = malloc(sizeof(element));
	element *last = l->head;
	tmp->op = data->op;
	tmp->mod = data->mod;
	tmp->result = data->result;
	tmp->res = data->res;
	tmp->x = data->x;
	tmp->y = data->y;
	tmp->size = data->size;
	tmp->next = NULL;
	if(l->head == NULL){
		l->head = tmp;
		return;
	}
	while (last->next != NULL){
		last = last->next;
	}
	last->next = tmp;
	return;
}

void deleteElement(list *l) {
  element *tmp;

  if(&l->head == NULL) return;

  tmp = l->head;
  l->head = l->head->next;
  free(tmp);
}

element* nextElement(list *l){
	l->current = l->current->next;
	return l->current;
}


int main(int argc, char *argv[]){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
   FILE *input, *output;
   char ys;
   char input_name[259],output_name[259];
   element *tmp;
   list l1, l2;
   do{
	   init_list(&l1);
	   init_list(&l2);

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
   			tmp->next = NULL;
   		   pushElement(&l1, tmp);
   	   }
   	   fclose(input);
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
	   fclose(output);
	   while (l1.head != NULL){
		   deleteElement(&l1);
	   }
	   while (l2.head != NULL){
		   deleteElement(&l2);
	   }
	   printf("Работа с файлом завершена!\n");
	   printf("Хотите продолжить работу?(y/n)\n");
	   scanf(" %c",&ys);
   }while(ys=='y');
   return 0;
}
