#include <iostream>
#include <iomanip>
#include "prototype.h"
using namespace std;

void iotest(void)
{
	char a;

	cout << "\"Hello world\"\a" << 3+4 << endl;

	cout << "please input a character:";
	cin >> a;
	cout << "you just input: " << a << endl;

	int x, y;
	cout << "please input a integer:";
	cin >> x;
	cout << "please input a integer:";
	cin >> y;
	cout << "sum: " << x + y << "\n" << endl;
	return;
}

void roomNum(void)
{
	char a;

	cout << "欢迎光临！\n\n";
	cout << "请输入你的房间号：";
	cin >> a;
	cout << "您的房间号是：" << a << endl;
	return;
}

void circumference(void)
{	
	float r, l;
	const float pi = 3.1415926F;

	cout << "please input radius: ";
	cin >> r;
	l = 2 * pi * r;
	cout << "the circumference is: " << l << endl;
}

void area(void)
{
	float r, s;
	const float pi = 3.1415926f;
	cout << "please input radius: ";
	cin >> r;
	s = pi * r * r;
	cout <<"the ara is: " << s << endl;
	return;
}

void rectangle(void)
{
	int a, b;

	cout << "input the length and width: ";
	cin >> a >> b;		// input a first, then b

	for (int i = 0; i < b; i++)
	{
		if (i != 0)
			cout << setw(i * 4) << ' ';
		for (int j = 0; j < a; j++)
		{
			cout << setw(4) << '*';
		}
		cout << endl;
	}
	return;
}

void numbers(void)
{
	int n;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			n = i * 10 + j;
			cout << setfill('0') << setw(2) << n << '\t';
		}
		cout << endl;
	}
}

int daffodil(void)
{
	for (int i = 1; i<=9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			for (int k = 0; k <= 9; k++)
			{
				int a = i * i * i + j * j * j + k * k * k;
				int b = i * 100 + j * 10 + k;

				if ( a == b)
				{
					cout << i << j << k << endl;
				}
			}
		}
	}
	return 0;
}

int multiplicationtable(void)
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << j << '*' << i << '=' << setw(2) << i * j << " ";
		}
		cout << endl;
	}
	return 0;
}
