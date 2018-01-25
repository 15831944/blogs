// error4.cpp -- using exception classes
#include <iostream>
#include <cmath>
#include "exc_mean.h"

// function prototypes
double hmean(double a, double b);
double gmean(double a, double b);

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (cin >> x >> y)
	{
		try {
			z = hmean(x, y);	// throw 引发异常, 字符串类型
			cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
			z = gmean(x, y);
			cout << "Geometirc mean of " << x << " and " << y << " is " << z << endl;
		}
		catch (bad_hmean &bg)	// 异常处理程序 expection handler
		{
			bg.mesg();
			std::cout << "try again.\n";
			continue;
		}
		catch (bad_gmean &hg)	// 异常处理程序 expection handler
		{
			cout << hg.mesg();
			std::cout << "sorry.\n";
			break;
		}
		// 没有异常则继续执行
	}
	std::cout << "Bye!" << std::endl;

	system("pause");
	return 0;
}

double hmean(double a, double b)
{
	if (a == -b)
	{
		throw bad_hmean(a, b);
	}
	return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)
{
	if (a < 0 || b < 0)
	{
		throw bad_gmean(a, b);
	}
	return std::sqrt(a * b);
}
