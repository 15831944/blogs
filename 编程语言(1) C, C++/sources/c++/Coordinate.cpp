#include "Coordinate.hpp"

Coordinate::Coordinate(int x, int y)
{
	m_iX = x;
	m_iY = y;
}

int Coordinate::getX()
{
	return m_iX;
}

int Coordinate::getY()
{
	return m_iY;
}

// 成员函数
Coordinate &Coordinate::operator-()
{
	this->m_iX = -this->m_iX;
	this->m_iY = -this->m_iY;
	return *this;
}

Coordinate &Coordinate::operator++()
{
	++m_iX;
	++m_iY;
	return *this;
}

Coordinate Coordinate::operator++(int)
{
	Coordinate oldCoor(*this);	// 调用默认拷贝构造函数
	m_iX++;
	m_iY++;
	return oldCoor;
}
/*
Coordinate Coordinate::operator+(Coordinate &c)
{
	Coordinate temp(0, 0);
	temp.m_iX = this->m_iX + c.m_iX;
	temp.m_iY = this->m_iY + c.m_iY;
	return temp;
}
*/
Coordinate operator+(Coordinate c1, Coordinate c2)
{
	Coordinate temp(0, 0);
	temp.m_iX = c1.m_iX + c2.m_iX;
	temp.m_iY = c1.m_iY + c2.m_iY;
	return temp;
}

/*
// 友元全局函数
Coordinate &operator-(Coordinate &c)
{
	c.m_iX = -c.m_iX;
	c.m_iY = -c.m_iY;
	return c;
}
*/

ostream &operator<<(ostream &output, Coordinate &coor)
{
	output << coor.m_iX << ", " << coor.m_iY;
	return output;
}

int Coordinate::operator[](int index)
{
	if (index == 0)
		return m_iX;
	else if (index == 1)
		return m_iY;
	else
		return 0;
}
