// DataStructure Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二叉树链式存储的第一次实现

#include <iostream>
#include <fstream>

using namespace std;

int amount = 0;
template <typename T>
class bond
{
public:
	T data;
	bond<T> *left = NULL;
	bond<T> *right = NULL;
	bond() { amount++; }
	~bond() { amount--; }
};


template <typename T>
class tree
{
public:
	bond<T> *root = NULL;
	bond<T> *queue[100];
	int flag = -1;
	int k = 0;
	void in(bond<T> *ptr);
	bond<T> *out();
	void bulid(T *u, int a);
	void print();
};
template <typename T>
void tree<T>::bulid(T *u, int a)
{

	if (root == NULL)
	{
		bond<T> *s = new bond<T>;
		s->data = u[k++];
		root = s;
	}
	bond<T> *p = root;
	while (p->left == NULL && p->right == NULL)
	{
		bond<T> *s1 = new bond<T>;
		bond<T> *s2 = new bond<T>;
		s1->data = u[k++];
		s2->data = u[k++];
		p->left = s1;
		p->right = s2;
		in(p->left); in(p->right);
		p = out();
		if (amount >= a) break;
	}	
}
template <typename T>
void tree<T>::in(bond<T> *ptr)
{
	queue[++flag] = ptr;
}
template <typename T>
bond<T> *tree<T>::out()
{
	bond<T> *p = queue[0];
	queue[0] = NULL;
	for (int i = 1; i <= flag; i++)
	{
		queue[i - 1] = queue[i];
	}
	flag--;
	return p;
}
template <typename T>
void tree<T>::print()
{
	for (int i = 0; i < flag; i++)
	{
		queue[i] = NULL;
	}
	flag = -1;
	bond<T> *p = root;
	while (p != NULL)
	{
		cout << p << '\t' << p->data << endl;
		in(p->left); in(p->right);
		p = out();
	}
}

int main()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
	tree<int> l;
	l.bulid(a, 9);
	cout << amount << endl;
	l.print();
	return 0;
}


