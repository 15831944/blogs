#include "student.h"
using namespace std;

char *student::get_name()
{
	return name;
}

int student::get_age()
{
	return age;
}

int student::get_height()
{
	return height;
}

int student::get_weight()
{
	return weight;
}

void student::set_physical(char *n, int a, int h, int w)
{
	int i;

	for (i = 0; n[i] != '\0'; i++)
	{
		name[i] = n[i];
	}
	name[i] = '\0';
	age = a;
	height = h;
	weight = w;
	return;
}

student::student()
{
	cout << "constructor no parameter" << endl;
}

student::student(char *n, int a, int h, int w)
{
	cout << "constructor with parameter" << endl;
	set_physical(n, a, h, w);
}