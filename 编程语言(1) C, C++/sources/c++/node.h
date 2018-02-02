#include <iostream>
using namespace std;

class Node
{
	/* 友元类 */
	friend class Linklist;
	friend class Stack;
	/* 友元函数 */
	friend void showNode(Node &n);
public:
	/* 读取成员数据 */
	int		read_idata() const;
	char	read_cdata() const;
	Node	*read_prior() const;
	Node	*read_next() const;
	/* 写入成员数据 */
	bool	set_data(int i);		// 重载函数
	bool	set_data(char c);
	bool	set_prior(Node *p);		// 参数类型相同，不能重载
	bool	set_next(Node *n);
	/* 初始化函数 */
	void	init(int i, char c);
	/* 构造函数 */
	Node();									// 构造函数
	Node(int i, char c = 'x');				// 构造函数重载1 默认参数
	Node(int i, char c, Node *p, Node *n);	// 构造函数重载2
	Node(Node &n);							// 构造函数重载3 节点拷贝
	/* 析构函数 */
	~Node();
	/* 静态成员函数 */
	static int allocation();

private:
	/* 成员数据 */
	int		idata;
	int		cdata;
	Node	*prior;
	Node	*next;
	/* 静态成员变量(私有) */
	static int cnts;
};
