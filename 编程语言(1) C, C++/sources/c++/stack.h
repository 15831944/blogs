#include "linklist.h"

class Stack:private Linklist
{
public:
	bool	push(int i, char c);
	bool	pop(int &i, char &c);
	void	show();
			Stack();
			Stack(int i, char c);
};