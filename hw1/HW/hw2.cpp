// file: scanf.c
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>

int main(void)
{
	printf("�����µ��� �Ҽ��� 3���� �Է��Ͻÿ�. \n");
	double a, b, c;
	double d, e, f;
	scanf_s("%lf %lf %lf", &a, &b, &c);


	printf("ȭ�� �µ���\n");
	d = (9.0 / 5.0) * a + 32.0;
	e = (9.0 / 5.0) * b + 32.0;
	f = (9.0 / 5.0) * c + 32.0;
	printf("%.4f %.4f %.4f", d, e, f);
	printf("�Դϴ�.");

}