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
