// DataStructure LinkList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。(´◔‸◔`)
// 栓动式链表：处于一个非常残疾的状态（需要手动输入链表元素，不能批量操作），一次录入一个元素所以称为栓动式-_-
// 栓动式链表现已完成1.0坂本升级，达到半自动水平 ╮(╯_╰)╭

#include <iostream>
#include<string.h>
using namespace std;
typedef double element;
#define ERROR -1;

static int amount = 0;

class node
{
public:
	element data;
	node *next = NULL;
	node();//构造函数
	node *HEAD();//链表头
	element set(int a);
	~node() { amount--;}
};

node::node()
{
	data = 0;
	amount++;
}
node *node::HEAD()
{
	data = 0x3f3f3f;
	node *head = this;
	return head;
}
element node::set(int a=0)
{
	data = a;
	return data;
}

node Head;
node *head = Head.HEAD();


class list
{
public:
	list();
	int add(int a);
	int add(double a);
	int search(int a);
	bool putin(int a, int b);
	node *find(int);
	bool destory(int a);
};

list::list()
{
	cout << "建立链表，头节点位置为" << head << "头元素Head.data=" << Head.data << endl;
}
int list::add(int a)
{
	node *s = new node;
	node *p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	s->data = a;
	p->next = s;
	return 0;
}
int list::add(double a)
{
	node *s = new node;
	node *p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	s->data = a;
	p->next = s;
	return 0;
}
int list::search(int a)
{
	node *p;
	p = head;
	int i = 0;
	while (p->next != NULL && p->data != a)
	{
		p = p->next;
		i++;
	}
	if (p->data == a)
		return i;
	else
		return ERROR;
}
bool list::putin(int a, int b)
{
	if (a >= amount || a < 0)
		return false;
	node *p;
	node *s = new node;
	p = head;
	for (int i = 1; i < a; i++)
	{
		p = p->next;
	}
	s->data = b;
	s->next = p->next;
	p->next = s;
	return true;
}
node *list::find(int a)
{
	if (a<0 || a>amount)
		return NULL;
	node *p;
	p = head;
	for (int i = 0; i < a; i++)
	{
		p = p->next;
	}
	return p;
}
bool list::destory(int a)
{
	if (a<0 || a>amount)
		return false;
	node *p;
	node *s = new node;
	p = head;
	for (int i = 0; i < a - 1; i++)
	{
		p = p->next;
	}
	s = p;
	p = p->next;
	s->next = p->next;
	delete p;
	cout << p <<p->data <<endl;
	return true;
}//这个链表的元素本质上还是通过new来构建的，所以可以通过delete来回收其所在内存。


int main()
{
	list L;
	cout << head <<'\t'<<Head.next<<'\t'<<Head.data<< endl;
	node u;
	u.data = 1;
	u.set(2);
	Head.next = &u;
	L.add(1);
	L.add(6);
	L.add(5);
	L.add(2.3);
	cout << amount << endl;
	node *p;
	p = head;
	int i = 0;
	while (p->next!= NULL)
	{
		p = p->next;
		i++;
	}
	cout << i <<'\t'<<L.search(5) << endl;
	L.putin(5, 16);
	node *a = L.find(5);
	cout<< a <<'\t'<<a->data<< endl;
	L.destory(5);
	cout << L.search(5) << endl;
	return 0;
}
