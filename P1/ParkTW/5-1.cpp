#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int a, b;
	int share, reminder;
	printf("�� ���� �Է��Ͽ���: ");
	scanf("%d %d", &a, &b);

	if (a > b)
		printf("���� %d �̰�, �������� %d �̴�.", a / b, a % b);
	else
		printf("���� %d �̰�, �������� %d �̴�.", b / a, b % a);

}