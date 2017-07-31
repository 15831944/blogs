#include <stdio.h>

int main()
{
	long long int			r = 0;
	unsigned long long int	a = 0, b = 0, c = 0;

	printf("%d %d %d\n", sizeof(long long int), sizeof(long int), sizeof(int));
	a = 0xfffffffffffffffe;
	b = 999;

	r = (long long int)(0xffffffffffffffff + b - a);
	printf("%lld\n", r);
	r = (long long int)(0xffffffffffffffff - a + b);
	printf("%lld\n", r);

	c = 0xffffffffffffffff + b;
	printf("%llu\n", c);
	c = 0xffffffffffffffff + b - a;
	printf("%llu\n", c);
}
