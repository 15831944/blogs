#include <iostream>
#include "prototype.h"
using namespace std;

int reference_test()
{
	int a = 2;
	int &b = a;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	a++;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	b++;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	return (0);
}

int swapTwoNumbers(void)
{
	int a = 2, b = 3;

	swap(a, b);
	cout << "a = " << a << endl << "b = " << b << endl;
	return (0);
}

void swap(int &x, int &y)
{
	int tmp;

	tmp = x;
	x = y;
	y = tmp;
}