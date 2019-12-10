#include <stdio.h>
#pragma warning(disable:4996)

int intpow(int a, int b);

int main()
{
	int m, n;
	printf("두 개의 정수를 입력하세요: ");
	scanf("%d%d", &m, &n);
	printf("함수의 결과는 %d입니다.\n", intpow(m, n));

	return 0;
}

int intpow(int a, int b)
{
	int mn = 0;
	mn = a * b;

	return mn;
}