#include <iostream>
using namespace std;

static union
{
	int		number;
	char	s;
}test;

bool isBigEndian();

/**************************************************
	http://blog.csdn.net/forestlight/article/details/6933528
	http://stackoverflow.com/questions/17914398/c-warning-anonymous-type-with-no-linkage-used-to-declare-variable
	由于使用了cout, 应用g++编译
**************************************************/
int main()
{
    if (isBigEndian())
		cout << "big" << endl;
	else
		cout << "small" << endl;
	return 0;
}

bool isBigEndian()
{
	test.number = 0x01000002;
    return (test.s == 0x01);
}
