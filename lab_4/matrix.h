#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);							//矩阵定义
	MAT(const MAT& a);					//深拷贝构造
	MAT(MAT&& a)noexcept;				//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址
	virtual MAT operator+(const MAT& a)const;	//矩阵加法
	virtual MAT operator-(const MAT& a)const;	//矩阵减法
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
	virtual char* print(char* s)const noexcept;//输出：每列用空格隔开，每行回车结束
};
