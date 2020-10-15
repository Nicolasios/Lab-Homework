#include "matrix.h"

//class MAT {
//	T* const e;							//ָ���������;���Ԫ�ص�ָ��
//	const int r, c;							//�������r����c��С
//public:
//	MAT(int r, int c);							//������
//	MAT(const MAT& a);					//�������
//	MAT(MAT&& a)noexcept;				//�ƶ�����
//	virtual ~MAT()noexcept;
//	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ
//	virtual MAT operator+(const MAT& a)const;	//����ӷ�
//	virtual MAT operator-(const MAT& a)const;	//�������
//	virtual MAT operator*(const MAT& a)const;	//����˷�
//	virtual MAT operator~()const;					//����ת��
//	virtual MAT& operator=(const MAT& a);		//�����ֵ����
//	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
//	virtual MAT& operator+=(const MAT& a);		//��+=������
//	virtual MAT& operator-=(const MAT& a);		//��-=������
//	virtual MAT& operator*=(const MAT& a);		//��*=������
//	virtual char* print(char* s)const noexcept;//�����ÿ���ÿո������ÿ�лس�����
//};


MAT<T>::MAT(int r,int c) {
	(int&)this->r = r;
	(int&)this->e = e;
	(T*&)e = (int*)malloc(sizeof(int) * r * c);
}
MAT<T>::MAT(const MAT& a){
	(int&)this->r = a.r;
	(int&)this->e = a.e;
	(T*&)e = (int*)malloc(sizeof(int) * a.r * a.c);
	memcpy(e, a.e, a.r * a.c);
}

MAT<T>::MAT(MAT&& a){
	(int&)this->r = a.r;
	(int&)this->c = a.c;
	(int*&)this->e = a.e;
	(int&)a.r = 0;
	(int&)a.c = 0;
	(T*&)a.e = NULL;
}

T* const MAT<T>::operator[](int r) {
	return (T*)(e + r * c);
}

MAT MAT<T>::operator+=(const MAT& a) {
	int counter;
	if (a.c != c || a.r != r) {
		return *this;
	}
	else {
		for (counter = 0; counter < r * c; counter++) {
			*(e + counter) += *(a.e + counter);
		}
		return *this;
	}
}
MAT MAT<T>::operator+(const MAT& a) const{
	int counter;
	MAT sum(a.r, a.c);
	if (a.c != c || a.r != r) {
		return *this;
	}
	else {
		for (counter = 0; counter < r * c; counter++) {
			*(sum.e + count) = *(e + counter) + *(a.e + counter);
		}
		return sum;
	}
}
MAT MAT<T>::operator-(const MAT& a) const {
	int counter;
	MAT sum(a.r, a.c);
	if (a.c != c || a.r != r) {
		return *this;
	}
	else {
		for (counter = 0; counter < r * c; counter++) {
			*(sum.e + count) = *(e + counter) - *(a.e + counter);
		}
		return sum;
	}
}

MAT MAT<T>::operator-=(const MAT& a) {
	int counter;
	if (a.c != r || a.r != c) {
		return *this;
	}
	else {
		for (counter = 0; counter < r * c; counter++) {
			*(e + counter) -= *(a.e + counter);
		}
		return *this;
	}
}

Mat MAT<T>::operator*(const MAT& a) {
	int result,;
	if (c!=a.r) {
		return *this;
	}
	else
	{
		result = 0;
		for()
	}
}

MAT MAT<T>::operator=(const MAT& a):r(a.r),c(a.c) {
	if (e)free(e);
	(T*&)e = (T*)malloc(sizeof(T) * a.c * a, r);
	memcpy(e, a.e, a.r * a.c);
	return *this;
}

MAT MAT<T>::operator=(MAT&& a) : r(a.r), c(a.c) {
	if (e)free(e);
	(T*&)e = a.e;
	a.e = NULL;
	a.c = 0;
	a.r = 0;
	return *this;
}