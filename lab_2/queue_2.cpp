#include<stdio.h>
#include <string.h>
#include <malloc.h>
#include"queue_2.h"

QUEUE::QUEUE(int m) :elems(NULL),max(0),tail(0),head(0){
	(int*&)elems = (int*)malloc(sizeof(int)*m);
	(int&)max = m;
	head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) :elems(NULL),max(0),tail(0),head(0){
	int counter;
	(int*&)elems = (int*)malloc(sizeof(int) * q.max);
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	for (counter = 0; counter < q.max; counter++) {
		*(elems + counter) = *(q.elems + counter);
	}
}
/*
* ����STACK(const STACK& s)������캯���������Ѿ����ڵĶ���s��������¶���ʱ��
* �¶����ܹ���s�Ļ���ͳ�ԱqΪelems������ڴ棬
* �¶���ҪΪ�����ͳ�Աq��elems�����sΪ�����ͳ�Աq��elems�����ͬ����С���ڴ棬
* ���ҽ�s��Ӧ��elems������������¶���Ϊ��Ӧelems������ڴ棻
* �¶���Ӧ���������ͳ�Աq��max��head��tail��s�Ķ�Ӧֵ��ͬ��
*/
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(NULL), max(0), tail(0), head(0) {
	(int*&)elems = q.elems;
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	(int&)q.max = q.head = q.tail = 0;
	(int*&)q.elems = NULL;
}
QUEUE::operator int() const noexcept {
	//���ض��е�ʵ��Ԫ�ظ���
	if (max == 0) {
		return 0;
	}
	else
	{
		return (tail - head + max) % max;
	}
}	
int QUEUE::size() const noexcept {
	return max;
	//���ض�����������Ԫ�ظ���max
}		
QUEUE& QUEUE::operator<<(int e) {
	//��e�����β���������ص�ǰ����
	if ((tail + 1) % max == head) {
		throw("QUEUE is full!");
	}
	else
	{
		*(elems + tail) = e;
		tail = (tail + 1) % max;
		return *this;
	}
}	
QUEUE& QUEUE::operator>>(int& e) {
	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
	if (head == tail) {
		throw("QUEUE is empty!");
		return  *this;
	}
	else
	{
		e = *(elems + head);
		head = (head + 1) % max;
		return *this;
	}
}	
QUEUE& QUEUE::operator=(const QUEUE& q) {
	//�����ֵ�����ر���ֵ����
	if (this == &q)
		return *this;
	if (elems != NULL)
		free(elems);
	void* p = malloc(sizeof(int) * q.max);
	if (p == 0)
		return *this;
	memcpy(p, q.elems, sizeof(int) * q.max);
	(int*&)elems = (int*)p;
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	return *this;

}
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {
	//�ƶ���ֵ�����ر���ֵ����
	if (this == &q)
		return *this;
	if (elems != NULL)
		free(elems);
	(int*&)elems = q.elems;
	(int&)max = q.max;
	head = q.head;
	tail = q.tail;
	(int*&)(q.elems) = NULL;
	(int&)(q.max) = 0;
	q.head = 0;
	q.tail = 0;
	return *this;
	
}
char* QUEUE::print(char* s) const noexcept {
	//��ӡ������sβ��������s��s[0]=��\0��
	int tempsize = (int)*this;
	int count;
	int strsize = 0;
	for (count = 0; count < tempsize; count++) {
		strsize += sprintf(s + strsize, "%d ", *(elems + (head + count) % max));
	}
	return s;

}
QUEUE::~QUEUE() {
	//���ٵ�ǰ����
		(int&)max = 0;
		head = 0;
		tail = 0;
	if (elems!=NULL){
		free(elems);
		(int*&)elems = NULL;
	}
}	 				

