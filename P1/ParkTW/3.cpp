#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int A, a;

	printf("평면의 사분면을 출력할 각도를 입력하여라. : ");
	scanf("%d", &A);

	a = A % 360;

	if (a == 0)
		printf("양의 X축입니다.");
	
	else if (a > 0 && a < 90)
		printf("제1사분면입니다.");

	else if (a == 90)
		printf("양의 Y축입니다.");

	else if (a > 90 && a < 180)
		printf("제2사분면입니다.");

	else if (a == 180)
		printf("음의 X축입니다.");

	else if (a > 180 && a < 270)
		printf("제3사분면입니다.");

	else if (a == 270)
		printf("음의 Y축입니다.");

	else
		printf("제4사분면입니다.");

	return 0;
}