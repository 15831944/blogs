#include<iostream>

class Complex2
{
public:
	/* 构造函数 */
	Complex2(Complex2 &a);
	Complex2(double r = 0, double i = 0);
	void display();
	/* 操作符作为友元函数重载 */
	friend Complex2 operator + (Complex2 a, Complex2 b);
	friend Complex2 operator + (Complex2 a, double r);
	friend Complex2 operator - (Complex2 a, Complex2 b);
	friend Complex2 operator - (Complex2 a, double r);
	/* ++ -- 操作符作为友元函数重载 */
	friend Complex2& operator ++ (Complex2 &a);		// 前 ++ 重载
	friend Complex2  operator ++ (Complex2 &a, int);	// 后 ++ 重载
	friend Complex2& operator -- (Complex2 &a);		// 前 -- 重载
	friend Complex2  operator -- (Complex2 &a, int);	// 后 -- 重载
private:
	double real;
	double imag;
};