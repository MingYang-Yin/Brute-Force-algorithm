#include <iostream>
using namespace std;
int girl[100][100] = { -1 };//储存女士的喜好表
int man[100][100] = { -1 };//储存男士的喜好表
int match[100] = { -1 };//储存婚姻匹配结果(男士序号)
int num = 0;//储存参与婚姻匹配的女士/男士人数
int mans_girl[100] = { 0 };//储存每个男士的好感度列表的遍历程度
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

void getUserInput() {//获取用户输入的男/女士好感度
	int sence = -1;
	char tempL[20];//暂时储存用户的输入
	cout << "请输入男士/女士的数量（不能超过100）：";
	cin >> tempL;
	num = examine(tempL);//检验用户输入
	while (!flag || num > 100) {//检验用户输入
		if (num > 100) {
			cout << "男士/女士的数量不能超过100\n";
		}
		cout << "请输入男士/女士的数量（不能超过100）：";
		cin >> tempL;
		num = examine(tempL);
	}
	cout << "定义：用数字1~" << num << "表示好感度（数字越大，好感度越高且好感度要唯一）";
	cout << "\n-----------------------------------------------------\n";
	cout << "          *输入女士好感度*           \n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << "请输入第" << i + 1 << "位女士对第" << j + 1 << "位男士的好感度：";
			cin >> tempL;
			girl[i][j] = examine(tempL);//检验用户输入
			if (!flag || girl[i][j] > num) {
				if (girl[i][j] > num)
					cout << "好感度不能大于" << num << "\n";
				j--;
			}
			for (int y = 0; y < j; y++) {
				if (girl[i][y] == girl[i][j]) {
					cout << "好感度要唯一\n";
					j--;
					break;
				}
			}
		}
		cout << "\n";
	}
	cout << "          *输入男士好感度*           \n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			bool test = true;
			cout << "请输入第" << i + 1 << "位男士对第" << j + 1 << "位女士的好感度：";
			cin >> tempL;
			sence = examine(tempL);//检验用户输入
			if (!flag || sence > num) {
				if (sence > num)
					cout << "好感度不能大于" << num << "\n";
				j--;
				test = false;
			}
			else if (man[i][num - sence] != -1) {
				cout << "好感度要唯一";
				j--;
				test = false;
				break;
			}
			if (test) {
				man[i][num - sence] = j;//储存好感度为sence的女士的序号(在第0位储存最喜爱的女士序号)
			}

		}
		cout << "\n";
	}
	cout << "\n-----------------------------------------------------\n";
}

void matching() {
	bool matchGirl[100] = { 0 };//储存女士是否被分配
	bool matchMan[100] = { 0 };//储存男士是否被分配
	int matchingMan = 0;//储存被分配的男士数量
	int temp = -1;
	while (matchingMan < num) {//当男士没有被全部分配时，执行循环
		for (int i = 0; i < num; i++) {
			if (matchMan[i] == false) {//若该男士(序号为i)没有婚配，为他选择婚配对象
				for (int j = mans_girl[i]; j < num&&matchMan[i] == false; j++) {
					int temp = man[i][j];//储存目前好感度最大的女士序号
					if (matchGirl[temp] == false) {//若该女士未被分配，直接将该女士分配给该男士
						match[temp] = i;//在婚姻匹配结果表中储存男士序号
						mans_girl[i] = j + 1;//若分配的女士被夺走，下一个从列表的j+1处查找
						matchGirl[temp] = true;//改变该女士分配状态
						matchMan[i] = true;//改变该男士分配状态
						matchingMan++;//被分配的男士数量+1
					}
					else {//该女士已有配偶，则检查该女士对当前配偶和该男士的好感度
						if (girl[temp][match[temp]] < girl[temp][i]) {//若该女士对该男士的好感更高，发生配偶替换
							matchMan[match[temp]] = false;//改变该女士配偶的分配状态
							matchMan[i] = true;////改变该男士分配状态
							match[temp] = i;//更新婚姻匹配结果表
							mans_girl[i] = j + 1;//若分配的女士被夺走，下一个从列表的j+1处查找
						}
					}
				}
			}
		}
	}
}


void printResult() {//打印婚姻匹配结果
	cout << "结果：\n";
	for (int i = 0; i < num; i++) {
		cout << "第" << i + 1 << "位女士" << "---" << "第" << match[i] + 1 << "位男士\n";
	}
}

int main() {
	for (int ii = 0; ii < 100; ii++) {
		for (int jj = 0; jj < 100; jj++) {
			man[ii][jj] = -1;
		}
	}
	getUserInput();//获取用户输入
	matching();//匹配婚姻
	printResult();//打印结果
	system("pause");
	return 0;
}