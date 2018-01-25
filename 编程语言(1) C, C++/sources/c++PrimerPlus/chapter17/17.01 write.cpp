// write.cpp -- using cout.write()
#include <iostream>

// 测试 ostream 类的 write 方法
int main()
{
	using std::cout;
	using std::endl;

	const char *state1 = "Florida";
	const char *state2 = "Kansas";
	const char *state3 = "Euphoria";
	int len = std::strlen(state2);

	cout << "Increasing loop index: " << endl;
	int i;
	for (i = 1; i <= len; i++)
	{
		cout.write(state2, i);
		cout << endl;
	}

	// concatenate output
	cout << "Decreasing loop index: " << endl;
	for (i = len; i > 0; i--)
	{
		cout.write(state2, i) << endl;
	}

	// exceed string length
	cout << "Exceeding string length: " << endl;
	cout.write(state2, len + 5) << endl;

	system("pause");
	return 0;
}
