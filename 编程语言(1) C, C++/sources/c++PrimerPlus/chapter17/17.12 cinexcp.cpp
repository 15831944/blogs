// cinexcp.cpp -- having cin throw an exception
#include <iostream>
#include <exception>

int main()
{
	using namespace std;
	// have failbit cause an exception to be thrown
	cin.exceptions(ios_base::failbit);	// 设置指定位被置1时将抛出 failure 异常类, 默认情况下输入失败不会抛出异常
	cout << "Enter numbers: ";

	int sum = 0;
	int input;
	try
	{
		while (cin >> input)	// 如果 istream 对象的错误状态被设置, 则该对象为 false, throw 异常
		{
			sum += input;
		}
	}
	catch (ios_base::failure & bf)	// failure 异常类派生自 exception 类
	{
		cout << bf.what() << endl;
		cout << "O! the horror!\n";
	}

	cout << "Last vale entered = " << input << endl;
	cout << "Sum = " << sum << endl;

	system("pause");
	return 0;
}
