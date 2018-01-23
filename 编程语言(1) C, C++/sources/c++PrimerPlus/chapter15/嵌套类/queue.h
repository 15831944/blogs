// queue.h -- inerface for a queue
#ifndef QUEUE_H_
#define QUEUE_H_

// This queue will contain Customer items
class Customer
{
private:
	long	arrive;			// arrive time for customer
	int		processtime;	// processing time for customer
public:
	Customer() {arrive = processtime = 0;}
	void set(long when);
	long when() const {return arrive;}
	int ptime() const {return processtime;}
};

typedef Customer Item;

// 定义队列类
class Queue
{
private:
// class scope definitions
	// Node is a nested class definition local to this class
	class Node
	{
	public:					// 由结构体修改为类, 原本的结构体成员相当于类的公有数据成员
		Item item;
		Node * next;
		Node(const Item & i) : item(i), next(nullptr) {}
	};
	enum {Q_SIZE = 10};
// private class members
	Node * front;					// pointer to front of Queue
	Node * rear;					// pointer to rear of Queue
	int items;						// current number of items in Queue
	const int qsize;				// maximum number of items in Queue
	// preemptive definitions to prevent public copying
	Queue(const Queue & q) : qsize(0) {}				// 拷贝构造函数
	Queue & operator=(const Queue & q) {return *this;}	// 赋值运算符重载
public:
	Queue(int qs = Q_SIZE);			// create queue with a qs limit
	~Queue();
	bool isEmpty() const;
	bool isFull() const;
	int queuecount() const;
	bool enqueue(const Item &item);	// add item to end
	bool dequeue(Item &item);		// remove item from front
};

#endif
