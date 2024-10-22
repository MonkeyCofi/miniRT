#include <stdio.h>

int main(void)
{
	double a = 3.14;
	double b = 4.23;

	printf("a is %f and b is %f\n", a, b);
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("a is %f and b is %f\n", a, b);
}
