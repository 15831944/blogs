#include "stack.h"
using namespace std;

/***************************
	压栈
		在链表尾添加节点
***************************/
bool Stack::push(int i, char c)
{
	while (current->next != NULL)
		current = current->next;
	return insert(i, c);	// 使用父类成员函数实现
}

/*************************
	退栈
		删除链表尾节点
*************************/
bool Stack::pop(int &i, char &c)
{
	while (current->next != NULL)
		current = current->next;
	i = current->idata;
	c = current->cdata;
	return remove();
}

/*******************************
	显示整个栈同显示整个链表
*******************************/
void Stack::show()
{
	show();
}

/***************
	构造函数
***************/
Stack::Stack()
{
	cout << "Stack constructor ..." << endl;
}

/*****************************************************
	构造函数
		将子类的构造函数的参数传递给父类的构造函数
*****************************************************/
Stack::Stack(int i, char c):Linklist(i, c)
{
	cout << "Stack constructor with parameters ..." << endl;
}