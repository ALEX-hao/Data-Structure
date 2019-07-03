// DateStructure LinkStack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 1.0链式存储栈

#include <iostream>
using namespace std;
static int amount = 0;
#define Max 100;
#define ERROR -0x3f3f3f;

class node
{
public:
	node() { amount++; }
	int date;
	node *next = NULL;
	~node() { amount--; }
};

class List
{
public:
	node Bottom;
	node *top = &Bottom;
	List();
	bool push(int a);
	int pop();
	void print();
	//~List();释放链表占用内存，制空所调用的指针.
};
List::List() {
	Bottom.date = -0x3f3f3f;
	cout << "建立链表" << &Bottom << endl;
}
bool List::push(int a) {
	if (amount >= 100) {
		cout << "栈已满" << endl;
		return false;
	}
	node *p = top;
	node *s = new node;
	s->date = a;
	s->next = p;
	top = s;
	return 1;
}
int List::pop() {
	if (top == &Bottom)
	{
		printf("Error！栈为空");
		return ERROR;
	}
	node *p = top->next;
	int temp = top->date;
	delete top;//出栈回收之前栈顶所指向的内存
	top = p;
	return temp;
}
void List::print() {
	node *p = top;
	while (p->next != NULL)
	{
		cout << p << '\t' << p->date << endl;
		p = p->next;
	}
}
/*List::~List() {
	node *p = head;
	node *s;
	while (p->next != NULL)
	{
		s = p;
		p = p->next;
		delete s;
	}
}*/

int main()
{
	List l;
	for (int i = 0; i < 10; i++) {
		l.push(i);
	}
	l.print();
	cout << l.pop() << endl;
	for (int i = 0; i < 10; i++) {
		cout << l.pop() << endl;
	}
    return 0; 
}
