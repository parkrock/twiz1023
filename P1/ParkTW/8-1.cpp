#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	char data = '*';
	char* ptrchar;
	ptrchar = &data;

	printf("������   �ּҰ�   ���尪\n");
	printf("----------------------------\n");
	printf(" data   %p     %8d\n", &data, data);
	printf("ptrchar %p     %p\n", &ptrchar, ptrchar);

	return 0;
}