#include <iostream>
using namespace std;

/*****************
	КЏЪ§жиди
*****************/
int		absolute(int    a);
float	absolute(float  a);
double	absolute(double a);

int overload(void)
{
	int		a = -5;
	int		b = 3;
	float	c = -2.4f;
	float	d = 8.4f;
	double	e = -3e-9;
	double	f = 3e6;

	cout << "a = " << abs(a) << endl;
	cout << "b = " << abs(b) << endl;
	cout << "c = " << abs(c) << endl;
	cout << "d = " << abs(d) << endl;
	cout << "e = " << abs(e) << endl;
	cout << "f = " << abs(f) << endl;
	return (0);
}

int absolute(int a)
{
	cout << "int abs ";
	return (a > 0 ? a : -a);
}

float absolute(float a)
{
	cout << "float abs ";
	return (a > 0 ? a : -a);
}

double absolute(double a)
{
	cout << "double abs ";
	return (a > 0 ? a : -a);
}