#include <stdio.h>
#include "queue_1.h"
#define _CRT_SECURE_NO_WARNINGS 


extern const char* TestQueue(int& s);

int main(void) {
	int s1 = 0;
	char const* e1 = TestQueue(s1);
	printf("%s\n", e1);
	printf("One Grade:%d\n", s1);
	return 0;
}
