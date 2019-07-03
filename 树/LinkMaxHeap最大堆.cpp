// DataStructure ArrayMaxHeap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 数组实现最大堆2.0
// -0x33333334 int的默认值
// 将pop和delete功能分开，重新命名了两种排序函数的名称

#include "pch.h"
#include <iostream>
using namespace std;

const static int root = 1;
const static int Max = 100;


class heap
{
public:
	int data[Max];									//存数据的
	int top = -1;									//指示数组顶部
	void insert_heap(int a);						//向堆中插入值a
	void down_sort(int i);							//在插入时排序维持最大堆的结构
	void swap(int *a, int *b);						//交换
	int heap_num();									//判断堆的满与空
	int pop_heap();									//弹出最大值
	void up_sort(int i);							//弹出后排序维持最大堆的结构
	void delete_elem(int i);						//删除指定元素
	int search_heap(int a);							//搜索指定的元素
	void print();									//输出打印最大堆
};
void heap::insert_heap(int a)
{
	if (top == -1) { data[0] = 0x3f3f3f; top++; }	//把第堆的最顶元素置为一个较大值来指示堆顶
	if (top >= Max) { cout << "heap已满" << endl; }
	else data[++top] = a;
	down_sort(top);
}
void heap::down_sort(int i)
{
	if (heap_num())
	{
		for (; data[i] > data[i / 2]; i /= 2)
			swap(&data[i], &data[i / 2]);
	}
	else;
}
void heap::swap(int *a, int *b)
{
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}
int heap::heap_num()
{
	if (top <= 0)
	{
		cout << "堆为空" << endl;
		return 0;
	}
	else if (top >= Max)
	{
		cout << "堆已满" << endl;
		return 0;
	}
	else return 1;
}
int heap::pop_heap()
{
	int n = 0;
	if (heap_num())
	{
		n = data[root];
		data[root] = data[top];
		data[top] = -0x33333334;
		top--;
		up_sort(root);
	}
	return n;
}
void heap::up_sort(int i)
{
	int temp = 0;
	if(heap_num())
	while(1)
	{
		if (data[i] >= data[2 * i] && data[i] >= data[2 * i + 1])
			break;
		else 
		{
			if (data[2 * i] > data[2 * i + 1])
				temp = 2 * i;
			else temp = 2 * i + 1;
			swap(&data[i], &data[temp]);
			i = temp;
		}
	}
}
int heap::search_heap(int a)
{
	if (a > data[1])
	{
		cout << "查找错误，目标数据不存在" << endl;
		return  0;
	}
	else for (int i = 1; i <= top; i++)
		if (a == data[i]) return i;
}
void heap::delete_elem(int i)
{
	if (heap_num())
	{
		int temp = search_heap(i);
		int n = i;
		data[temp] = data[top];
		data[top] = -0x33333334;
		top--;
		up_sort(temp);
	}
}
void heap::print()
{
	if (heap_num())
		for (int i = 1; i <= top; i++)
			cout << &data[i] << '\t' << data[i] << endl;
}

int main()
{
	heap H;
	for (int i = 0; i < 10; i++)
	{
		H.insert_heap(i);
	}
	for (int i = 1; i < 10; i++)
	{
		cout << H.data[i] << '\t' << &H.data[i] << endl;
	}
	cout << "---------------------------------------------" << endl;
	cout<<H.pop_heap();
	H.delete_elem(5);
	H.print();
	return 0;
}
