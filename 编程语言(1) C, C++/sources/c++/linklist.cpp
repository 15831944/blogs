#include <iostream>
#include "linklist.h"
using namespace std;

/******************************************
	定位 current 指针到包含整数 i 的节点
******************************************/
bool Linklist::locate(int i)
{
	Node *temp = &head;
	while(temp != NULL)
	{
		// if (temp->read_idata() == i)
		if (temp->idata == i)
		{
			current = temp;
			return true;
		}
		// temp = temp->read_next();
		temp = temp->next;
	}
	return false;
}

/******************************************
	定位 current 指针到包含字符 c 的节点
******************************************/
bool Linklist::locate(char c)
{
	Node *temp = &head;
	while(temp != NULL)
	{
		if (temp->read_cdata() == c)
		{
			current = temp;
			return true;
		}
		temp = temp->read_next();
	}
	return false;
}

/*************************************************
	在 current 指针后插入新节点(新建 Node 对象)
*************************************************/
bool Linklist::insert(int i, char c)
{
	if (current != NULL)
	{
		/* 新节点的上一个节点为 current 指针, 新节点的下一个节点为 current 指针的下一个节点 */
		Node *temp = new Node(i, c, current, current->read_next());

		if (current->read_next() != NULL)
		{
			current->read_next()->set_prior(temp);	// 下游节点的上一个节点为新节点
		}
		current->set_next(temp);					// 上游节点的下一个节点为新节点
		return true;
	}
	else
		return false;
}

/**********************************
	删除 current 指针指向的节点
**********************************/
bool Linklist::remove()
{
	if (current != NULL && current != &head)
	{
		Node *temp = current;
		if (temp->read_next() != NULL)
		{
			temp->read_next()->set_prior(current->read_prior());	// 下游节点的上一个节点为待删除节点的上一个节点
		}
		temp->read_prior()->set_next(current->read_next());			// 上游节点的下一个节点为待删除节点的下一个节点
		current = temp->read_prior();								// current 指针指向待删除节点的上一个节点
		delete temp;
		return true;
	}
	else
		return false;
}

/*********************************
	从头节点开始依次打印各节点
*********************************/
void Linklist::show()
{
	Node *temp = &head;

	while(temp != NULL)
	{
		cout << temp->read_idata() << '\t' << temp->read_cdata() << endl;
		temp = temp->read_next();
	}
}

/*********************************
	删除整个链表(不包括头节点)
*********************************/
void Linklist::destroy()
{
	Node *temp = head.read_next();

	while (temp != NULL)
	{
		Node *temp2 = temp->read_next();
		delete temp;
		temp = temp2;
	}
	head.set_next(NULL);
}

/***********************************************
	构造函数
		首先调用冒号后面各成员对象的构造函数
***********************************************/
Linklist::Linklist(int i, char c):head(i, c)
{
	cout << "Linklist Constructor is running" << endl;
	current = &head;
}

/********************************************
	构造函数重载1 拷贝构造函数 浅拷贝
		调用节点拷贝构造函数来初始化 head
********************************************/
// #define	SHALLOW 0xff
#ifdef	SHALLOW

Linklist::Linklist(Linklist &l):head(l.head)
{
	// cout << "Linklist shallow copy ..." << endl;
	current = l.current;
}

/********************************************
	构造函数重载2 拷贝构造函数 深拷贝
		调用节点拷贝构造函数来初始化 head
********************************************/

#else

Linklist::Linklist(Linklist &l):head(l.head)
{
	// cout << "Linklist deep copy ..." << endl;
	current = &head;				// current 先指向头节点
	Node *temp1 = l.head.next;		// 指向原链表中头节点后的需要复制的节点, 友元类可直接访问私有成员变量
	while (temp1 != NULL)
	{
		/* 新建节点 */
		Node *temp2 = new Node(temp1->read_idata(), temp1->read_cdata(), current, NULL);
		current->set_next(temp2);
		current = current->next;	// current 最终指向尾节点
		temp1 = temp1->next;
	}
}

#endif

/**************
	析构函数
**************/
Linklist::~Linklist()
{
	// cout << "Linklist Destructor ..." << endl;
	destroy();
}