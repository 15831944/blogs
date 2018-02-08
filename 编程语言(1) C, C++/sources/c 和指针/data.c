#include <stdio.h>

unsigned int reverse_bits(unsigned int value);

int RootValue ()
{
	float new;
	float last;
	float number;

	printf("Enter a number: ");
	scanf("%f", &number);

	if (number < 0)
	{
		printf("Cannot compute the square root of a negative number!\n");
		return EXIT_FAILURE;
	}

	new = 1;
	do{
		last = new;
		new = (last +number / last) / 2;
		printf("%.15e\n", new);
	}while (new != last);

	printf("Square root of %g is %g\n", number, new);

	return EXIT_SUCCESS;
}

int Primenumber ()
{
	int i, j, prime;
	for (i = 1; i <= 100; i++)
	{
		prime = FALSE;
		for (j = 2; j < i; j++)
		{
			if (i % j != 0)
			{
				prime = TRUE;
			}
			else
			{
				prime = FALSE;
				break;
			}
		}
		if (prime == TRUE)
			printf("%d\n", i);
	}
}

int cast()
{
	int a, b, c;
	a = 8;
	b = 3;
	c = a / b;
	printf("c = %d\n", c);
	printf("c = %f\n", (float)c);

	float x, y, z;
	x = 10.0f;
	y = 3.0f;
	z = x / y;
	printf("x = %f y = %f\n", x, y);
	printf("z = %f\n", z);
	printf("z = %d\n", (int)z);
}

int complement()
{
	int a = 0;
	int b = 1;
	int c = 2;
	int d = -1;
	int e = -2;

	printf("%d %x ���� %d %x\n", a, a, ~a, ~a);
	printf("%d %x ���� %d %x\n", b, b, ~b, ~b);
	printf("%d %x ���� %d %x\n", c, c, ~c, ~c);
	printf("%d %x ���� %d %x\n", d, d, ~d, ~d);
	printf("%d %x ���� %d %x\n", e, e, ~e, ~e);
}

#include <stdio.h>
#include <string.h>
#include <float.h>

int main()
{
	/*����ʽ�ĳ���*/
	int a = 0, b = 0;
	printf("%lu %lu %lu \n", sizeof(a), sizeof(b), sizeof(a = b + 1));

	char c = 0;
	printf("%lu %lu \n", sizeof(c), sizeof(c = a + b));

	/*�����ĳ���*/
	int a1[16];
	char a2[16];
	printf("%lu %lu \n", sizeof(a1), sizeof(a2));

	char a3[] = "hello";
	char *p;
	p = a3;
	printf("%lu %lu \n", sizeof(a3), sizeof(p));
	printf("%lu \n", strlen(a3));
	printf("a = %d b = %d\n", a, b);

	short int a;
	int b;
	long int c;

	printf("size short = %lu\n", sizeof(short));
	printf("size int = %lu\n", sizeof(int));
	printf("size long = %lu\n", sizeof(long));

	a = 0x7fff;
	b = 0x7ffff00f;
	c = 0x7fffffffffffffff;

	printf("a = %d %x\n", a, a);
	printf("b = %d %x\n", b, b);
	printf("c = %ld %lx\n", c, c);

	a = b;
	b = c;

	printf("a = %d %x\n", a, a);
	printf("b = %d %x\n", b, b);
	printf("c = %ld %lx\n", c ,c);

	a = -4081;
	printf("a = %d %x\n", a, a);

	c = -4081;
	printf("c = %ld %lx\n", c, c);

	float a;
	double b;
	long double c;

	printf("size float = %lu\n", sizeof(float));
	printf("size double = %lu\n", sizeof(double));
	printf("size long double = %lu\n", sizeof(long double));

	a = FLT_MAX;
	b = DBL_MAX;
	c = LDBL_MAX;

	printf("a = %e\n", a);
	printf("b = %e\n", b);
	printf("c = %Le\n", c);

	a = FLT_MIN;
	b = DBL_MIN;
	c = LDBL_MIN;

	printf("a = %e\n", a);
	printf("b = %e\n", b);
	printf("c = %Le\n", c);

	a = -4.44;
	printf("a = %e %f\n", a, a);

	b = 1.23e40;
	a = b;
	printf("a = %e \n", a);
	printf("b = %e \n", b);

	return 0;
}
