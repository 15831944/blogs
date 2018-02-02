#include <iostream>
#include "complex.h"
using namespace std;

/* 构造函数 */
Complex::Complex(Complex &a)
{
	real = a.real;
	imag = a.imag;
}

/* 构造函数重载 */
Complex::Complex(double r, double i)
{
	real = r;
	imag = i;
}

/* 显示结果 */
void Complex::display()
{
	cout << real << (imag >= 0 ? "+" : "") << imag << "i" << endl;
}

/* 赋值运算 */
void Complex::set(Complex &a)
{
	real = a.real;
	imag = a.imag;
}

/* 算术运算 */
Complex Complex::plus(Complex a)
{
	Complex temp(real + a.real, imag + a.imag);
	return temp;
}

Complex Complex::minus(Complex a)
{
	Complex temp(real - a.real, imag - a.imag);
	return temp;
}

Complex Complex::plus(double r)
{
	Complex temp(real + r, imag);
	return temp;
}
Complex Complex::minus(double r)
{
	Complex temp(real - r, imag);
	return temp;
}

/* 操作符重载 */
void Complex::operator = (Complex a)
{
	real = a.real;
	imag = a.imag;
}

Complex Complex::operator + (Complex a)
{
	Complex temp(real + a.real, imag + a.imag);
	return temp;
}

Complex Complex::operator - (Complex a)
{
	Complex temp(real - a.real, imag - a.imag);
	return temp;
}

Complex Complex::operator + (double r)
{
	Complex temp(real + r, imag);
	return temp;
}

Complex Complex::operator - (double r)
{
	Complex temp(real - r, imag);
	return temp;
}
