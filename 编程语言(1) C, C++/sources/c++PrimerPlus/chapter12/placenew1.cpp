// placenew1.cpp -- new, placement new, no delete
#include <iostream>
#include <string>
#include <new>
using namespace std;
const int BUF = 512;

class JustTesting
{
private:
	string	words;
	int		number;
public:
	JustTesting(const string & s = "Just Testing", int n = 0)
	{
		words = s;
		number = n;
		cout << words << "constructed" << endl;
	}
	~JustTesting()
	{
		cout << words << "destroyed" << endl;
	}
	void Show() const
	{
		cout << words << ", " << number << endl;
	}
};

int main()
{
	char *buffer = new char[BUF];		// get a block of memory

	JustTesting *pc1, *pc2;

	pc1 = new (buffer) JustTesting;		// place object in buffer
	pc2 = new JustTesting("Heap1", 20);	// place object on heap

	cout <<
}
