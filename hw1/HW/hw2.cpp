// file: scanf.c
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>

int main(void)
{
	printf("�����µ��� �Ҽ��� 3���� �Է��Ͻÿ�. \n");
	float a, b, c;
	scanf_s("%f %f %f", &a, &b, &c);


	printf("ȭ�� �µ���\n");
	printf("%f\n", (9 / 5) * a + 32);
	printf("%f\n", (9 / 5) * b + 32);
	printf("%f\n", (9 / 5) * c + 32);
	printf(" �̴�");

}