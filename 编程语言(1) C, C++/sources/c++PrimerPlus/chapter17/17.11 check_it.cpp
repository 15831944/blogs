// check_it.cpp -- checking for valid input
#include <iostream>

int main()
{
	using namespace std;
	cout << "Enter numbers: ";

	int sum = 0;
	int input;
	while (cin >> input)	// 如果 istream 对象的错误状态被设置, 则该对象为 false
	{
		sum += input;
	}
	if (cin.eof())
	{
		cout << "Loop terminated because EOF encountered\n";
	}

	// cout << "Last vale entered = " << input << endl;
	// cout << "Sum = " << sum << endl;

	// 排除不匹配的输入, 但只能排除一个
	if (cin.fail() && !cin.eof())	// failed because of mismatched input
	{
		cin.clear();		// reset stream state 否则无法继续输入
		while (!isspace(cin.get()))
			continue;	// get rid of bad inputs
	}
	else	// else bail out
	{
		cout << "I cannot go on!\n";
		exit(1);
	}

	while (cin >> input)	// 如果 istream 对象的错误状态被设置, 则该对象为 false
	{
		sum += input;
	}
	cout << "Last vale entered = " << input << endl;
	cout << "Sum = " << sum << endl;

	system("pause");
	return 0;



	cout << "Now enter a new number: \n";
	cin.clear();	// reset stream state

	// 一直读取字符, 直到空白为止, 即丢弃下一个单词
	while (!isspace(cin.get()))
	{
		static int i = 0;
		cout << "i = " << ++i << endl;
		continue;	// get rid of bad inputs
	}

	// 丢弃输入行中的剩余部分
	while (cin.get() != '\n')
	{
		static int j = 0;
		cout << "j = " << ++j << endl;
		continue;	//get rid rest of line
	}

	cin >> input;
	cout << "current string in istream: " << input << endl;

	system("pause");
	return 0;
}
