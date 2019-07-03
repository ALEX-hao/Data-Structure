#include <iostream>
using namespace std;

#define Error -1;

class Linelist
{
private:
	int n;
	int *list;
public:
	Linelist(int m);
	int print();
	int *Return();//返回数组list的首地址
	int Query(int a);//查找并返回第a个元素
	int Search(int a);//查找值为a的元素并返回其序号
	int Order();//排序
	int Delete(int a);//删除第a个元素
	int Insert(int a, int b);//在第a个位置插入元素b
	~Linelist() { delete list; }//析构函数不会主动回收动态数组所申请的内存
};

int *Linelist::Return() { int *u = list; return u; }//指针函数返回指针
Linelist::Linelist(int m)
{
	n = m;
	list = new int[n];
	printf("请逐项输入线性表内容，并以回车确认每一个输入值\n");
	for (int i = 0; i < n; i++)
	{
		cin >> list[i];
	}
	printf("输入数据为:\n");
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << '\t';
		if ((i + 1) % 5 == 0)
		{
			cout << '\n' << '\n';
		}
	}
	cout << endl;
}
int Linelist::print()
{
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << '\t';
		if ((i + 1) % 5 == 0)
		{
			cout << '\n' << '\n';
		}
	}
	return 0;
}
int Linelist::Query(int a)
{
	int m = a-1;
	if (m > n&&m < 0)
	{
		printf("查询范围错误，查询序号不存在");
		return Error;
	}
	else
	return list[m];
}
int Linelist::Search(int a)
{
	int m = a;
	int i = 0;
	while (list[i] != m )
	{
		i++;
		if (i > n)
		{
			printf("未查找的指定数值\n");
			return Error;
		}
	}
	return i+1;
}
int Linelist::Order()
{
	int temp = 0;
	int flag = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; (j < n - i-1); j++)
		{
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	return 0;
}
int Linelist::Delete(int a)
{
	int m = a;
	int x = 0;
	if ((m > n)||(m < 0))
	{
		printf("目标不存在\n");
		return Error;
	}

	for (int i = m; i < n; i++)
	{
		x = list[i];
		list[i - 1] = x;
	}

	//delete &list[n - 1]; 
	//new申请的动态数组不能用delete释放单个元素所在的内存   error:合法堆指针为空
	n = n - 1;
	return 0;
}
int Linelist::Insert(int a, int b)
{
	if (a<0 || a>n)
	{
		printf("位置错误\n");
		return Error;
	}
	int m = a - 1;
	int value = b;
	for (int i = n; i > m; i--)
	{
		list[i] = list[i - 1];
	}
	list[m] = value;
	n = n + 1;
	return 0;
}


int main()
{
	int *p;
		int n = 0;
		printf("输入线性表长度\n");
		cin >> n;
		Linelist L(n);
		p = L.Return();
	cout << p << '\t' << *p << endl;
	cout << L.Search(5) << '\t' << L.Query(2) << endl;
	L.Order();
	L.Delete(5);
	L.Insert(5, 55);
	L.print();

	return 0;
}
