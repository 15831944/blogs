#include "undergraduate.h"
using namespace std;

double Undergraduate::getGPA()
{
	return GPA;
}

void Undergraduate::setGPA(double g)
{
	GPA = g;
	return;
}

bool Undergraduate::isAdult()
{
	return age >= 18 ? true : false;
}