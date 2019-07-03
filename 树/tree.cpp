// DataStructure Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二叉树链式存储的第一次实现

#include <iostream>
#include <fstream>

using namespace std;

static int amount_tree = 0;
template <typename T>
class bond
{
public:
	T data;
	bond<T> *left = NULL;
	bond<T> *right = NULL;
	bond() { amount_tree++; }
	~bond() { amount_tree--; }
};


template <typename T>
class tree
{
public:
	bond<T> *root = NULL;
	bond<T> *queue[100];
	int flag_tree_queue = -1;
	int k_tree_array = 0;
	void in(bond<T> *ptr);
	bond<T> *out();
	void bulid_tree(T *u, int a);
	void print_tree();
};
template <typename T>
void tree<T>::bulid_tree(T *u, int a)
{

	if (root == NULL)
	{
		bond<T> *s = new bond<T>;
		s->data = u[k_tree_array++];
		root = s;
	}
	bond<T> *p = root;
	for (int i = 0; i < flag_tree_queue; i++)
	{
		queue[i] = NULL;
	}
	flag_tree_queue = -1;
	while (p->left == NULL && p->right == NULL)
	{
		bond<T> *s1 = new bond<T>;
		bond<T> *s2 = new bond<T>;
		s1->data = u[k_tree_array++];
		s2->data = u[k_tree_array++];
		p->left = s1;
		p->right = s2;
		in(p->left); in(p->right);
		p = out();
		if (amount_tree >= a) break;
	}
}
template <typename T>
void tree<T>::in(bond<T> *ptr)
{
	queue[++flag_tree_queue] = ptr;
}
template <typename T>
bond<T> *tree<T>::out()
{
	bond<T> *p = queue[0];
	queue[0] = NULL;
	for (int i = 1; i <= flag_tree_queue; i++)
	{
		queue[i - 1] = queue[i];
	}
	flag_tree_queue--;
	return p;
}
template <typename T>
void tree<T>::print_tree()
{
	for (int i = 0; i < flag_tree_queue; i++)
	{
		queue[i] = NULL;
	}
	flag_tree_queue = -1;
	bond<T> *p = root;
	while (p != NULL)
	{
		cout << p << '\t' << p->data << endl;
		in(p->left); in(p->right);
		p = out();
	}
}


