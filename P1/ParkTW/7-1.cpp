#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int i, j;

	for (i = 1; i <= 5; i++)
	{
		for (j = 5; j >= i; j--)
		{
			printf("%d", j);
		}
		printf("\n");
	}

	return 0;
}