#include "prototype.h"
#include "complex.h"
#include "undergraduate.h"
#include "stack.h"

#include <iostream>
using namespace std;

/***************
	主函数
***************/
int main()
{
	stack_operation();

	return 0;
}

/*******************
	栈相关操作
*******************/
int stack_operation(void)
{
	Stack	mystack;
	int		i, j;
	char	c;

	for (j = 0; j < 3; j++)
	{
		cout << "input an integer and a char: " << endl;
		cin  >> i >> c;
		if (mystack.push(i, c))
			cout << "push success" << endl;
	}
	mystack.show();
	return 0;
}

/*******************
	学生相关操作
*******************/
int student_operation(void)
{
	Undergraduate student1;

	student1.set_physical("Tom", 21, 178, 60);
	student1.setGPA(3.75);
	
	cout << student1.get_name()   << endl;
	cout << student1.get_age()    << endl;
	cout << student1.get_height() << endl;
	cout << student1.get_weight() << endl;
	cout << student1.getGPA()     << endl;
	cout << student1.isAdult()    << endl;

	return 0;
}

/*******************
	复数相关操作
*******************/
int complex_operation(void)
{
	Complex a(3, 2), b(5, 4), c(1, 1), d(4, 2), temp;
	
	/* 成员函数算术运算 */
	temp.set(a.plus(b));
	temp.display();
	
	temp.set(a.minus(b));
	temp.display();
	
	/* 操作符重载 */
	temp = a + b;
	temp.display();

	temp = a - b;
	temp.display();

	temp = (a + b) - (c + d);
	temp.display();

	temp = a + 1.5;
	temp.display();

	return 0;
}

/*******************
	链表相关操作
*******************/
int linklist_operation(void)
{
	int		headi;
	char	headc;
	
	/* 用户接口 */
	cout << "input data of head node with an integer and a char: " << endl;
	cin  >> headi >> headc;
	
	/* 创建链表并调用成员对象的构造函数进行初始化 */
	Linklist mylist(headi, headc);

	/* 定位 current 指针到整数 i 所在节点 */
	mylist.locate(headi);

	/* 动态创建新节点并插入到链表中 */
	mylist.insert(15, 'F');
	mylist.insert(14, 'E');
	mylist.insert(13, 'D');
	mylist.insert(12, 'C');
	mylist.insert(11, 'B');	
	cout << "after insert: " << endl;
	mylist.show();

	/* 静态成员函数(节点计数) */
	cout << "Node count: " << Node::allocation() << endl;
	
	/* 删除节点 */
	mylist.locate('D');
	mylist.remove();
	cout << "after delete: " << endl;
	mylist.show();
	
	/* 复制链表 */
	Linklist clonelist(mylist);			//链表拷贝构造函数, 创建 clonelist, 并将 mylist 拷贝到 clonelist
	cout << "Linklist clonelist: " << endl;
	clonelist.show();
	
	/* 删除链表 */
	mylist.destroy();
	cout << "after destroy: " << endl;
	mylist.show();
	
	// cout << "Linklist clonelist: " << endl;
	// clonelist.show();

	/* 新建节点 */
	Node anode;
	cout << "anode count: " << anode.allocation() << endl;
	
	/* 友元函数 */
	Node node1(26, 'Z');
	showNode(node1);

	return 0;
}

/*******************
	节点相关操作
*******************/
int node_operation(void)
{
	Node	my_node;
	Node	&my_node_r = my_node;
	Node	*my_node_p = &my_node;
	
	/* 构造函数 */
	Node	my_node_2(8);
	Node	my_node_3(9, 'F', NULL, NULL);
	
	/* 使用构造函数初始化 */
	cout << my_node.read_idata() << endl;
	cout << my_node.read_cdata() << endl;
	
	/* 初始化函数 */
	my_node.init(1, 'a');
	cout << my_node.read_idata() << endl;
	cout << my_node.read_cdata() << endl;

	/* 使用成员函数初始化 */
	my_node.set_data(2);
	my_node.set_data('b');
	cout << my_node.read_idata() << endl;
	cout << my_node.read_cdata() << endl;
	
	/* 引用 */
	my_node_r.set_data(3);
	cout << my_node_r.read_idata() << endl;
	
	/* 对象指针 */
	my_node_p->set_data('c');
	cout << my_node_p->read_cdata() << endl;
	
	/*重载构造函数*/
	cout << my_node_2.read_idata() << endl;
	cout << my_node_2.read_cdata() << endl;

	cout << my_node_3.read_idata() << endl;
	cout << my_node_3.read_cdata() << endl;

	return 0;
}