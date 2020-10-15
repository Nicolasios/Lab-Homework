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
	//ע�͵�����Ϊ��ȷ��˼·���ǹ�������ʦ�Ĳ��Գ���
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
* ����STACK& operator=(const STACK& s)�����ֵ������
* ���õȺ��ұߵĶ���s�����ֵ�Ⱥ���ߵĶ���sʱ���Ⱥ���߶���Ļ���ͳ�Աq���ܹ���s�Ļ���ͳ�ԱqΪelems������ڴ棬
* ���Ⱥ���ߵĶ���Ϊ�����ͳ�Աq��elems�������ڴ棬��Ӧ���ͷŵ��Ա����ڴ�й©��
* Ȼ��Ϊ��elems�����sΪ�����ͳ�Աq��elems�����ͬ����С���ڴ棬
* ���ҽ�s��Ӧ����elems�����ݿ������Ⱥ���߶����Ӧ����elems���ڴ棻
* �Ⱥ���߶����е�max��head��tailӦ���óɺ�s�л���ͳ�Աq�Ķ�Ӧֵ��ͬ��
*/
STACK& STACK::operator=(const STACK& s) {
	q = (const QUEUE&)(s.q);
	QUEUE::operator=((QUEUE&)s);
	return *this;
}
/*
* ����STACK& operator=(STACK&& s)noexcept�ƶ���ֵ��
* ���õȺ��ұߵĶ���s�ƶ���ֵ���Ⱥ���ߵĶ���ʱ��
* �Ⱥ���ߵĶ�������Ѿ�Ϊ�����ͳ�Աq�е�elems�������ڴ棬��Ӧ���ͷ��Ա����ڴ�й©��
* Ȼ�����ʹ��s�Ļ���ͳ�ԱqΪelems������ڴ棬
* ���ҵȺ���߶����е�max��head��tailӦ��s�л���ͳ�Աq�еĶ�Ӧֵ��ͬ��
* s�л���ͳ�Աq��elems����Ϊ��ָ���Ա�ʾ�ڴ汻���ߣ�ͬʱ���Ӧ��max��head��tail��Ӧ����Ϊ0��
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