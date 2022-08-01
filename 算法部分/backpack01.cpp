#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}//获取最大值

int main() {

	cout << "**********************************************"
		<< endl << endl << endl
		<< "xx SA21xxxxxxxx"
		<< endl << endl << "测试数据在data.txt" << endl
		<< "**********************************************"
		<< endl << endl;

	int n = 0, v = 0, c = 0, bag = 0;
	//依次是 物品数量 价值 体积 背包容量
	fstream data;
	data.open("data.txt");
	data >> n >> bag;
	vector<int> value(n+1), capacity(n+1);
	vector<vector<int>> dp;		//dp数组用于记录动态过程		
	value.clear();
	capacity.clear();
	dp.clear();
	value.push_back(0);
	capacity.push_back(0);


	vector<int> temp(bag+1, 0);

	for (int i = 0; i <= n; i++) {
		dp.push_back(temp);
	}

	for (int k = 0; k < 5; k++) {
		cout << "第" << k + 1 << "组数据" << endl;
		for (int i = 1; i <= n; i++) {
			data >> c >> v;
			cout<<"第"<<i<<"个物品" <<"  容量：" << c <<"  价值：" << v << endl;
			capacity.push_back(c);
			value.push_back(v);
		}
		for (int i = 1; i <= n; i++)
			for (int j = bag; j >= 0; j--) {
				if (j < capacity[i]) {
					dp[i][j] = dp[i - 1][j];
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - capacity[i]] + value[i]);
				}
			}
		cout << "第" << k + 1 << "组数据" << "最大收益为：" << endl;
		cout << dp[n][bag] << endl << endl;
		capacity.clear();
		value.clear();
		value.push_back(0);
		capacity.push_back(0);
		dp.clear();
		for (int i = 0; i <= n; i++) {
			dp.push_back(temp);
		}
	}

	return 0;
}