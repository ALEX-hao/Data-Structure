// DataStructure TreeSearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "tree.cpp"//依赖文件
using namespace std;

template <typename T>
void frontsearch(bond<T> *p)
{
	if (p != NULL)
	{
		cout << p << "\t" << p->data << endl;
		frontsearch(p->left);
		frontsearch(p->right);
	}
}

template <typename T>
void midsearch(bond<T> *p)
{
	if (p != NULL)
	{
		midsearch(p->left);
		cout << p << "\t" << p->data << endl;
		midsearch(p->right);
	}
}

template <typename T>
void rearsearch(bond<T> *p)
{
	if (p != NULL)
	{
		rearsearch(p->left);
		rearsearch(p->right);
		cout << p << "\t" << p->data << endl;
	}
}



int main()
{
	int a[15];
	for (int i = 0; i < 15; i++)
	{
		a[i] = i;
	}
	tree<int> Tree;
	Tree.bulid_tree(a, 15);
	Tree.print_tree();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	frontsearch(Tree.root);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	midsearch(Tree.root);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	rearsearch(Tree.root);
	return 0;
}

