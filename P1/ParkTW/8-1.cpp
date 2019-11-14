#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	char data = '*';
	char* ptrchar;
	ptrchar = &data;

	printf("변수명   주소값   저장값\n");
	printf("----------------------------\n");
	printf(" data   %p     %8d\n", &data, data);
	printf("ptrchar %p     %p\n", &ptrchar, ptrchar);

	return 0;
}