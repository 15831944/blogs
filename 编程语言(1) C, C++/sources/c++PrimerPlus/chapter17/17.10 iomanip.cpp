// iomanip.cpp -- using manipulator from iomanip
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
	using namespace std;

	// use new standard manipulators
	cout << fixed << right;

	// use iomanip manipulators
	cout << setw(6)  << "N"
	     << setw(12) << "square root"
	     << setw(14) << "fourth root" << endl;

	double root;
	for (int n = 10; n <= 100; n += 10)
	{
		root = sqrt(double(n));
		cout << setw(6)	 << setfill('.') << n << setfill(' ')
		     << setw(12) << setprecision(3) << root
		     << setw(14) << setprecision(4) << sqrt(root) << endl;
	}

	system("pause");
	return 0;
}
