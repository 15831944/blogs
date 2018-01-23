// nested.cpp -- using a queue template that has a nested class
#include <iostream>
#include <string>
#include "queuetp.h"

int main()
{
	using std::string;
	using std::cin;
	using std::cout;
	using std::endl;

	QueueTP<string> cs(5);
	string temp;

	while (!cs.isFull())
	{
		cout << "Please enter your name. You will be served in the order of arrival." << endl << "name: ";
		getline(cin, temp);
		cs.enqueue(temp);
	}
	cout << "The queue is full. Processing begins!" << endl;

	while (!cs.isEmpty())
	{
		cs.dequeue(temp);
		cout << "Now processing " << temp << "... " << endl;
	}
	return 0;
}
