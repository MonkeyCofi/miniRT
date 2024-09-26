#include <stdio.h>
#include <stdbool.h>

bool	is_equal(float n1, float n2)
{
	if (n1 - n2 < 0.0001f)
		return (true);
	return (false);
}

int main(void)
{
	float x = 1;
	float y = 1 * 0.1f;
	float z = 1* 0.01;
	printf("%.10f\n", y);
	printf("%.10f\n", z);
	printf("%s\n", is_equal(y, z) == true ? "True" : "False");
}
