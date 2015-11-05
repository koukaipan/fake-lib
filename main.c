#include <stdio.h>

extern int encode(double v);
extern int encode2(double v);

int main()
{
	int ret;

	printf("1st call\n");
	ret = encode(3.14159);
	printf("1st ret = %d\n", ret);
	printf("2nd call\n");
	ret = encode2(1.1432);
	printf("2nd ret = %d\n", ret);

	return 0;
}
