#include <iostream>
#include "node.h"
using namespace std;

class Linklist
{
public:
	/* 查找, 插入, 删除, 显示, 销毁 */
	bool	locate(int i);
	bool	locate(char c);
	bool	insert(int i = 0, char c = '0');
	bool	remove();
	void	show();
	void	destroy();
	/* 构造函数 */
	Linklist(int i, char c);	// 链表类构造函数
	Linklist(Linklist &l);		// 链表拷贝构造函数
	/* 析构函数 */
	~Linklist();

// private:
protected:
	Node	head;
	Node	*current;
};
