#include <stdio.h>
#pragma warning(disable:4996)

double change(int a);

int main()
{
	double inch;
	printf("인치를 입력하세요: ");
	scanf("%lf", &inch);
	printf("%f인치는 %.2fcm입니다.\n", inch, change(inch));

	return 0;
}

double change(int a)
{
	double cm;
	cm = (a * 2.54);
	return (cm);
}