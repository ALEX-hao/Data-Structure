#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}//��ȡ���ֵ

int main() {

	cout << "**********************************************"
		<< endl << endl << endl
		<< "xx SA21xxxxxxxx"
		<< endl << endl << "����������data.txt" << endl
		<< "**********************************************"
		<< endl << endl;

	int n = 0, v = 0, c = 0, bag = 0;
	//������ ��Ʒ���� ��ֵ ��� ��������
	fstream data;
	data.open("data.txt");
	data >> n >> bag;
	vector<int> value(n+1), capacity(n+1);
	vector<vector<int>> dp;		//dp�������ڼ�¼��̬����		
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
		cout << "��" << k + 1 << "������" << endl;
		for (int i = 1; i <= n; i++) {
			data >> c >> v;
			cout<<"��"<<i<<"����Ʒ" <<"  ������" << c <<"  ��ֵ��" << v << endl;
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
		cout << "��" << k + 1 << "������" << "�������Ϊ��" << endl;
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