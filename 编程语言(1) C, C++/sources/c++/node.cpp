#include <iostream>
#include "node.h"
using namespace std;

int Node::cnts = 0;		// 别忘了初始化静态成员变量

/*******************
	读取成员数据
*******************/
int Node::read_idata() const
{
	return idata;
}

char Node::read_cdata() const
{
	return cdata;
}

Node *Node::read_prior() const
{
	return prior;
}

Node *Node::read_next() const
{
	return next;
}

/*******************
	写入成员数据
*******************/
bool Node::set_data(int i)
{
	idata = i;
	return true;
}

bool Node::set_data(char c)
{
	cdata = c;
	return true;
}

bool Node::set_prior(Node *p)
{
	prior = p;
	return true;
}

bool Node::set_next(Node *n)
{
	next = n;
	return true;
}

/*****************
	初始化对象
*****************/
void Node::init(int i, char c)
{
	idata = i;
	cdata = c;
	prior = NULL;
	next  = NULL;
}

/***************
	构造函数
***************/
Node::Node()
{
	// cout << "Node Constructor 0 is runing" << endl;
	idata = 0;
	cdata = '0';
	prior = NULL;
	next  = NULL;

	cnts++;
}

/******************************
	构造函数 重载1 默认参数
******************************/
Node::Node(int i, char c)
{
	// cout << "Node Constructor 1 is runing" << endl;
	idata = i;
	cdata = c;
	prior = NULL;
	next  = NULL;

	cnts++;
}

/****************************
	构造函数 重载2 带参数
****************************/
Node::Node(int i, char c, Node *p, Node *n)
{
	// cout << "Node Constructor 2 is runing" << endl;
	idata = i;
	cdata = c;
	prior = p;
	next  = n;

	cnts++;
}

/**********************************
	构造函数 重载3 节点对象拷贝
**********************************/
Node::Node(Node &n)
{
	/* 可以读取同类对象的私有成员数据 */
	idata = n.idata;
	cdata = n.cdata;
	prior = n.prior;
	next  = n.next;

	cnts++;
}

/****************
	析构函数
****************/
Node::~Node()
{
	// cout << "Node Destructor ..." << endl;
	
	cnts--;
}

/*******************
	静态成员函数
*******************/
int Node::allocation()
{
	return cnts;
}

/****************
	友元函数
****************/
void showNode(Node &n)
{
	/* 友元函数可以访问私有成员数据 */
	cout << n.idata << '\t' << n.read_cdata() << endl;
	// cout << n.idata << '\t' << n.cdata << endl;
}