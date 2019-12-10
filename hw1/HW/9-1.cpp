#include <stdio.h>

int main(void)
{
	double degree[] = { -5.34, 3.67, 19.76, 28.76, 35.63 };
	int size = sizeof(degree);

	for (int i = 0; i < (size / sizeof(double)); i++) {
		printf("%lf", degree[i]);
	}
}