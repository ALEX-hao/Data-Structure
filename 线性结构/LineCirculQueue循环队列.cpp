// DataStructure CirculQueue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 循环队列实现

#include <iostream>
using namespace std;
const int Max = 10;

class queue {
private:
	int front = 0;
	int rear = 0;
	int flag = -1;
public:
	int list[Max];
	queue() { cout << "建立队列" << list << endl; }
	void print();
	int judge();
	bool in(int a);
	int out();
};
void queue::print()
{
	int j = 0;
	if (judge() == -1)
	{
		for (int i = 0; i <Max; i++)
		{
			cout << list[i] << '\t';
			j++;
			if (j == 5)
			{
				j = 0;
				cout << endl;
			}
		}
	}
	else
	{
		for (int i = front; i != -1; i++)
		{
			if (i > Max-1 ) i = 0;
			if (i != rear)
			{
				cout << list[i] << '\t';
				j++;
				if (j == 5)
				{
					j = 0;
					cout << endl;
				}
			}
			else if (i == rear) i = -2;//for 运行完一次循环后 i+1
		}
	}
}
int queue::judge()
{
	if (front == rear && flag == 1)
	{
		cout << "队列已满" << endl;
		return -1;
	}
	else if (front == rear && flag == 0)
	{
		cout << "队列为空" << endl;
		return 0;
	}
	else return 1;
}
bool queue::in(int a)
{
	if (judge() == -1) return false;
	list[rear] = a;
	rear++;
	if (rear >= Max) rear = 0;
	flag = 1;
	return true;
}
int queue::out()
{
	if (judge() == 0) return false;
	int a= list[front];
	list[front] = -858993459;//置空
	front++;
	if (front >= Max) front = 0;
	flag = 0;
	return a;
}

int main()
{
	queue l;
	for (int i = 1; i <= 10; i++)
	{
		l.in(i);
	}
	l.print();
	for (int i = 0; i < 10; i++)
	{
		cout << l.out() << endl;
	}
	l.print();
	cout << endl;
	l.in(99);
	l.in(72);
	cout << endl;
	l.print();	
	return 0;
}
