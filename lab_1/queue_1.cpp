#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "queue_1.h"

#define _CRT_SECURE_NO_WARNINGS 

void initQueue(Queue *const p, int m) {
	int* temp;
	temp = (int*)malloc(sizeof(int) * m);
	if (temp == NULL) { return; }
	(int *&)p->elems = temp;
	(int &)p->max = m;
	p->head = p->tail = 0;
}

void initQueue(Queue* const p, const Queue& s) {
	int counter;
	(int *&)p->elems = (int*)malloc(sizeof(int) * s.max);
	(int &)p->max = s.max;
	p->head = s.head;
	p->tail = s.tail;
	for (counter = 0; counter < s.max; counter++) {
		*(p->elems + counter) = *(s.elems + counter);
	}
}
void initQueue(Queue* const p, Queue&& s) {
	(int*&)p->elems = s.elems;
	(int&)p->max = s.max;
	p->head = s.head;
	p->tail = s.tail;
	(int *&)s.elems = 0;
	s.head = 0;
	(int &)s.max = 0;
	s.tail = 0;
}
int number(const Queue* const p) {
	if (p->max == 0) {
		return 0;
	}
	else
		return (p->tail - p->head + p->max ) % p->max;
}

int size(const Queue* const p) {
	return p->max;
}

Queue* const enter(Queue* const p, int e) {
	if ((p->tail + 1) % p->max == p->head) {
		throw("Queue is full!");
		return p;
	}
	else {
	*(p->elems + p->tail) = e;
	p->tail = (p->tail + 1) % p->max;
	return p;
	}
}

Queue* const leave(Queue* const p, int& e) {
	if (p->head == p->tail) {
		throw("Queue is empty!");
		return p;
	}
	else {
		e = *(p->elems + p->head);
		p->head = (p->head + 1) % p->max;
		return p;
	}
}

Queue* const assign(Queue* const p, Queue const& q) {
	int* temp;
	temp = (int*)malloc(sizeof(int) * q.max);
	if (temp == NULL) {
		return p;
	}
	memcpy(temp, q.elems, (q.max) * sizeof(int));
	free(p->elems);
	(int*&)p->elems = temp;
	(int&)p->max = q.max;
	p->head = q.head;
	p->tail = q.tail;
	return p;
}

Queue* const assign(Queue* const p, Queue&& q){
	if (p->elems != q.elems) {
		destroyQueue(p);
		(int*&)p->elems = q.elems;
		(int&)p->max = q.max;
		p->head = q.head;
		p->tail = q.tail;
		(int*&)q.elems = NULL;
		q.head = (int &)q.max = q.tail = 0;
		return p;
	}
	else {
		return p;
	}
	
}

char* print(const Queue* const p, char* s) {
	int tempsize = number(p);
	int count;
	int strsize = 0;
	for (count = 0; count < tempsize; count++) {
		strsize += sprintf(s + strsize  , "%d ", *(p->elems + (p->head + count) % p->max));
	}
	//printf("%s\n",s);
	return s;
}

void destroyQueue(Queue* const p) {
	if (p->elems != NULL) {
		free(p->elems);
		(int*&)p->elems = NULL;
		p->head = p->tail = 0;
		(int&)p->max = 0;
	}
	return;
}

