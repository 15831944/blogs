// width.cpp -- using the width format
#include <iostream>

int main()
{
	using std::cout;
	int w = cout.width(30);		// 设置指定的字段宽度, 并返回旧的字段宽度, 只影响显示的下一个项目
	cout << "default field width = " << w << ":\n";
	w = cout.width(5);		// 由于输出了其他字符, 返回0而不是30
	cout << "N" << ':';
	w = cout.width(8);		// 返回0而不是5
	cout << "N * N" << ":\n";

	for (long i = 1; i <= 100; i *= 10)
	{
		cout.width(5);
		cout << i << ':';
		cout.width(8);
		cout << i * i << ":\n";
	}

	cout.width(8);		// 返回0
	w = cout.width(5);	// 返回8
	cout << w;			// 以宽度5显示数字8
	cout << '\n';

	system("pause");
	return 0;
}
