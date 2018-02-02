#include "Coordinate.hpp"
#include <iostream>
using namespace std;

int main(void)
{
	Coordinate a(1, 2);
	Coordinate b(3, 4);
	Coordinate c(0, 0);
	c = a + b;
	cout << c[0] << endl;
	return(0);
}
