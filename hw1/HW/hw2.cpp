// file: scanf.c
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>

int main(void)
{
	printf("섭씨온도를 소수로 3개를 입력하시오. \n");
	float a, b, c;
	scanf_s("%f %f %f", &a, &b, &c);


	printf("화씨 온도는\n");
	printf("%f\n", (9 / 5) * a + 32);
	printf("%f\n", (9 / 5) * b + 32);
	printf("%f\n", (9 / 5) * c + 32);
	printf(" 이다");

}