#include <iostream>
using namespace std;

int seq(int n);

int sequence(void)
{
	for (int i = 1; i <= 8; i++)
	{
		cout << "seq(" << i << ") = " << seq(i) << endl;
	}
	return 0;
}

int seq(int n)
{
	if (n == 1)
		return 1;
	else
		return 2 * seq(n - 1) + 3;
}