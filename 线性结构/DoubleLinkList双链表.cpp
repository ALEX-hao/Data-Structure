// DateStructure DoubleLinkList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 双链表尝试0.1  已实现功能：添加、打印、插入、删除。

#include <iostream>
#include <windows.h>
using namespace std;
typedef int T;

static int amount = 0;
class node
{
public:
	node() { amount++; }
	T date = -1;
	node *next = NULL;
	node *piror = NULL;
	void print(node *p) { cout << p << '\t' << p->date << endl; }
	~node() { amount--; }
};


node Head;
node *foot;
node *head = &Head;


class list
{
public:
	list();
	void print();
	void print(bool );
	bool add(int a);
	bool insert(int a, int n);
	bool destroy(int a);
};


list::list()
{
	head->date = 0x3f3f3f;
	cout << "建立双链表" << head << "头元素date=" << Head.date << endl;
}
bool list::add(int a)
{
	node *p = head;
	node *s = new node;
	while (p->next != NULL)
	{
		p = p->next;
	}
	s->date = a;
	p->next = s;
	s->piror = p;
	foot = s;
	return true;
}
void list::print() 
{

	node *p = head;
	while (p!= NULL)
	{
		cout << "地址" << p << "值为" << p->date << endl;
		p = p->next;
	}
}
void list::print(bool )
{

	node *p = foot;
	while (p != NULL)
	{
		cout << "地址" << p << "值为" << p->date << endl;
		p = p->piror;
	}
}
bool list::insert(int a, int n)
{
	if (n < 0 && n>amount)
	{
		printf("插入位置错误\n");
		return false;
	}
	node *p = head;
	node *s = new node;
	s->date = a;
	while (p->next != NULL && n > 0)
	{
		p = p->next;
		n--;
	}
	s->next = p;
	s->piror = p->piror;
	p->piror->next = s;
	p->piror = s;
}
bool list::destroy(int a)
{
	if (a<0 && a>amount)
	{
		printf("位置错误Error01\N");
		return false;
	}
	node *p = head;
	int n = a;
	while (p->next != NULL && a > 0)
	{
		p = p->next;
		a--;
	}
	printf("是否确认删除第%d个元素？(Y/N)\t", n);
	p->print(p);
	char u;
	cin >> u;
	if (u == 'Y')
	{
		p->piror->next = p->next;
		p->next->piror = p->piror;
		free(p); p = NULL;
		return true;
	}
	else if (u == 'N')
	{
		printf("已取消\n");
		return true;
	}
	else 
	{
		printf("操作无效请输入正确操作符\n");
		return false;
	}
}

int main()
{
	list L;
	L.add(1); L.add(2); L.add(3); L.add(4); L.add(5); L.add(6);
	L.print();
	L.insert(3, 2);
	L.print();
	L.add(7); L.add(8);
	L.destroy(3);
	L.print();
	L.print(1);
	return 0;
}
