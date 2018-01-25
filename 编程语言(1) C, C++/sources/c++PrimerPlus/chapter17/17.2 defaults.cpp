// defaults.cpp -- cout default formats
#include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	cout << "12345678901234567890\n";	// 原样输出

	char ch = 'K';
	int t = 273;
	cout << ch << ":\n";			// 显示字符而不是整数
	cout << t << ":\n";				// 显示整数
	cout << -t << ":\n";

	double fl = 1.200;
	cout << fl << ":\n";				// 末尾不显示0, 但有6个空格
	cout << (fl + 1.0 / 9.0) << ":\n";	// 浮点数默认显示为6位

	double  f2 = 1.67E2;
	cout << f2 << ":\n";			// 定点表示法
	f2 += 1.0 / 9.0;
	cout << f2 << ":\n";			// 定点表示法?
	cout << (f2 * 1.0e4) << ":\n";	// 科学计数法(指数大于等于6)

	double f3 = 2.3e-4;
	cout << f3 << ":\n";			// 定点表示法?
	cout << f3 / 10 << ":\n";		// 科学计数法(指数小于等于-5)

	system("pause");
	return 0;
}
