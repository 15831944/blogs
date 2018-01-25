// str2.cpp -- capacity() and reserve()
#include <iostream>
#include <string>

int main()
{
	using namespace std;

	string empty;
	string small = "bit";
	string larger = "Elephants are a girl's best firend";

	cout << "Size: " << endl;
	cout << "\tempty: " << empty.size() << endl;		// 0 返回字符串的实际长度
	cout << "\tsmall: " << small.size() << endl;		// 3
	cout << "\tlarger: " << larger.size() << endl;		// 34

	cout << "Capacities: " << endl;
	cout << "\tempty: " << empty.capacity() << endl;	// 15 = 16 - 1 返回当前分配给字符串的内存块的大小
	cout << "\tsmall: " << small.capacity() << endl;	// 15 = 16 - 1 比标准容量选择(16的倍数)小1
	cout << "\tlarger: " << larger.capacity() << endl;	// 47 = 48 - 1

	empty.reserve(50);		// 请求内存块的最小长度
	cout << "Capacity after empty.reserve(50): " << empty.capacity() << endl;	// 63 = 64 - 1

	system("pause");
	return 0;
}
