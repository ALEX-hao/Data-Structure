// DataStructure Queue_Link.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 队列链式实现

#include <iostream>
using namespace std;

static int amount = 0;
class node
{
public:

	node() { amount++; }
	int data;
	node *next = NULL;
	~node() { amount--; }
};

class Queue
{
public:
	node *front = NULL;
	node *rear = NULL;
	Queue()
	{ 
		cout << "建立队列" << endl;
	}
	void add(int a);
	int out();
	void print();
};
void Queue::add(int a)
{
	node *s = new node;
	s->data = a;
	if (amount == 1)
	{
		rear = s;
		front = s;
	}
	else
	{
		rear->next = s;
		rear = s;
	}
}
int Queue::out()
{
	if (amount == 0)
	{
		cout << "队列为空" << endl;
		return -1;
	}
	int u = 0;
	node *p;
	u = front->data;
	p = front;
	front = front->next;
	delete p;
	return u;
}
void Queue::print()
{
	node *p = front;
	while (p != NULL)
	{
		cout << p << '\t' << p->data << endl;
		p = p->next;
	}
}

int main()
{
	Queue R;
	for (int i = 0; i < 10; i++)
	{
		R.add(i);
	}
	R.print();
	cout << endl;
	cout << R.out() << endl;
	cout << R.out() << endl;
	cout << R.out() << endl;
	cout << endl;
	R.print();
	return 0;
}
