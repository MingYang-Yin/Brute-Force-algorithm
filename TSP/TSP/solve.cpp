#include <iostream>
#include <vector>
#define NodeNum 4
using namespace std;
int cost = 10000;//�������
int graphCost[NodeNum][NodeNum];//������۾���
int allPath[100][NodeNum + 1] = { -1 };//��������õ�������·��
bool visit[NodeNum] = { 0 };//��¼����Ƿ񱻷��ʹ�
int index = 0;

bool flag = true;//��¼�û������Ƿ�Ϊ������
int examine(char a[]) {//����û��������Ƿ�Ϊ����
	flag = true;
	int i = 0;
	int result = 0;
	for (; a[i] != 0; i++) {
		if (a[i] < 48 || a[i]>57) {
			cout << "������һ����������" << endl;
			flag = false;
			break;
		}
	}
	if (flag) {
		for (int j = 0; a[j] != 0; j++) {//���û�����������ַ�ת��Ϊ��
			result = result + (a[j] - 48) * pow(10, i - j - 1);
		}
	}
	return result;
}

void result(vector<int>seq) {
	int temp = 0;
	int pre = -1;
	int i = 1;
	cout << "�߹��Ľ����������Ϊ";
	for (int ele : seq) {
		cout << ele + 1 << " ";
		if (pre != -1) {
			temp += graphCost[pre][ele];
		}
		pre = ele;
		allPath[index][i] = ele;//����·��
		i++;
	}
	cout << seq.front() + 1;
	temp += graphCost[seq.back()][seq.front()];
	allPath[index][0] = temp;//�������
	if (temp < cost) {
		cost = temp;
	}
	cout << "   ����Ϊ��" << temp << "\n";
	index++;
}


void dfs(vector<int>seq, int begin) {//�㷨��Ҫ����
	for (int i = 0; i < NodeNum; i++) {
		if (i == begin)//·������㱻ָ�����������
			continue;
		else {
			if (!visit[i]) {//����һ�����֮��Ľ��δ���ʹ����������²���
				visit[i] = 1;//����
				seq.push_back(i);//����·������
				dfs(seq, begin);//�������еݹ����
				seq.erase(find(seq.begin(), seq.end(), i));//��·�������в����ý��
				visit[i] = false;//���÷��ʱ�־
			}
		}
	}
	if (seq.size() == NodeNum) {//��һ·��������ȫ���Ľ�㣬���ӡ
		result(seq);
	}
	return;
}

void search(vector<int>seq, int begin) {//Ѱ����begin��Ϊ��������·��
	visit[begin] = 1;
	seq.push_back(begin);
	dfs(seq, begin);
}

int main() {
	//�û�������۾���
	cout << "��������۾���\n";
	char tempL[20];//��ʱ�����û�������
	for (int i = 0; i < NodeNum; i++) {
		for (int j = 0; j < NodeNum; j++) {
			if (j == i) {
				graphCost[i][j] = -1;
			}
			else {
				cout << "��������" << i + 1 << "����" << j + 1 << "֮��Ĵ��ۣ�";
				cin >> tempL;
				graphCost[i][j] = examine(tempL);//�����û�����
				if (!flag) {
					j--;
				}
			}
		}
	}
	cout << "\n-----------------------------------------------------\n";
	cout << "����·������������£�\n";
	vector<int> seq;//�����߹��Ľ������
	for (int k = 0; k < NodeNum; k++) {
		cout << "\n       *�ӵ�" << k + 1 << "���������õ���·��*              \n";
		search(seq, k);//Ѱ����k��Ϊ��������·��
		for (int i = 0; i < NodeNum; i++) {//����visit����
			visit[i] = 0;
		}
		seq.clear();
	}
	cout << "\n-----------------------------------------------------\n";
	cout << "��С����Ϊ" << cost << "��ʵ�ָô��۵�·�����£�\n";
	for (int i = 0; i < 100; i++) {//����С·��
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
