#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int A, a;

	printf("����� ��и��� ����� ������ �Է��Ͽ���. : ");
	scanf("%d", &A);

	a = A % 360;

	if (a == 0)
		printf("���� X���Դϴ�.");
	
	else if (a > 0 && a < 90)
		printf("��1��и��Դϴ�.");

	else if (a == 90)
		printf("���� Y���Դϴ�.");

	else if (a > 90 && a < 180)
		printf("��2��и��Դϴ�.");

	else if (a == 180)
		printf("���� X���Դϴ�.");

	else if (a > 180 && a < 270)
		printf("��3��и��Դϴ�.");

	else if (a == 270)
		printf("���� Y���Դϴ�.");

	else
		printf("��4��и��Դϴ�.");

	return 0;
}