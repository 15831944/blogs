// str1.cpp -- introducing the string class
#include <iostream>
#include <string>

//using string constructions
int main()
{
	using namespace std;

	string one("Lottery Winner!");		// ctor #1 将 string 对象初始化为C字符串(NBTS)
	cout << "one: " << one << endl;				// overloaded << 操作符

	string two(20, '$');				// ctor #2 创建n个元素为c的 string 对象
	cout << two << endl;

	string three(one);					// ctor #3 拷贝构造函数
	cout << three << endl;

	one += " Oops!";					// overloaded += 操作符
	cout << one << endl;

	two = "Sorry! That was ";			// overloaded = 操作符
	three[0] = 'P';						// overloaded [] 操作符

	string four;						// ctor #4 默认构造函数
	// + 运算符经过多次重载, 使得第1个操作数必须是 string 对象, 第2个操作数可以是 string 对象, C字符串, char 值
	four = two + three;					// overloaded +, = 操作符, 创建临时对象并赋值
	cout << four << endl;

	char alls[] = "All's well that ends well";
	string five(alls, 20);				// ctor #5 将 string 对象初始化为C字符串(NBTS)的前n个字符
	cout << five << "!\n";

	string six(alls + 6, alls + 10);	// ctor # 6 将 string 对象初始化为区间内的字符, 数组名是指针
	cout << "six: " << six << endl;

	string seven(&five[6], &five[10]);	// ctor #6 again, char 值指针
	cout << seven << "..." << endl;

	string eight(four, 7, 16);			// ctor #7 将 string 对象初始化为对象str从位置pos开始的n个字符
	cout << "eight: " << eight << " in motion!" << endl;

	system("pause");
	return 0;
}
