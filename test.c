#include <stdio.h>

int main(void)
{
	float a = 3.14;
	float b = 4.23;

	printf("a is %f and b is %f\n", a, b);
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("a is %f and b is %f\n", a, b);
}
