// DaraStructrue AVLTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// DataStructure Tree.cpp
// 二叉树链式存储的第5.5次实现
// 已实现 队列-层序建立树、打印树 ; 栈-递归-中序赋值、打印 ; 递归查找、删除 ; 计算树中节点的高度、清零高度；AVL实现平衡二叉树
// 新增：AVL化 、更新了AVL的算法使之能应对复杂情况

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

static int amount_tree = 0;								//这里如果不用静态变量会导致报错 LK2005 变量重名
template <typename T>
class bond
{
public:
	T data;
	bond<T> *left = NULL;
	bond<T> *right = NULL;
	int height = 0;
	int dalte = 0;
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
	void in_queue(bond<T> *ptr);						//把节点压入队列
	bond<T> *out_queue();								//把节点弹出队列

	bond<T> *stack_tree_bond[100];						//节点栈
	int top_tree_stack = -1;							//节点栈的栈帧
	void push_stack(bond<T> *ptr);						//节点入栈
	bond<T> *pop_stack();								//节点弹出

	int numptr_tree_array = 0;							//读取输入数组数据的标志符，数字指针
	void bulid_tree(T *u, int a);						//建树
	bond<T> *insert_tree_bond(T a, bond<T> *p=root);	//按搜索树顺序来插入一个节点

	void mid_order_tree(T *u, bond<T> *p);				//递归中序输入数据到树中
	void mid_input_tree(T *u);							//用栈实现中序输入节点

	void print_tree();									//层序输出树的内容
	void mid_print_tree(bond<T> *p=root);				//中序遍历并输出树中数据

	bond<T> *find_tree_bond(T a, bond<T> *p);			//查找制定的数据返回对应节点地址
	bond<T> *find_min(bond<T> *ptr);					//找到最小值
	bond<T> *destory_bond(T a, bond<T> *ptr);			//删除节点，并保持搜索树的结构

	int count_tree_high(bond<T> *ptr=root);				//计算树中节点的高度
	void set_tree_height_0(bond<T> *p=root);			//将节点的height高度值归零

	int max(int a, int b) { return a > b ? a : b; }
	void copy(bond<T>*p, bond<T>*s)
	{
		if (p&&s) { p->dalte = s->dalte; p->data = s->data; p->height = s->height; }
	}
	int swap(bond<T> *p, bond<T> *s);

	int find_unbalanced();								//查找对外接口
	int find_unbalanced_push(bond<T> *pr=root);			//计算高度差并将不平衡节点入栈
	int AVL();											//调整树的结构
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
	if (top_tree_stack < 0)
	{
		cout << "xxxxxxxxxx栈空xxxxxxxxxx" << endl;
		return NULL;
	}
	bond<T> *p = NULL;
	p = stack_tree_bond[top_tree_stack];
	stack_tree_bond[top_tree_stack] = NULL;
	top_tree_stack--;
	return p;
}

template <typename T>
void tree<T>::mid_input_tree(T *u)						//用栈实现中序输入节点
{														//这里不想用递归，递归会导致数组的标志无法置零，影响后续使用
	numptr_tree_array = 0;
	bond<T> *p = root;
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
		cout << p << '\t' << p->height << '\t' << p->dalte << '\t' << p->data << endl;
		if (p->left != NULL) in_queue(p->left);
		if (p->right != NULL) in_queue(p->right);
		p = out_queue();
	}
	for (int i = 0; i <= flag_tree_queue; i++)
	{
		queue_tree_bond[i] = NULL;
	}
	flag_tree_queue = -1;
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
		cout << p << '\t' << p->height << '\t' << p->dalte << '\t' << p->data << endl;
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
	if (root == NULL)									//树空时建立root节点
	{
		bond<T> *s = new bond<T>;
		s->data = a;
		root = s;
	}
	else if (!p)										//建立节点并返回该节点的值
	{
		bond<T> *s = new bond<T>;
		s->data = a;
		p = s;
	}
	else if (a > p->data)								//比节点值大递归进右子树
		p->right = insert_tree_bond(a, p->right);		//把右指针指向递归返回的节点
	else if (a < p->data)
		p->left = insert_tree_bond(a, p->left);
	return p;											//返回递归结束后的指针
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
template<typename T>
int tree<T>::count_tree_high(bond<T> *ptr)
{
	if (!ptr->left && !ptr->right)
		ptr->height++;
	else if (ptr->left&&ptr->right)
		ptr->height = max(count_tree_high(ptr->left), count_tree_high(ptr->right)) + 1;
	else if (ptr->left == NULL)
		ptr->height = count_tree_high(ptr->right) + 1;
	else if (ptr->right == NULL)
		ptr->height = count_tree_high(ptr->left) + 1;
	return ptr->height;
}
template <typename T>
void tree<T>::set_tree_height_0(bond<T> *p)
{
	if (p)
	{
		p->height = 0;
		set_tree_height_0(p->left);
		set_tree_height_0(p->right);
	}
}
template <typename T>
int tree<T>::find_unbalanced()
{
	top_tree_stack = -1;
	set_tree_height_0(root);
	count_tree_high(root);
	find_unbalanced_push(root);
	return 0;
}
template <typename T>
int tree<T>::find_unbalanced_push(bond<T> *pr)
{
	if (pr)
	{
		if (pr->left == NULL && pr->right == NULL) pr->dalte = 0;
		else if (pr->left != NULL && pr->right != NULL)
			pr->dalte = pr->left->height - pr->right->height;
		else if (pr->left == NULL && pr->right != NULL)
			pr->dalte = -pr->right->height;
		else if (pr->right == NULL && pr->left != NULL)
			pr->dalte = pr->left->height;
		if (abs(pr->dalte) >= 2)push_stack(pr);
		find_unbalanced_push(pr->left);
		find_unbalanced_push(pr->right);
	}
	return 0;
}
template <typename T>
int tree<T>::AVL()
{
	find_unbalanced();
	bond<T> *dt = pop_stack();
	bond<T> *pt = NULL, *ft = NULL;
	for(;dt; dt = pop_stack())
	{
		if (dt->dalte >= 2)
		{
			pt = dt->left;								//左单旋
			if (pt->dalte >= 1)
			{
				ft = pt->left;
				swap(dt, pt);
				pt->left = pt->right;
				pt->right = dt->right;
				dt->right = pt;
				dt->left = ft;
			}											//左右双旋
			else
			{
				ft = pt->right;
				swap(ft, dt);
				pt->left = pt->right;
				pt->right = dt->right;
				dt->right = pt;
				dt->left = ft;
			}
		}
		else if(dt->dalte<=-2)
		{
			pt = dt->right;								//右单旋
			if (pt->dalte <= -1)
			{
				ft = pt->right;
				swap(pt, dt);
				pt->right = pt->left;
				pt->left = dt->left;
				dt->left = pt;
				dt->right = ft;
			}											//右左双旋
			else
			{
				ft = pt->left;
				swap(ft, dt);
				pt->left = ft->left;
				ft->left = dt->left;
				dt->left = ft;
			}
		}
		find_unbalanced();								//重新统计树的高度、高度差
	}
	set_tree_height_0(root);
	count_tree_high(root);
	top_tree_stack = -1;
	return 0;
}
template <typename T>
int tree<T>::swap(bond<T> *p, bond<T> *s)
{
	bond<T> *temp = new bond<T>;
	copy(temp, p);
	copy(p, s);
	copy(s, temp);
	return 0;
}

int main()
{
	tree<int> v;
	int a[15];
	for (int i = 0; i < 15; i++)
	{
		a[i] = i;
	}
	v.bulid_tree(a, 15);
	v.mid_input_tree(a);
	v.count_tree_high(v.root);
	v.mid_print_tree(v.root);

	/*			  7
			  3       11
		    1   5   9    13
		   0 2 4 6 8 10 12 14 
	*/
	v.insert_tree_bond(30, v.root);
	v.insert_tree_bond(31, v.root);
	v.insert_tree_bond(-2, v.root);
	v.insert_tree_bond(-3, v.root);
	cout << "==============================" << endl;
	cout << "原来的" << endl;
	v.find_unbalanced();
	v.print_tree();
	/*                      7
		           3                11
			   1	   5	    9       13
			 0   2	 4	 6	 8	 10	 12	 14
		   -2								30
		 -3									  31
	*/
	
	v.count_tree_high(v.root);
	cout << "==============================" << endl;
	cout << "AVL" << endl;
	v.AVL();
	/*		   7
		  3       11
	    1   5   9    13
	  -2 2 4 6 8 10 12 30
	 -3 0             14 31	
	*/
	v.set_tree_height_0(v.root);
	v.count_tree_high(v.root);
	v.print_tree();
	cout << "==============================" << endl;
	v.mid_print_tree(v.root);
	tree<int> R;
	R.insert_tree_bond(30, R.root);
	R.insert_tree_bond(31, R.root);
	R.insert_tree_bond(-2, R.root);
	R.insert_tree_bond(-3, R.root);
	R.insert_tree_bond(-4, R.root);
	/*      30
		  -2  31
		 -3
		-4
	*/
	R.find_unbalanced();
	R.AVL();
	R.print_tree();
	cout << endl;
	R.mid_print_tree(R.root);
	//*/
	return 0;
}
