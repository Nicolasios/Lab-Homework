#include <stdio.h>
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS 

template MAT<int>;
template MAT<long long>;
extern const char* TestMAT(int& s);

int main(void) {
	int s1 = 0;
	char const* e1 = TestMAT(s1);
	printf("%s\n", e1);
	printf("Four Grade:%d\n", s1);
	return 0;
}
