#include <iostream>
#include <vector>
#define NodeNum 4
using namespace std;
int cost = 10000;//储存代价
int graphCost[NodeNum][NodeNum];//储存代价矩阵
int allPath[100][NodeNum + 1] = { -1 };//储存遍历得到的所有路径
bool visit[NodeNum] = { 0 };//记录结点是否被访问过
int index = 0;

bool flag = true;//记录用户输入是否为正整数
int examine(char a[]) {//检测用户的输入是否为数字
	flag = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "请输入一个正整数！" << endl;
			flag = false;
			break;
		}
	}
	if (flag) {
		for (int j = 0; a[j] != 0; j++) {//将用户输入的数字字符转化为数
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
	}
	return result;
}

void result(vector<int>seq) {
	int temp = 0;
	int pre = -1;
	int i = 1;
	cout << "走过的结点序列依次为";
	for (int ele : seq) {
		cout << ele + 1 << " ";
		if (pre != -1) {
			temp += graphCost[pre][ele];
		}
		pre = ele;
		allPath[index][i] = ele;//储存路径
		i++;
	}
	cout << seq.front() + 1;
	temp += graphCost[seq.back()][seq.front()];
	allPath[index][0] = temp;//储存代价
	if (temp < cost) {
		cost = temp;
	}
	cout << "   代价为：" << temp << "\n";
	index++;
}


void dfs(vector<int>seq, int begin) {//算法主要部分
	for (int i = 0; i < NodeNum; i++) {
		if (i == begin)//路径的起点被指定，无需操作
			continue;
		else {
			if (!visit[i]) {//若有一除起点之外的结点未访问过，进行以下操作
				visit[i] = 1;//访问
				seq.push_back(i);//加入路径序列
				dfs(seq, begin);//继续进行递归操作
				seq.erase(find(seq.begin(), seq.end(), i));//从路径序列中擦除该结点
				visit[i] = false;//重置访问标志
			}
		}
	}
	if (seq.size() == NodeNum) {//若一路径访问了全部的结点，则打印
		result(seq);
	}
	return;
}

void search(vector<int>seq, int begin) {//寻找以begin作为起点的所有路径
	visit[begin] = 1;
	seq.push_back(begin);
	dfs(seq, begin);
}

int main() {
	//用户输入代价矩阵
	cout << "请输入代价矩阵：\n";
	char tempL[20];//暂时储存用户的输入
	for (int i = 0; i < NodeNum; i++) {
		for (int j = 0; j < NodeNum; j++) {
			if (j == i) {
				graphCost[i][j] = -1;
			}
			else {
				cout << "请输入结点" << i + 1 << "与结点" << j + 1 << "之间的代价：";
				cin >> tempL;
				graphCost[i][j] = examine(tempL);//检验用户输入
				if (!flag) {
					j--;
				}
			}
		}
	}
	cout << "\n-----------------------------------------------------\n";
	cout << "所有路径及其代价如下：\n";
	vector<int> seq;//储存走过的结点序列
	for (int k = 0; k < NodeNum; k++) {
		cout << "\n       *从第" << k + 1 << "个结点出发得到的路径*              \n";
		search(seq, k);//寻找以k作为起点的所有路径
		for (int i = 0; i < NodeNum; i++) {//重置visit数组
			visit[i] = 0;
		}
		seq.clear();
	}
	cout << "\n-----------------------------------------------------\n";
	cout << "最小代价为" << cost << "，实现该代价的路径如下：\n";
	for (int i = 0; i < 100; i++) {//找最小路径
		if (allPath[i][0] == cost) {
			for (int j = 0; j < NodeNum; j++) {
				cout << allPath[i][j + 1] + 1 << " ";
			}
			cout << allPath[i][1] + 1;
			cout << "\n";
		}
	}
	system("pause");
	return 0;
}
