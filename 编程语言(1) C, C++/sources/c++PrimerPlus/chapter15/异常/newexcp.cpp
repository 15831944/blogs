// newexcp.cpp -- the bad_alloc exception
#include <iostream>
#include <new>			// 声明了 bad_alloc 类, 继承自 exception 类
#include <cstdlib>
using namespace std;

struct Big
{
	double stuff[20000];
};

int main()
{
	Big *pb;
	try {
		cout << "Trying to get a big block of memory:" << endl;
		pb = new Big[10000];		// 默认会抛出异常 20000 * 10000 * 8 = 1,600,000,000 bytes
		cout << "Got past the new request:" << endl;
		pb = new (std::nothrow) Big[10000];		// 使用编译器提供的标记使 new 不抛出异常而是返回空指针
		if (pb == nullptr)
		{
			cout << "Could not allocate memory." << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
	}
	catch (bad_alloc &ba)
	{
		cout << "Caught the exception" << endl;
		cout << ba.what() << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	cout << "Memory successfully allocated" << endl;
	pb[0].stuff[0] = 4.0;
	cout << pb[0].stuff[0] << endl;
	delete []pb;

	system("pause");
	return 0;
}
