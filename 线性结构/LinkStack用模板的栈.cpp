// 模板template尝试1.0.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

int amount = 0;
template<typename T>
class node
{
public:
	node() { amount++; }
	T date;
	node *next = NULL;
	~node() { amount--; }
};

template<typename T>
class stack
{
public:
	node<T> *top = NULL;
	void push(T a);
	T pop();
};
template<typename T>
void stack<T>::push(T a)//定义类模板的模板函数
{
	node<T> *s = new node<T>;
	s->date = a;
	if (amount == 1)
	{
		top = s;
	}
	else
	{
		s->next = top;
		top = s;
	}
}
template<typename T>
T stack<T>::pop()
{
	if (amount <= 0)
	{
		cout << "栈为空" << endl;
		return -1;
	}
	else
	{
		node<T> *p = top->next;
		T a = top->date;
		delete top;
		top = p;
		return a;
	}
}

int main()
{
	stack<double> l;
	l.push(6.2);
	
	for (int i = 0; i < 10; i++)
	{
		l.push(i);
	}
	
	for (int i = 0; i <= 10; i++)
	{
		cout << l.pop() << endl;
	}
	return 0;
}
