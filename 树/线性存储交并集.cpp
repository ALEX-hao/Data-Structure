// 一个叫做交并集的东西.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 线性结构实现交并集 1.0
// 用rand()生成随机数指向随机的父位置

#include "pch.h"
#include <iostream>
using namespace std;

const static int max = 100;

template <typename T>
class element
{
public:
	T data;
	int father = -1;
};

template <typename T>
class aggregate
{
public:
	int top = -1;
	element<T> line[max];
	int insert(T da, int fa = -1);
	int search(T da);
	int link_to(T da1, T da2);
	void print();
};
template <typename T>
int aggregate<T>::insert(T da, int fa)
{
	if (top >= max - 1) 
	{
		cout << "已满!!" << endl;
		return -1;
	}
	line[++top].data = da;
	line[top].father = fa;
	return top;
}
template <typename T>
int aggregate<T>::search(T da)
{
	for (int i = 0; i <= top; i++)
		if (line[i].data == da) return i;
	cout << "没找到呢:-)" << endl;
	return 0;
}
template <typename T>
int aggregate<T>::link_to(T da1, T da2)					//把子元素少的集合并入子元素多的集合
{
	int pos1 = search(da1);
	int pos2 = search(da2);
	int temp1 = 0; int temp2 = 0;
	if (pos1 == -1 || pos2 == -1) return -101;
	if (line[pos1].father == -1)
	{
		for (int i = 0; i <= top; i++)
			if (line[i].father == pos1) temp1++;
		line[pos1].father = -temp1;
	}
	if (line[pos2].father == -1)
	{
		for (int i = 0; i <= top; i++)
			if (line[i].father == pos2) temp2++;
		line[pos2].father = -temp2;
	}
	if (line[pos1].father >= line[pos2].father)
	{
		line[pos1].father = pos2;
		return pos2;
	}
	else
	{
		line[pos2].father = pos1;
		return pos1;
	}
}
template <typename T>
void aggregate<T>::print()
{
	for (int i = 0; i <= top; i++)
		cout << i << '\t' << line[i].data << '\t' << line[i].father << endl;
}

int main()
{
	aggregate<char> u;
	int x = 0;
	for (char i = 'A'; i < 'O'; i++)
	{
		x = rand() % 10;
		if (x == (i - 'A')) u.insert(i);
		else u.insert(i, x);
	}
	u.print();
	cout << "=============" << endl;
	u.link_to('A', 'C');
	u.print();
    return 0; 
}
