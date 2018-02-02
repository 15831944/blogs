#include "student.h"

class Undergraduate:public student
{
public:
	double	getGPA();
	void	setGPA(double g);
	bool	isAdult();
protected:
	double	GPA;

};