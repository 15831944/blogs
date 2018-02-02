#include <iostream>
using namespace std;

void create(int n = 100);	// 在函数声明中指定默认参数

int default_para()
{
	create();
	create(5);
	return (0);
}

void create(int n)
{
	cout << "n = " << n << endl;
}