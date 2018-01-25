// showpt.cpp -- setting the precision, showing trailing point
#include <iostream>

int main()
{
	using std::cout;
	using std::ios_base;

	float price1 = 20.40;
	float price2 = 1.9 + 8.0 / 9.0;

	cout.setf(ios_base::showpoint);
	cout << "\"Furry Friends\" is $" << price1 << "!\n";
	cout << "\"Fiery Fiend\" is $" << price2 << "!\n";

	cout.precision(2);	// 默认输出模式下, 设置精度的总位数为2, 并且会四舍五入
	cout << "\"Furry Friends\" is $" << price1 << "!\n";
	cout << "\"Fiery Fiend\" is $" << price2 << "!\n";

	system("pause");
	return 0;
}
