// error5.cpp -- unwinding the stack
#include <iostream>
#include <cmath>
#include <string>
#include "exc_mean.h"

// 用于指示栈解退时自动变量的释放(调用析构函数)
class demo
{
private:
	std::string word;
public:
	demo (const std::string &str)
	{
		word = str;
		std::cout << "demo " << word << " created" << std::endl;
	}
	~demo()
	{
		std::cout << "demo " << word << " destroyed" << std::endl;
	}
	void show() const
	{
		std::cout << "demo " << word << " lives" << std::endl;
	}
};

// function prototypes
double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	double x, y, z;

	{
		demo d1("found in block in main()");	// 生命周期在代码块
		std::cout << "Enter two numbers: ";
		while (cin >> x >> y)
		{
			try {
				z = means(x, y);	// throw 引发异常, 字符串类型
				cout << "The means of " << x << " and " << y << " is " << z << endl;
				cout << endl << "Enter next pair: ";
			}
			catch (bad_hmean &bg)	// 异常处理程序 expection handler
			{
				bg.mesg();
				std::cout << "try again.\n";
				continue;
			}
			catch (bad_gmean &hg)	// 异常处理程序 expection handler
			{
				cout << hg.mesg();
				std::cout << "sorry.\n";
				break;
			}
			// 没有异常则继续执行
		}
		d1.show();
	}
	cout << "Bye!" << std::endl;
	cin.get();
	cin.get();

	system("pause");
	return 0;
}

// 计算调和平均数
double hmean(double a, double b)
{
	if (a == -b)
	{
		throw bad_hmean(a, b);
	}
	return 2.0 * a * b / (a + b);
}

// 计算几何平均数
double gmean(double a, double b)
{
	if (a < 0 || b < 0)
	{
		throw bad_gmean(a, b);
	}
	return std::sqrt(a * b);
}

// 计算算术平均数, 调和平均数, 几何平均数
double means(double a, double b)
{
	double am, hm, gm;
	demo d2("found in means()");	// 随所在函数的调用和返回构造和析构
	am = (a + b) / 2.0;
	try
	{
		hm = hmean(a, b);
		gm = gmean(a, b);	// 没有在当前函数捕获此异常, 将进行栈解退, 释放自动变量并直接跳到 main 中的 ctach 块
	}
	catch (bad_hmean &bg)
	{
		bg.mesg();
		std::cout << "Caught in means()" << std::endl;
		throw;		// rethrows the exception 重新引发异常, 是当前函数终止, 将异常向上发送给 main() 函数
	}
	d2.show();
	return (am + hm + gm) /3.0;
}
