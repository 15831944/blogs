// error3.cpp -- using an exception
#include <iostream>

double hmean(double a, double b);

int main()
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		try {
			z = hmean(x, y);	// throw 引发异常, 字符串类型
		}
		catch (const char *s)	// 异常处理程序 expection handler
		{
			std::cout << s << std::endl;
			std::cout << "Enter a new pair of numbers: ";
			continue;
		}
		// 没有异常则继续执行
		std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;
		std::cout << "Enter next set of numbers <q to quit>: ";
	}
	std::cout << "Bye!" << std::endl;

	system("pause");
	return 0;
}

double hmean(double a, double b)
{
	if (a == -b)
	{
		throw "One value should not be the negative of the other.";	// 引发异常, 后退
	}
	return 2.0 * a * b / (a + b);
}
