#include<iostream>
using namespace std;

class Complex
{
public:
	/* 构造函数 */
	Complex(Complex &a);
	Complex(double r = 0, double i = 0);
	void display();
	/* 幅值, 加, 减 */
	void set(Complex &a);
	Complex plus(Complex a);
	Complex minus(Complex a);
	Complex plus(double r);
	Complex minus(double r);
	/* 操作符重载 */
	void operator = (Complex a);
	Complex operator + (Complex a);
	Complex operator + (double r);
	Complex operator - (Complex a);
	Complex operator - (double r);
private:
	double real;
	double imag;
};