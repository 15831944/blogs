// queuetp.h -- queue template with a nested class
#ifndef QUEUETP_H_
#define QUEUETP_H_

// 定义队列类模板
template <typename Item>
class QueueTP
{
private:
// class scope definitions
	enum {Q_SIZE = 10};
	// Node is a nested class definition local to this class
	class Node
	{
	public:					// 由结构体修改为类, 原本的结构体成员相当于类的公有数据成员
		Item item;
		Node *next;
		Node(const Item & i) : item(i), next(nullptr) {}	// 虽然Node 不是模板类, 但是 Node 却利用通用类型 Item 来定义
	};
// private class members
	Node * front;					// pointer to front of Queue
	Node * rear;					// pointer to rear of Queue
	int items;						// current number of items in Queue
	const int qsize;				// maximum number of items in Queue
	// preemptive definitions to prevent public copying
	QueueTP(const QueueTP & q) : qsize(0) {}				// 拷贝构造函数
	QueueTP & operator=(const QueueTP & q) {return *this;}	// 赋值运算符重载
public:
	QueueTP(int qs = Q_SIZE);			// create queue with a qs limit
	~QueueTP();
	bool isEmpty() const
	{
		return items == 0;
	}
	bool isFull() const
	{
		return items == qsize;
	}
	int queuecount() const
	{
		return items;
	}
	bool enqueue(const Item &item);	// add item to end
	bool dequeue(Item &item);		// remove item from front
};

// QueueTP methods 必须放在头文件中
template <class Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs)
{
	front = rear = 0;
	items = 0;
}

template <class Item>
QueueTP<Item>::Queue::~Queue()
{
	Node *temp;
	while (front != nullptr)	// while queue is not yet empty
	{
		temp = front;			// save address of front item
		front = front->next;	// reset pointer to next item
		delete temp;			// delete former front
	}
}

// Add item to queue
template <class Item>
bool QueueTP<Item>::enqueue(const Item & item)
{
	if (isFull())
		return false;
	Node * add = new Node(item);	// create, initialize node
	// on failure, new throws std::bad_alloc exception
	items++;
	if (front == nullptr)	// if queue is empty,
		front = add;		// place item at front
	else
		rear->next = add;	// else place at rear
	rear = add;				// have rear point to new node;
	return true;
}

// Place front item into item variable and remove from queue
template <class Item>
bool QueueTP<Item>::dequeue(Item & item)
{
	if (front == nullptr)
		return false;
	item = front->item;		// set item to first item in queue
	items--;
	Node *temp = front;		// save location of first item
	front = front->next;	// reset front to next item
	delete temp;			// delete former first item
	if (items == 0)
		rear = nullptr;
	return true;
}

#endif
