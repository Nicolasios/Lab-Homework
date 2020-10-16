#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//ָ���������;���Ԫ�ص�ָ��
	const int r, c;							//�������r����c��С
public:
	MAT(int r, int c);							//������
	MAT(const MAT& a);					//�������
	MAT(MAT&& a)noexcept;				//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ
	virtual MAT operator+(const MAT& a)const;	//����ӷ�
	virtual MAT operator-(const MAT& a)const;	//�������
	virtual MAT operator*(const MAT& a)const;	//����˷�
	virtual MAT operator~()const;					//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
	virtual char* print(char* s)const noexcept;//�����ÿ���ÿո������ÿ�лس�����
};

template <typename T>
MAT<T>::MAT(int r, int c) :r(r), c(c), e((T*)malloc(sizeof(T)* r* c)) {
}

template <typename T>
MAT<T>::MAT(const MAT& a) : r(a.r), c(a.c), e((T*)malloc(sizeof(T)* a.r* a.c)) {
	memcpy(e, a.e, sizeof(T) * a.r * a.c);
}

template <typename T>
MAT<T>::MAT(MAT&& a)noexcept:r(a.r), c(a.c), e(a.e) {
	(int&)a.r = 0;
	(int&)a.c = 0;
	(T*&)a.e = NULL;
}

template <typename T>
MAT<T>::~MAT() {
	if (e != NULL) {
		free(e);
		(T*&)e = NULL;
	}
}

template <typename T>
T* const MAT<T>::operator[ ](int r) {
	if (r < 0 || r >= this->r)
		throw "flow out!";
	return (T*)(e + r * c);
}

//+�����Ϊ��Ԫ�����
template <typename T>
MAT<T> MAT<T>::operator+(const MAT& a) const {
	if (r != a.r || c != a.c)
		throw "Canot add!";
	MAT<T> ret(r, c);
	for (int i = 0; i < r * c; i++)
		(ret.e)[i] = e[i] + (a.e)[i];
	return ret;
}

//-�����Ϊ��Ԫ�����
template <typename T>
MAT<T> MAT<T>::operator-(const MAT& a) const {
	int counter;
	MAT sum(a.r, a.c);
	if (a.c != c || a.r != r) {
		throw "Cannot sub!";
	}
	else {
		for (counter = 0; counter < r * c; counter++) {
			*(sum.e + counter) = *(e + counter) - *(a.e + counter);
		}
		return sum;
	}
}

//*�����Ϊ��Ԫ�����
template <typename T>
MAT<T> MAT<T>::operator*(const MAT& a) const {
	//ԭ����lowһ��
	int hang, lie, temp;
	int sum;
	if (c != a.r) {
		throw "Cannot multiply!";
	}
	MAT<T> res(r, a.c);
	for (hang = 0; hang < r; hang++) {
		for (lie = 0; lie < a.c; lie++) {
			sum = 0;
			for (temp = 0; temp < c; temp++) {
				sum += e[hang * c + temp] * a.e[temp * c + lie];
			}
			res.e[hang * a.c + lie] = sum;
		}
	}
	return res;
}

//~�����Ϊ��Ŀ�����
//��r x c�ľ���ת��Ϊc x r�ľ���
//ʵ�ֶԽǸ�ֵ
template <typename T>
MAT<T> MAT<T>::operator~() const {
	MAT<T> res(c, r);
	int hang, lie;
	for (hang = 0; hang < r; hang++) {
		for (lie = 0; lie < c; lie++) {
			res.e[lie * r + hang] = e[hang * c + lie];
		}
	}
	return res;
}


template <typename T>
MAT<T>& MAT<T>::operator=(const MAT& a){
	if (this == &a) {
		return *this;
	}
	if (r != a.r || c != a.c) {
		throw "cant deep copy!";
	}
	if (e)free(e);
	(T*&)e = (T*)malloc(sizeof(T) * a.c * a.r);
	memcpy(e, a.e, sizeof(T) * a.r * a.c);
	(int&)r = a.r;
	(int&)c = a.c;
	return *this;
}


template<typename T>
MAT<T>& MAT<T>::operator=(MAT&& a) noexcept { 
	if (this == &a)
		return *this;
	if (e != NULL)
		free(e);
	(T*&)e = a.e;
	(int&)r = a.r;
	(int&)c = a.c;
	(T*&)(a.e) = NULL;
	(int&)(a.r) = 0;
	(int&)(a.c) = 0;
	return *this;
}


template <typename T>
MAT<T>&  MAT<T>::operator+=(const MAT& a) {
	*this = *this + a;
	return *this;

}


template <typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) {
	*this = *this - a;
	return *this;
}

template <typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a) {
	*this = (*this) * a;
	return *this;
}

//����Ϊ��Ӧ��ͬ������ֵ���ͣ���ӡ�ĳ��Ȳ�һ��
int printValue(char* s, int value, int counter) {
	counter += sprintf(s + counter, "%6ld ", value);
	return counter;
};

int printValue(char* s, long long value, int counter) {
	counter += sprintf(s + counter, "%6lld ", value);
	return counter;
};

int printValue(char* s, float value, int counter) {
	counter += sprintf(s + counter, "%8f ", value);
	return counter;
};

int printValue(char* s, long float value, int counter) {
	counter += sprintf(s + counter, "%8lf ", value);
	return counter;
};

template <typename T>
char* MAT<T>::print(char* s)const noexcept {
	int strlen = 0, counter1, counter2;
	for (counter1 = 0; counter1 < r; counter1++) {
		for (counter2 = 0; counter2 < c; counter2++) {
			strlen = printValue(s, e[counter1 * c + counter2], strlen);
		}
		strlen += sprintf(s + strlen, "%c", '\n');
	}
	return s;
}

