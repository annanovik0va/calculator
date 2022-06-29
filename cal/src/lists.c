
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"


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

