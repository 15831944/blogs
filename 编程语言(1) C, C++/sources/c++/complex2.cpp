#include "complex2.h"
using namespace std;

/* 构造函数 */
Complex2::Complex2(Complex2 &a)
{
	real = a.real;
	imag = a.imag;
}

/* 构造函数重载 */
Complex2::Complex2(double r, double i)
{
	real = r;
	imag = i;
}

/* 显示结果 */
void Complex2::display()
{
	cout << real << (imag >= 0 ? "+" : "") << imag << "i" << endl;
}

/* 操作符作为友元函数重载 */
Complex2 operator + (Complex2 a, Complex2 b)
{
	Complex2 temp(a.real + b.real, a.imag + b.imag);
	return temp;
}

Complex2 operator - (Complex2 a, Complex2 b)
{
	Complex2 temp(a.real - b.real, a.imag - b.imag);
	return temp;
}

Complex2 operator + (Complex2 a, double r)
{
	Complex2 temp(a.real + r, a.imag);
	return temp;
}

Complex2 operator - (Complex2 a, double r)
{
	Complex2 temp(a.real - r, a.imag);
	return temp;
}

/* 自增自减操作符重载 */
Complex2& operator ++ (Complex2 &a)	// 前
{
	a.real++;
	a.imag++;
	return a;
}
Complex2 operator ++ (Complex2 &a, int)
{
	Complex2 temp(a);
	a.real++;
	a.imag++;
	return temp;
}
Complex2& operator -- (Complex2 &a)
{
	a.real--;
	a.imag--;
	return a;
}
Complex2 operator -- (Complex2 &a, int)
{
	Complex2 temp(a);
	a.real--;
	a.imag--;
	return temp;
}