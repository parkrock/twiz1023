#include <stdio.h>

int main(void)
{
	int n = 6527;
	printf("4�ڸ� ���� �Է�: 6527\n");

	printf("%10d\n", n);
	printf("%010d\n", n);
	printf("%+010d\n", n);
	printf("%d\n", n);
	printf("%10o\n", n);
	printf("%010o\n", n);
	printf("%10x\n", n);
	printf("%0#10x\n", n);

}