#include <stdio.h>
#include "queue_2.h"
#define _CRT_SECURE_NO_WARNINGS 

extern const char* TestQUEUE(int& s);

int main(void) {
	int s1 = 0;
	char const* e1 = TestQUEUE(s1);
	printf("%s\n", e1);
	printf("Two Grade:%d\n", s1);
	return 0;
}
