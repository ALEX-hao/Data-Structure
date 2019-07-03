// DateStructureCirculating Double Link List.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//1.0 实现循环链表 

#include <iostream>
using namespace std;
typedef int elmet;

static int amount = 0;
class node
{
public:
	node() { amount++; }
	node *next = NULL;
	node *prior = NULL;
	int data;
	void print();
};
void node::print()
{
	cout << this <<' '<< data << endl;	
}

node *head;
node Head;

class List
{
public:
	
	List()
	{ 
		head = &Head;
		head->data=0x3f3f3f; 
		cout << "建立循环双链表" << head << endl; 
	}
	void add(int a);
	bool insert(int a, int b);
	void print();
};
void List::add(int a)
{
	node *p = head;
	node *s = new node;
	s->data = a;
	while ( p->next!=head&&p->next != NULL)
	{
		p = p->next;
	}
	p->next = s;
	s->prior = p;
	s->next = head;
	head->prior = s;
}
void List::print()
{
	node *p = head->next;
	while (p  != head)
	{
		cout << "地址" << p << "数值" << p->data << endl;
		p = p->next;
	}
}
bool List::insert(int a, int b)
{
	if (b<0 || b>amount)
	{
		cout << "插入位置错误" << endl;
		return false;
	}
	node *s = new node;
	node *p = head;
	s->data = a;
	while (b > 0)
	{
		p = p->next;
		b--;
	}
	s->prior = p->prior;
	s->next = p;
	p->prior->next = s;
	p->prior = s;
	return true;
}

int main()
{
	List l;
	l.add(1); l.add(2); l.add(3); l.add(4); l.add(5); l.add(6);
	l.print();
	l.insert(9, 3);
	l.print();
	return 0;
}
