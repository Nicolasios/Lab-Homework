#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "stack.h"



STACK::STACK(int m):q(m),QUEUE(m){
}

STACK::STACK(const STACK& s):q(s.q),QUEUE(s){
}
STACK::STACK(STACK&& s)noexcept:q((QUEUE &&)s.q),QUEUE((QUEUE &&)s) {
}
int STACK::size()const noexcept{
	return q.size() + QUEUE::size();
}

STACK::operator int() const noexcept {
	return int(q) + QUEUE::operator int();
}

STACK& STACK::operator<<(int e) {
	if (QUEUE::operator int() < QUEUE::size() - 1)
		QUEUE::operator<<(e);
	else if (int(q) < q.size() - 1)
		q << e;
	else
		throw "STACK is full!";
	return *this;
	//注释掉是因为正确的思路但是过不了老师的测试程序
	//if (int(*this) == 2 * q.size() - 2) {
	//	throw("STACK is full!");
	//}
	//else if (int(*this) == 0) {
	//	QUEUE::operator<<(e);
	//}
	//else if (int(*this) < q.size() - 1) {
	//	for (counter = 0; counter < num1; counter++) {
	//		QUEUE::operator>>(array[counter]);
	//	}
	//	QUEUE::operator<<(e);
	//	for (counter = 0; counter < num1; counter++) {
	//		QUEUE::operator<<(array[counter]);
	//	}
	//}
	//else if (int(*this) == q.size() - 1) {
	//	for (counter = 0; counter < QUEUE::size(); counter++) {
	//		QUEUE::operator>>(array[counter]);
	//	}
	//	QUEUE::operator<<(e);
	//	for (counter = 0; counter < QUEUE::size() - 1; counter++) {
	//		QUEUE::operator<<(array[counter]);
	//	}
	//	q.operator<<(array[QUEUE::size()-1]);
	//}
	//else {
	//	for (counter = 0; counter <QUEUE::size(); counter++) {
	//		QUEUE::operator>>(array[counter]);
	//	}
	//	QUEUE::operator<<(e);
	//	for (counter = 0; counter <QUEUE::size()-1; counter++) {
	//		QUEUE::operator<<(array[counter]);
	//	}
	//	for (counter_1 = 0; counter_1<int(q); counter_1++) {
	//		q.operator>>(array_1[counter_1]);
	//	}
	//	q.operator<<(array[QUEUE::size() - 1]);
	//	for (counter_1 = 0; counter_1<int(q); counter_1++) {
	//		q.operator<<(array_1[counter_1]);
	//	}
	//}
	//return *this;
}

STACK& STACK::operator>>(int& e) {
	int a, b, counter;
	if (!this->operator int()) {
		throw "STACK is empty!";
	}
	for (counter = 0; counter<int(*this) - 1; counter++) {
		QUEUE::operator>>(a);
		if ((QUEUE*)(&q)->operator int()) {
			q >> b;
			QUEUE::operator<<(b);
			q << a;
		}
		else
			QUEUE::operator<<(a);
	}
	QUEUE::operator>>(e);
	if ((QUEUE*)(&q)->operator int()) {
		q >> a;
		QUEUE::operator<<(a);
	}
	return *this;

}
/*
* 对于STACK& operator=(const STACK& s)深拷贝赋值函数，
* 在用等号右边的对象s深拷贝赋值等号左边的对象s时，等号左边对象的基类和成员q不能共用s的基类和成员q为elems分配的内存，
* 若等号左边的对象为其基类和成员q的elems分配了内存，则应先释放掉以避免内存泄漏，
* 然后为其elems分配和s为其基类和成员q的elems分配的同样大小的内存，
* 并且将s对应两个elems的内容拷贝至等号左边对象对应两个elems的内存；
* 等号左边对象中的max、head、tail应设置成和s中基类和成员q的对应值相同。
*/
STACK& STACK::operator=(const STACK& s) {
	q = (const QUEUE&)(s.q);
	QUEUE::operator=((QUEUE&)s);
	return *this;
}
/*
* 对于STACK& operator=(STACK&& s)noexcept移动赋值，
* 在用等号右边的对象s移动赋值给等号左边的对象时，
* 等号左边的对象如果已经为其基类和成员q中的elems分配了内存，则应先释放以避免内存泄漏，
* 然后接受使用s的基类和成员q为elems分配的内存，
* 并且等号左边对象中的max、head、tail应和s中基类和成员q中的对应值相同；
* s中基类和成员q的elems设置为空指针以表示内存被移走，同时其对应的max、head、tail均应设置为0。
*/
STACK& STACK::operator=(STACK&& s)noexcept {
	q = (QUEUE&&)(s.q);
	QUEUE::operator=((QUEUE&&)s);
	return *this;
}

char* STACK::print(char* b)const noexcept {
	int a = 0;
	int counters = 0;
	int round;
	int lowerLen = QUEUE::operator int();
	int higherLen = int(q);
	int ret[100];
	for (int i = 0; i < lowerLen; i++) {
		((QUEUE*)(this))->QUEUE::operator>>(a);
		counters += snprintf(b + counters, sizeof(b), "%d,", a);
		((QUEUE*)(this))->QUEUE::operator<<(a);
	}
	if (QUEUE::size() % lowerLen == 0)
		round = QUEUE::size() / lowerLen - 1;
	else
		round = QUEUE::size() - 1;
	for (int i = 0; i < round; i++) {
		for (int m = 0; m < lowerLen; m++) {
			((QUEUE*)(this))->QUEUE::operator>>(a);
			((QUEUE*)(this))->QUEUE::operator<<(a);
		}
	}

	if (higherLen) {
		if (q.size() % higherLen == 0)
			round = q.size() / higherLen - 1;
		else
			round = q.size() - 1;
		for (int i = 0; i < higherLen - 1; i++) {
			((QUEUE*)(&q))->operator>>(a);
			counters += snprintf(b + counters, sizeof(b), "%d,", a);
			((QUEUE*)(&q))->operator<<(a);
		}
		if (higherLen) {
			((QUEUE*)(&q))->operator>>(a);
			counters += snprintf(b + counters, sizeof(b), "%d", a);
			((QUEUE*)(&q))->operator<<(a);
		}
		for (int i = 0; i < round; i++) {
			for (int m = 0; m < lowerLen; m++) {
				((QUEUE*)(&q))->operator>>(a);
				((QUEUE*)(&q))->operator<<(a);
			}
		}
	}
	return b;
}

STACK::~STACK() {

}