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
* 对于STACK(const STACK& s)深拷贝构造函数，在用已经存在的对象s深拷贝构造新对象时，
* 新对象不能共用s的基类和成员q为elems分配的内存，
* 新对象要为其基类和成员q的elems分配和s为其基类和成员q的elems分配的同样大小的内存，
* 并且将s相应的elems的内容深拷贝至新对象为对应elems分配的内存；
* 新对象应设置其基类和成员q的max、head、tail和s的对应值相同。
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
	//返回队列的实际元素个数
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
	//返回队列申请的最大元素个数max
}		
QUEUE& QUEUE::operator<<(int e) {
	//将e入队列尾部，并返回当前队列
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
	//从队首出元素到e，并返回当前队列
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
	//深拷贝赋值并返回被赋值队列
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
	//移动赋值并返回被赋值队列
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
	//打印队列至s尾部并返回s：s[0]=’\0’
	int tempsize = (int)*this;
	int count;
	int strsize = 0;
	for (count = 0; count < tempsize; count++) {
		strsize += sprintf(s + strsize, "%d ", *(elems + (head + count) % max));
	}
	return s;

}
QUEUE::~QUEUE() {
	//销毁当前队列
		(int&)max = 0;
		head = 0;
		tail = 0;
	if (elems!=NULL){
		free(elems);
		(int*&)elems = NULL;
	}
}	 				

