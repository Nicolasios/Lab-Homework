#include "matrix.h"

//class MAT {
//	T* const e;							//指向所有整型矩阵元素的指针
//	const int r, c;							//矩阵的行r和列c大小
//public:
//	MAT(int r, int c);							//矩阵定义
//	MAT(const MAT& a);					//深拷贝构造
//	MAT(MAT&& a)noexcept;				//移动构造
//	virtual ~MAT()noexcept;
//	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址
//	virtual MAT operator+(const MAT& a)const;	//矩阵加法
//	virtual MAT operator-(const MAT& a)const;	//矩阵减法
//	virtual MAT operator*(const MAT& a)const;	//矩阵乘法
//	virtual MAT operator~()const;					//矩阵转置
//	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
//	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
//	virtual MAT& operator+=(const MAT& a);		//“+=”运算
//	virtual MAT& operator-=(const MAT& a);		//“-=”运算
//	virtual MAT& operator*=(const MAT& a);		//“*=”运算
//	virtual char* print(char* s)const noexcept;//输出：每列用空格隔开，每行回车结束
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