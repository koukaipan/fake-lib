#include <stdio.h>

int encode(double v)
{
	printf("this is true encode1, v = %lf\n", v);
	return 1;
}

int encode2(double v)
{
	printf("this is true encode2, v = %lf, then, invoke 1\n", v);
	encode(v + 2.0);

	return 1;
}
