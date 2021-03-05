#include <iostream>
#include <vector>
#define SUM 4
#define WEIGHT 10
using namespace std;
struct goods {
	int weight;
	int value;
};//储存物体的重量和价值
struct goods goods[SUM];//物体数组
bool visit[SUM] = { 0 };//储存物体是否被访问过
int index = 0;
int preNode = 0;
int maxValue = 0;//储存最大价值
int allPath[100][SUM + 1] = { -1 };

bool flag = true;//记录用户输入是否为正整数
void result(int currentWeight, vector<int>seq);
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

void traverse(int currentWeight, vector<int>seq) {//遍历物体的函数，算法主要部分
	for (int i = 0; i < SUM; i++) {
		if (!visit[i]) {//若该元素未访问过，进行以下操作
			//如果物体重量之和大于总重量/该序号比前一个访问的序号小，则跳过
			if (currentWeight + goods[i].weight > WEIGHT || i < preNode)
				continue;
			visit[i] = 1;//否则，访问该物体，将visit数组置1
			seq.push_back(i);//将该物品序号放入序列中
			preNode = i;//更新前一个物体的序号
			//递归遍历
			traverse((currentWeight + goods[i].weight), seq);
			//打印最大物品序列后，擦除一个，重置状态，继续往后遍历
			//相当于将该物品从背包中取出，将序号在该物品之后的元素尝试放入背包
			seq.erase(find(seq.begin(), seq.end(), i));
			visit[i] = false;
		}
	}
	//当for循环结束，说明已找到以物品i开始的的一个物品序列
	if (seq.size() > 0) {//剔除为空的情况
		result(currentWeight, seq);//打印结果
	}
	preNode--;//前一个物品的序号减一
	return;
}

void result(int currentWeight, vector<int>seq) {
	int sumVal = 0;
	int j = 1;
	for (int i = 0; i < SUM; i++) {
		if (visit[i])
			sumVal += goods[i].value;
	}

	cout << "背包中装入的物品为：";
	for (int ele : seq) {
		cout << ele + 1 << " ";
		allPath[index][j] = ele + 1;
		j++;
	}
	if (sumVal > maxValue) {
		maxValue = sumVal;
	}
	allPath[index][0] = sumVal;
	index++;
	cout << "；\t总重量为：" << currentWeight << "；";
	cout << "\t总价值为：" << sumVal << "\n";
}

int main() {
	vector<int> seq;
	char tempL[20];//暂时储存用户的输入
	cout << "\n--------------------背包总容量为" << WEIGHT << "，物品总数为" << SUM << "-------------------\n\n";
	//获取用户输入的重量和价值
	for (int i = 0; i < SUM; i++)
	{
		cout << "请输入第" << i + 1 << "个物品的重量：";
		cin >> tempL;
		goods[i].weight = examine(tempL);//检验用户输入
		if (!flag) {
			i--;
		}
	}
	cout << "\n";
	for (int j = 0; j < SUM; j++)
	{
		cout << "请输入第" << j + 1 << "个物品的价值：";
		cin >> tempL;
		goods[j].value = examine(tempL);//检验用户输入
		if (!flag) {
			j--;
		}
	}
	cout << "\n--------------------------------------------------------\n";
	traverse(0, seq);//执行遍历算法
	cout << "\n--------------------------------------------------------\n";
	cout << "当前背包中装入物品的最大价值为" << maxValue << "，得到的物品组合为：\n";
	for (int i = 0; allPath[i][0] != 0; i++) {//打印最大价值的物品组合
		if (allPath[i][0] == maxValue) {
			for (int j = 1; j < SUM + 1 && allPath[i][j] != 0; j++) {
				cout << allPath[i][j] << " ";
			}
			cout << "\n";
		}
	}
	system("pause");
	return 0;
}