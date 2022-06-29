
#ifndef STRUCT_H_
#define STRUCT_H_

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

// Структура для описания очереди
typedef struct queue{
	element *head;
	element *tail;
} queue;

//Элемент стека
struct StackElement{
  double element;
  struct StackElement *next;
};

struct Stack
{
  struct StackElement *tail;
};


#endif /* STRUCT_H_ */
