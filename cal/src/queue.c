
#include "struct.h"
#include <stdlib.h>
#include <stdio.h>


// Функция для инициализации очереди
void init_queue(queue *l) {
	l->head = NULL;
	l->tail = NULL;
}

// Функция для добавления элемента в очередь
void enqueue(queue *l, element *data) {
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

// Функция для изъятия данных из очереди
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
