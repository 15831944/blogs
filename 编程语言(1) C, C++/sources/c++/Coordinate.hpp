#pragma once
#include <iostream>
using namespace std;

class Coordinate
{
	// friend Coordinate &operator-(Coordinate &c);	// 负号操作符的友元函数的重载
	friend Coordinate operator+(Coordinate c1, Coordinate c2);
	friend ostream &operator<<(ostream &output, Coordinate &coor);
public:
	Coordinate(int x, int y);
	Coordinate &operator-();	// 负号操作符的成员函数的重载, 返回当该类对象的引用
	Coordinate &operator++();	// 前置自增运算符的成员函数的重载
	Coordinate operator++(int);	// 后置自增运算符
	// Coordinate operator+(Coordinate &c);
	int operator[](int index);
	int	getX();
	int	getY();
private:
	int	m_iX;
	int	m_iY;
};
