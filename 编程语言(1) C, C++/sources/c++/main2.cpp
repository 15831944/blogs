#include "prototype.h"
#include "complex2.h"
using namespace std;

/***************
	主函数
***************/
int main2()
{
	complex2_operation();

	return 0;
}

int complex2_operation(void)
{
	Complex2 a(3, 2), b(5, 4), c(1, 1), d(4, 2), e(2, 2), f(2, 4), temp;
	
	/* 操作符作为友元函数重载 */
	temp = a + b;
	temp.display();

	temp = a - b;
	temp.display();

	temp = (a + b) - (c + d);
	temp.display();

	temp = a + 1.5;
	temp.display();

	/* 自增自减操作符重载 */
	temp = (e++) + f;
	temp.display();

	temp = f - (++e);
	temp.display();

	e.display();
	return 0;
}