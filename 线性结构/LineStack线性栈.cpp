// DateStructure LineStack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 1.0线性栈实现

#include <iostream>
using namespace std;

const static int Max = 100;

class LineStack
{
private:
	int list[Max];
	int top = -1;
public:
	bool in(int a);
	int out();
	void print();
};
bool LineStack::in(int a)
{
	if(top>=Max)
	{
		cout << "Error-栈已满" << endl;
		return false;
	}
	list[++top] = a;
}
int LineStack::out()
{
	if (top > -1)
	{
		return list[top--];
	}
	else cout << "栈为空" << endl;
	return -1;
}
void LineStack::print()
{
	for (int i = top; i >= 0; i--)
	{
		cout << "位置" << i+1 << ':' << list[i]<<'\n';
		if (i != 0 && i % 5 == 0)
		{
			cout << endl;
		}
	}
}

int main()
{
	LineStack l;
	for (int i = 1; i < 11; i++)
	{
		l.in(i);
	}
	l.print();
	for (int i = 0; i < 11; i++)
	{
		cout << l.out() << endl;
	}
	l.print();
	return 0;
}
