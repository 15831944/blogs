// queue.cpp -- Queue and Customer methods
#include <cstdlib>	// (or stdlib.h) for rand()
#include <queue.h>

// Queue methods
Queue::Queue(int qs) : qsize(qs)
{
	front = rear = nullptr;
	items = 0;
}

// 从队头挨着删除节点到队尾
Queue::~Queue()
{
	Node *temp;
	while (front != nullptr)	// while queue is not yet empty
	{
		temp = front;			// save address of front item
		front = front->next;	// reset pointer to next item
		delete temp;			// delete former front
	}
}

bool Queue::isEmpty() const
{
	return items == 0;
}

bool Queue::isFull() const
{
	return items == qsize;
}

int Queue::queuecount() const
{
	return items;
}

// Add item to queue
bool Queue::enqueue(const Item & item)
{
	if (isFull())
		return false;
	Node * add = new Node;	// create new node 注意是结构体
	// on failure, new throws std::bad_alloc exception
	add->item = item;		// set node pointers
	add->next = nullptr;
	items++;
	if (front == nullptr)	// if queue is empty,
		front = add;		// place item at front
	else
		rear->next = add;	// else place at rear
	rear = add;				// have rear point to new node;
	return true;
}

// Place front item into item variable and remove from queue
bool Queue::dequeue(Item & item)
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

// time set to a random value in the range 1 - 3
void Customer::set(long when)
{
	processtime = std::rand() % 3 + 1;
	arrive = when;
}
