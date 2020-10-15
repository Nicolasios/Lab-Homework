#include <stdio.h>
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS 

extern const char* TestSTACK(int& s);

int main(void) {
	int s1 = 0;
	char const* e1 = TestSTACK(s1);
	printf("%s\n", e1);
	printf("Two Grade:%d\n", s1);
	return 0;
}
