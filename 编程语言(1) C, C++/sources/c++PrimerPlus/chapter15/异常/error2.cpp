// error2.cpp -- returning an error code
#include <iostream>
#include <cstdlib>
#include <cfloat>

bool hmean(double a, double b, double *ans);

int main()
{
	double x, y, z;

	std::cout << "Enter two numbers: ";
	while (std::cin >> x >> y)
	{
		if (hmean(x, y, &z))	// 使用函数返回值返回错误码
			std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;
		else
			std::cout << "One value should not be the negative of the other - try again." << std::endl;
		std::cout << "Enter next set of numbers <q to quit>: ";
	}
	std::cout << "Bye!" << std::endl;

	// system("pause");
	return 0;
}

bool hmean(double a, double b, double *ans)
{
	if (a == -b)
	{
		*ans = DBL_MAX;
		return false;
	}
	*ans = 2.0 * a * b / (a + b);
	return true;
}
