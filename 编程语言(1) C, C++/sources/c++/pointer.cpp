#include <iostream>
using namespace std;

int pointer_test(void)
{
	int i = 3;
	int *p = &i;
	int **pp = &p;

	cout << "addr of variable i: " <<   p << endl;
	cout << "data of vaviable i: " <<  *p << endl;
	cout << "addr of pointer  p: " <<  pp << endl;
	cout << "addr of variable i: " << *pp << endl;

	*p = *p + 2;
	cout << "data of vaviable i: " <<  *p << endl;

	return (0);
}