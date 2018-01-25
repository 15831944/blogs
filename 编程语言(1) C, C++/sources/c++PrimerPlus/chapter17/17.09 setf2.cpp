// setf2.cpp -- using setf() with 2 arguments to control formatting
#include <iostream>
#include <cmath>

int main()
{
	using namespace std;

	// use left justification, show the plus sign, show trailing zeros, with a precision of 3
	cout.setf(ios_base::left, ios_base::adjustfield);	// 左
	cout.setf(ios_base::showpos);
	cout.setf(ios_base::showpoint);
	cout.precision(3);

	// use e-notation and save old format setting
	ios_base::fmtflags old  = cout.setf(ios_base::scientific, ios_base::floatfield);	// 3位有效小数(科学计数法)
	cout << "Left Justification:\n";
	long n;
	for (n = 1; n <=41; n+=10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|\n";
	}

	// change to internal justification
	cout.setf(ios_base::internal, ios_base::adjustfield);	// 中
	// restore default floating-point display sytle
	cout.setf(old, ios_base::floatfield);					// 总位数为3(默认的浮点显示)

	cout << "internal Justification:\n";
	for (n = 1; n <=41; n+=10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|\n";
	}

	// use right justification, fixed notation
	cout.setf(ios_base::right, ios_base::adjustfield);		// 右
	cout.setf(ios_base::fixed, ios_base::floatfield);		// 小数点后3位(定点显示)

	cout << "Right Justification:\n";
	for (n = 1; n <=41; n+=10)
	{
		cout.width(4);
		cout << n << "|";
		cout.width(12);
		cout << sqrt(double(n)) << "|\n";
	}

	system("pause");
	return 0;
}
