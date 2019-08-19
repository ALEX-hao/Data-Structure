// Algorithm Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 排序算法，已实现：bubblesort insertsort shellsort
// 用rand()函数生成随机数表 "rand.txt" 作为测试算法的数据

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int lagerswap(int *a, int *b)
{
	int temp = 0;
	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
	return 0;
}

int swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*b = *a;
	*a = temp;
	return 0;
}

int bubblesort(int a[],int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
			lagerswap(&a[j], &a[j + 1]);
	return 0;
}

int insertsort(int a[], int n)
{
	int temp = 0;
	int i = 0;
	for (int p = 1; p < n; p++)
	{
		temp = a[p];
		for (i = p; i > 0 && a[i - 1] > temp; i--)
		{
			a[i] = a[i - 1];
		}
		a[i] = temp;
	}
	return 0;
}

int shellsort(int a[],int n)
{
	int k = 0;
	int j = 0;
	int temp = 0;
	k = (log(n)) / log(2);	
	for (int dealt = pow(2, k) - 1; k > 0; dealt = pow(2, k) - 1)
	{	
		for (int i = dealt; i < n; i+=dealt)		//核心排序依然是插入排序
		{											//只是间隔变成了dealt
			temp = a[i];
			for (j = i; j > 0 && a[j - dealt] > temp; j = j - dealt)
			{
				a[j] = a[j - dealt];
			}
			a[j] = temp;
		}
			k--;
	}
	return 0;
}

int main()
{
	fstream file("rand.txt");
	int arr[100];
	for (int i = 0; i < 100; i++)
		file >> arr[i];
	file.close();
	//bubblesort(arr, 100);
	//shellsort(arr, 100);
	//insertsort(arr, 100);
	shellsort(arr, 100);
	for (int i = 0; i < 100; i++)
		cout << arr[i] << '\t';
	return 0;
}

