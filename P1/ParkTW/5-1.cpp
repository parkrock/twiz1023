#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a, b;
	int share, reminder;
	printf("두 수를 입력하여라: ");
	scanf("%d %d", &a, &b);

	if (a > b)
		printf("몫은 %d 이고, 나머지는 %d 이다.", a / b, a % b);
	else
		printf("몫은 %d 이고, 나머지는 %d 이다.", b / a, b % a);

}