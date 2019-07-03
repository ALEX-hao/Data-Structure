// DataStructure Tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二叉树链式存储的第3次实现
// 已实现 队列-层序建立树、打印树 ；栈-递归-中序赋值、打印 ；递归查找、删除

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

static int amount_tree = 0;								//这里如果不用静态变量会导致报错 LK2005 变量重名
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
	bond<T> *queue_tree_bond[100];						//用于储存节点指针的队列
	int flag_tree_queue = -1;							//节点指针队列的标识符
	bond<T> *stack_tree_bond[100];						//节点栈
	int top_tree_stack = -1;							//节点栈的栈帧
	int numptr_tree_array = 0;							//读取输入数组数据的标志符，数字指针
	void in_queue(bond<T> *ptr);						//把节点压入队列
	bond<T> *out_queue();								//把节点弹出队列
	void bulid_tree(T *u, int a);						//建树
	void print_tree();									//层序输出树的内容
	void mid_order_tree(T *u, bond<T> *p);				//中序输入数据到树中
	void mid_print_tree(bond<T> *p);					//中序遍历并输出树中数据
	bond<T> *find_tree_bond(T a, bond<T> *p);			//查找制定的数据返回对应节点地址
	bond<T> *insert_tree_bond(T a, bond<T> *p);			//按搜索树顺序来插入一个节点
	void push_stack(bond<T> *ptr);						//节点入栈
	bond<T> *pop_stack();								//节点弹出
	int mid_input_tree(T *u);							//用栈实现中序输入节点
	bond<T> *find_min(bond<T> *ptr);					//找到最小值
	bond<T> *destory_bond(T a, bond<T> *ptr);			//删除节点，并保持搜索树的结构
};
template <typename T>
void tree<T>::bulid_tree(T *u, int a)					//建树并初始化各个节点的值
{

	if (root == NULL)
	{
		bond<T> *s = new bond<T>;
		s->data = u[numptr_tree_array++];
		root = s;
	}
	bond<T> *p = root;
	for (int i = 0; i < flag_tree_queue; i++)
	{
		queue_tree_bond[i] = NULL;
	}
	flag_tree_queue = -1;								//清空队列后注意要把队列标志置空
	while (p->left == NULL && p->right == NULL)			//给节点增加左右儿子
	{
		bond<T> *s1 = new bond<T>;
		bond<T> *s2 = new bond<T>;
		s1->data = u[numptr_tree_array++];
		s2->data = u[numptr_tree_array++];
		p->left = s1;
		p->right = s2;
		in_queue(p->left); in_queue(p->right);
		p = out_queue();								//把左右儿子的指针装入队列反复生成新节点到预定的个数
		if (amount_tree >= a) break;
	}
	numptr_tree_array = 0;								//将传入数组标志置零队列
}
template <typename T>
void tree<T>::in_queue(bond<T> *ptr)					//把节点压入队列
{
	queue_tree_bond[++flag_tree_queue] = ptr;
}
template <typename T>
bond<T> *tree<T>::out_queue()							//把节点弹出队列
{
	bond<T> *p = queue_tree_bond[0];
	queue_tree_bond[0] = NULL;
	for (int i = 1; i <= flag_tree_queue; i++)
	{
		queue_tree_bond[i - 1] = queue_tree_bond[i];
	}
	flag_tree_queue--;
	return p;
}
template <typename T>
void tree<T>::push_stack(bond<T> *ptr)					//将节点压入栈中
{
	stack_tree_bond[++top_tree_stack] = ptr;
}
template <typename T>
bond<T> *tree<T>::pop_stack()							//将节点从栈中弹出
{
	bond<T> *p = NULL;
	p = stack_tree_bond[top_tree_stack];
	stack_tree_bond[top_tree_stack] = NULL;
	top_tree_stack--;
	return p;
}

template <typename T>
int tree<T>::mid_input_tree(T *u)						//用栈实现中序输入节点
{														//这里不想用递归，递归会导致数组的标志无法置零，影响后续使用
	numptr_tree_array = 0;
	bond<T> *p = root;
	cout << "fuck!!!!!!!!!!!!!!!" << endl;
	while (p || (top_tree_stack > -1))
	{
		while (p)
		{
			push_stack(p);
			p = p->left;
		}
		if (top_tree_stack > -1)
		{
			p = pop_stack(); 
			p->data = u[numptr_tree_array++];
			p = p->right; 
		}
	}
	numptr_tree_array = 0;
	return numptr_tree_array;
}

template <typename T>
void tree<T>::print_tree()								//层序输出树的内容
{
	for (int i = 0; i < flag_tree_queue; i++)
	{
		queue_tree_bond[i] = NULL;
	}
	flag_tree_queue = -1;								//清空队列后注意要把队列标志置空
	bond<T> *p = root;
	while (p != NULL)
	{
		cout << p << '\t' << p->data << endl;
		in_queue(p->left); in_queue(p->right);
		p = out_queue();
	}
}
template <typename T>
void tree<T>::mid_order_tree(T *u, bond<T> *p)			//递归的实现中序遍历并给树的节点赋值
{
	if (p)
	{
		mid_order_tree(u, p->left);
		p->data = u[numptr_tree_array++];
		mid_order_tree(u, p->right);
	}
}
template <typename T>
void tree<T>::mid_print_tree(bond<T> *p)				//递归实现中序遍历并打印节点
{
	if (p)
	{
		mid_print_tree(p->left);
		cout << p << '\t' << p->data << endl;
		mid_print_tree(p->right);
	}
}
template <typename T>
bond<T> *tree<T>::find_tree_bond(T a, bond<T> *p)		//递归实现，查找节点
{
	if (!p)
	{ 
		cout << "查找错误，未找到数据" << endl; 
		return NULL;
	}
	if (a > p->data) 
		return find_tree_bond(a, p->right);
	else if (a < p->data) 
		return find_tree_bond(a, p->left);
	else return p;
}
template <typename T>
bond<T> *tree<T>::insert_tree_bond(T a, bond<T> *p)		//向树中插入元素并保证查找树的顺序，递归的返回指针
{
	if (!p)
	{
		bond<T> *s = new bond<T>;
		s->data = a;
		p = s;
	}
	else if (a > p->data)
		p->right = insert_tree_bond(a, p->right);
	else if (a < p->data)
		p->left = insert_tree_bond(a, p->left);
	return p;
}
template <typename T>
bond<T> *tree<T>::find_min(bond<T> *ptr)				//查找二叉树的最小值
{
	while (ptr->left)
	{
		ptr = ptr->left;
	}
	return ptr;
}
template <typename T>
bond<T> *tree<T>::destory_bond(T a, bond<T> *ptr)		//查找并删除指定值的节点
{
	bond<T> *temp = NULL;
	if (ptr == NULL)
		cout << "未找到指定元素" << endl;
	else if (a > ptr->data)								//递归进入右子树
		ptr->right = destory_bond(a, ptr->right);
	else if (a < ptr->data)								//递归进入左子树
		ptr->left = destory_bond(a, ptr->left);
	else												//找到需要的值进行判定
	{
		if (ptr->left && ptr->right)					//有两个子节点时
		{
			temp = find_min(ptr->right);				//找到右子树的最小值
			ptr->data = temp->data;						//代替目标节点
			ptr->right = destory_bond(ptr->data, ptr->right);
		}												//继续递归删除“最小值”所在的节点
		else
		{
			temp = ptr;
			if (ptr->left == NULL)						//无子节点或有右节点
				ptr = ptr->right;						//返回右节点指针
			else if (ptr->right == NULL)				//无子节点或有左节点
				ptr = ptr->left;						//返回左节点指针
			delete temp;								//删除节点
			temp = NULL;
		}
	}
	return ptr;
}
