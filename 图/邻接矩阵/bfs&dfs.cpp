// DataStructure 邻接矩阵的遍历.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// DSP和BSP的实现; 这里还使用了输入输出控制; 文件名为data.txt;

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

typedef int vertex;

ifstream datatxt("data.txt");

class edge									//边类型用于暂时存储和定位边和设定权重
{
public:
	void set(int a, int b, int c)
	{
		v1 = a;
		v2 = b;
		weight = c;
	}
	int v1 = 0;
	int v2 = 0;
	int weight = 0;
};

class Enode
{
public:
	int num_node = 0;						//临界矩阵节点数
	int num_edge = 0;						//边数
	bool undirect = false;					//是否为有向边的标志
	int graph[100][100];					//邻接矩阵
	int data[100];							//节点存储数据可以更改
	int queue[100];							//实现bsf的队列
	int toptr = -1;							//栈帧
	bool visited[100];						//是否被访问过的标记
	Enode()									//构造函数初始化矩阵和访问标记
	{
		for (int i = 0; i < 100; i++)
		{
			visited[i] = false;
			for (int j = 0; j < 10; j++)
				graph[i][j] = -0x33333333;
		}
	}
	int *insert()							//向矩阵中和数据表中输入数据
	{
		int a1 = 0, a2 = 0, we = 0;
		int v1 = 0, v2 = 0, da = 0;
		datatxt >> a1 >> a2;
		num_node = a1;
		num_edge = a2;
		edge temp;
		for (int i = 0; i < num_node; i++)
		{
			datatxt >> v1 >> da;
			temp.set(v1, v1, 0);
			data[v1] = da;
			graph[temp.v1][temp.v1] = temp.weight;
		}
		for (int i = 0; i < num_edge; i++)
		{
			datatxt >> v1 >> v2 >> we;
			temp.set(v1, v2, we);
			graph[temp.v1][temp.v2] = temp.weight;
			if (undirect)
				graph[temp.v2][temp.v1] = temp.weight;
		}
		return &graph[temp.v2][temp.v1];
	}
	bool visit(vertex v)					//访问并打印节点
	{
		if (v >= 0 && v <= num_node)
		{
			printf("节点%d对应节点数据%d\n", v, data[v]);
			visited[v] = true;
			return true;
		}
		else return false;
	}
	int dfs(vertex v = 1)					//深度优先遍历
	{
		if (v >= 0 && v <= num_node)
		{
			visit(v);
			for (int i = 0; i <= num_node; i++)
			{
				if (graph[v][i] > 0 && visited[i] == false)
					dfs(i);
			}
		}
		return 0;
	}
	void print()							//输出矩阵中内容，辅助观察debug
	{
		for (int i = 0; i < num_node; i++)
		{
			for (int j = 0; j <= num_node; j++)
			{
				if (graph[i][j] > 0)
					cout << i << " " << j << " " << graph[i][j] << " " << data[i] << endl;
			}
		}
	}
	void setvisit()							//清空visited的标记
	{
		for (int i = 0; i < 100; i++)
			visited[i] = false;
	}
	int push(vertex v)
	{
		if (v >= 0 && toptr < 100)
		{
			queue[++toptr] = v;
			return 0;
		}
		else return -1;
	}
	vertex pop()
	{
		if (toptr >= 0)
		{
			int u = queue[0];
			for(int i = 0; i < toptr; i++)
			{
				queue[i] = queue[i + 1];
			}
			toptr--;
			return u;
		}
		else return -1;
	}
	int bsf(vertex v = 1)					//广度优先遍历
	{
		push(v);
		while (toptr >= 0)
		{
			v = pop();
			if (!visited[v])
			{
				visit(v);
				for (int i = 0; i <= num_node; i++)
				{
					if (graph[v][i] >= 0)
						push(i);
				}
			}
		}
		return 0;
	}
};


int main()
{
	Enode x;
	x.insert();
	x.dfs();
	x.setvisit();
	cout << endl;
	x.bsf();
	return 0;
}

