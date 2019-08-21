// Algorithm Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 排序算法，已实现：bubblesort insertsort shellsort mergersort(递归和迭代) Qsort(quicksort)
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
	int temp = 0;
	temp = *b;
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

int merge(int a[], int at[], int L, int R, int end)//排序核心算法
{
	int temp = L;
	int num = end - L + 1;
	int Lend = R - 1;
	while (L <= Lend && R <= end)
	{
		if (a[L] <= a[R])
			at[temp++] = a[L++];
		else at[temp++] = a[R++];
	}
	while (L <= Lend)
		at[temp++] = a[L++];
	while (R <= end)
		at[temp++] = a[R++];
	for (int i = 0; i < num; i++, end--)			//注意这里的边界条件
		a[end] = at[end];							
	return end;
}
int msort(int a[], int at[], int L, int end)		//分
{
	if (end > L)
	{
		int center = (end + L) / 2;
		msort(a, at, L, center);
		msort(a, at, center + 1, end);
		merge(a, at, L, center + 1, end);
	}
	return 0;
}
int mergesort(int a[], int n)						//对外调用的接口
{
	int *at = new int[n];
	msort(a, at, 0, n - 1);
	delete at;
	at = NULL;
	return 0;
}

int merge_for(int a[], int at[], int L, int R, int end)//排序核心算法
{
	int temp = L;
	int num = end - L + 1;
	int Lend = R - 1;
	while (L <= Lend && R <= end)
	{
		if (a[L] <= a[R])
			at[temp++] = a[L++];
		else at[temp++] = a[R++];
	}
	while (L <= Lend)
		at[temp++] = a[L++];
	while (R <= end)
		at[temp++] = a[R++];
	return end;
}
int merges(int a[], int at[], int n, int length)
{
	int i = 0;
	for (i = 0; i <= n - 2 * length; i += 2 * length)
		merge_for(a, at, i, i + length, i + 2 * length - 1);
	if (n - i > length)
		merge_for(a, at, i, i + length, n - 1);
	else for (int j = i; j < n; j++) at[j] = a[j];
	return 0;
}
int merge_sort(int a[], int n)
{
	int length = 1;
	int *at = new int[n];
	while (length < n)
	{
		merges(a, at, n, length);
		length *= 2;
		merges(at, a, n, length);
		length *= 2;
	}
	delete at;
	at = NULL;
	return 0;
}

int findpivot(int a[], int L, int R)
{
	int m = (R + L) / 2;
	if (a[L] > a[R])
		swap(&a[L], &a[R]);
	if (a[L] > a[m])
		swap(&a[L], &a[m]);
	if (a[m] > a[R])
		swap(&a[m], &a[R]);
	swap(&a[m], &a[R - 1]);
	return a[R - 1];
}
int quicksort(int a[], int L,int R)				//快速排序适用于大量的数据
{												//但是也不能太大了……递归不下
	int low = L, high = R - 1;
	if (R - L > 10)								//自身无法递归结束，需要调用低阶算法。
	{
		int pivot = findpivot(a, L, R);
		while (1)
		{
			while (a[++low] < pivot);
			while (a[--high] > pivot);
			if (low < high)
				swap(&a[low], &a[high]);
			else break;
		}
		swap(&a[low], &a[R - 1]);
		quicksort(a, L, low - 1);
		quicksort(a, low + 1, R);
	}
	else insertsort(a + L, R - L);
	return 0;
}
int Qsort(int a[], int n)
{
	quicksort(a, 0, n - 1);
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
	//shellsort(arr, 100);
	//merge_sort(arr, 100);
	Qsort(arr, 100);
	for (int i = 0; i < 100; i++)
		cout << arr[i] << '\t';
	return 0;
}

