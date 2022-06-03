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

FILE *input, *output;

struct element{
	char op, mod;
	int size;
	float *x, *y;
	struct element *next;
};

struct resElement{
	int size;
	float *result;
	unsigned long long res;
	struct resElement *next;
};

typedef struct element element;
typedef struct resElement resElement;

void pushElement(element** head){
	element* tmp = (element*) malloc(sizeof(element));
	element *last = *head;
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

	if(*head == NULL){
		*head = tmp;
		return;
	}

	while (last->next != NULL){
		last = last->next;
	}
	last->next = tmp;
	return;
}

void pushResult(resElement** head, char op, int size, float *result, unsigned long int res){
	resElement* tmp = (resElement*) malloc(sizeof(resElement));
	resElement *last = *head;
	tmp->size = size;
	if (op == '!' || op == '^'){
		tmp->res = res;
	}
	else{
		tmp->result = result;
	}
	tmp->next = NULL;
	if(*head == NULL){
		*head = tmp;
		return;
	}

	while (last->next != NULL){
		last = last->next;
	}

	last->next = tmp;
	return;
}

void deleteElement(element **head) {
  element *tmp;

  if(head == NULL || *head == NULL) return;

  tmp = *head;

  *head = (*head)->next;

  free(tmp);
}

void deleteResult(resElement **head){
	resElement *tmp;

	if(head == NULL || *head == NULL) return;

	tmp = *head;

	*head = (*head)->next;

	free(tmp);
}

element* nextElement(element *current){
	return current->next;
}

resElement* nextResult(resElement *current){
	return current->next;
}


int main(int argc, char *argv[]){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
   char ys;
   element* head; // Указатель на голову списка данных
   element* current; // Указатель на текущий элемент списка данных
   resElement* resHead; // Указатель на голову списка результата
   resElement* resCurrent; // Указатель на текущий элемент списка результата
   do{
	   head = NULL;
	   current = NULL;
	   resHead = NULL;
	   resCurrent = NULL;
	   char input_name[259],output_name[259];
	   //Имя файла, из которого будут читаться операции в данном случае "input.txt".
   	   printf("Введите имя файла, из которого будут читаться операции.\n");
   	   scanf("%s", input_name);
   	   //Имя файла, в который будут записываться результаты в данном случае "output.txt".
   	   printf("Введите имя файла, в который будут записываться результаты.\n");
   	   scanf("%s", output_name);
   	   input = fopen(input_name,"r");
   	   while (feof(input) == 0){
   		   pushElement(&head);
   	   }
   	   fclose(input);
   	   current = head;
   	   while (current != NULL){
   		   float *result;
   		   int p;
   		   unsigned long int res = 1;
   		   switch (current->mod){
   		   	   case 'v':
   		   		   switch (current->op){
   						case '+':
   							result = malloc(current->size*sizeof(float));
   							for (int i = 0; i < current->size; i++) result[i] =  current->x[i] + current->y[i];
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '-':
   							result = malloc(current->size*sizeof(float));
   							for (int i = 0; i < current->size; i++) result[i] =  current->x[i] - current->y[i];
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '*':
   							result = malloc(sizeof(float));
   							*result = 0;
   							for (int i = 0; i < current->size; i++) *result +=  current->x[i] * current->y[i];
   							pushResult(&resHead, current->op, 1, result, 0);
//   							free(result);
   							break;
   					}
   					break;
   				case 'n':
   					switch (current->op){
   						case '+':
   							result = malloc(1*sizeof(double));
   							*result = *current->x + *current->y;
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '-':
   							result = malloc(1*sizeof(double));
   							*result = *current->x - *current->y;
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '*':
   							result = malloc(1*sizeof(double));
   							*result = *current->x * *current->y;
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '/':
   							result = malloc(1*sizeof(double));
   							*result = *current->x / *current->y;
   							pushResult(&resHead, current->op, current->size, result, 0);
//   							free(result);
   							break;
   						case '!':
   							if (*current->x > 0){
   								for (int  i = 1; i <= *current->x; i++) {
   									res *=i;
   								}
   							}
   							pushResult(&resHead, current->op, current->size, 0, res);
   							break;
   						case '^':
							p = *current->x;
   							if (p < 0)	{
   								p = -p;
   								for (int i=1; i<=p; i++) {
   									res *= p;
   								}
   							res = (1/(*result));
   							}
   							else {
   								for (int i=1; i<=p; i++) {
   									res *= p;
   								}
   							}
   							pushResult(&resHead, current->op, current->size, 0, res);
   							break;
   					}
   					break;
   				}
   		   current = nextElement(current);
   	   }
   	   current = head;
   	   resCurrent = resHead;
   	   if ((output = fopen(output_name, "a")) == NULL) {
   		   output = fopen(output_name, "w");
   	   }
		while (current != NULL){
				switch (current->mod){
					case 'v':
						fprintf(output, "( ");
						for (int i = 0; i < current->size; i++){
							if (i == current->size - 1){
								fprintf(output, "%lf", current->x[i]);
							}
							else fprintf(output, "%lf ", current->x[i]);
						}
						fprintf(output, " ) %c ( ", current->op);
						for (int i = 0; i < current->size; i++){
							if (i == current->size - 1){
								fprintf(output, "%lf", current->y[i]);
							}
							else fprintf(output, "%lf ", current->y[i]);
						}
						if (current->op == '+' || current->op == '-'){
							fprintf(output, " ) = ( ");
							for (int i = 0; i < resCurrent->size; i++){
								if (i == resCurrent->size - 1){
									fprintf(output, "%lf", resCurrent->result[i]);
								}
								else fprintf(output, "%lf ", resCurrent->result[i]);
							}
							fprintf(output, " )\n");
						}
						else{
							fprintf(output, " ) = %lf\n", *resCurrent->result);
						}
						break;
					case 'n':
						switch (current->op){
							case '+':
								fprintf(output, "%lf + %lf = %lf\n", *current->x, *current->y, *resCurrent->result);
								break;
							case '-':
								fprintf(output, "%lf - %lf = %lf\n", *current->x, *current->y, *resCurrent->result);
								break;
							case '*':
								fprintf(output, "%lf * %lf = %lf\n", *current->x, *current->y, *resCurrent->result);
								break;
							case '/':
								fprintf(output, "%lf / %lf = %lf\n", *current->x, *current->y, *resCurrent->result);
								break;
							case '!':
								fprintf(output, "%lf! = %llu\n", *current->x, resCurrent->res);
								break;
							case '^':
								fprintf(output, "%lf^%lf = %llu\n", *current->x, *current->y, resCurrent->res);
								break;
						}
				}
			current = nextElement(current);
			resCurrent = nextResult(resCurrent);
		}
	   fclose(output);
	   while (head != NULL){
	   		deleteElement(&head);
	   	}
	   	while (resHead != NULL){
	   		deleteResult(&resHead);
	   	}
	   printf("Работа с файлом завершена!\n");
	   printf("Хотите продолжить работу?(y/n)\n");
	   scanf(" %c",&ys);
   }while(ys=='y');
   return 0;
}
