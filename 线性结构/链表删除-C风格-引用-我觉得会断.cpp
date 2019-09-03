// 数据结构 - 链表-我觉得会断.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

typedef struct node
{
	int data = 0;
	node *next = NULL;
}node, *list;

class link
{
public:
	node star;
	node *head = &star;
	int insert(int a)
	{
		node *p = head;
		while (p->next)p = p->next;
		node *s = new node;
		s->data = a;
		p->next = s;
		return 0;
	}
	void print()
	{
		node *p = head->next;
		while (p)
		{
			cout << p << '\t' << p->data << endl;
			p = p->next;
		}
	}
};

void Del(list &L, int x)
{
	node *p = NULL;
	if (L == NULL) return;
	if (L->data == x)
	{
		p = L;
		L = L->next;
		delete p; 
		p = NULL;
		Del(L, x);
	}
	else Del(L->next, x);
}


int main()
{
	link u;
	for (int i = 0; i < 10; i++)
		u.insert(i);
	u.print();
	cout << endl;
	Del(u.head, 3);
	cout << endl;
	u.print();
    return 0; 
}


