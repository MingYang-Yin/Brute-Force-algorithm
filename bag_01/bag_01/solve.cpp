#include <iostream>
#include <vector>
#define SUM 4
#define WEIGHT 10
using namespace std;
struct goods {
	int weight;
	int value;
};//��������������ͼ�ֵ
struct goods goods[SUM];//��������
bool visit[SUM] = { 0 };//���������Ƿ񱻷��ʹ�
int index = 0;
int preNode = 0;
int maxValue = 0;//��������ֵ
int allPath[100][SUM + 1] = { -1 };

bool flag = true;//��¼�û������Ƿ�Ϊ������
void result(int currentWeight, vector<int>seq);
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

void traverse(int currentWeight, vector<int>seq) {//��������ĺ������㷨��Ҫ����
	for (int i = 0; i < SUM; i++) {
		if (!visit[i]) {//����Ԫ��δ���ʹ����������²���
			//�����������֮�ʹ���������/����ű�ǰһ�����ʵ����С��������
			if (currentWeight + goods[i].weight > WEIGHT || i < preNode)
				continue;
			visit[i] = 1;//���򣬷��ʸ����壬��visit������1
			seq.push_back(i);//������Ʒ��ŷ���������
			preNode = i;//����ǰһ����������
			//�ݹ����
			traverse((currentWeight + goods[i].weight), seq);
			//��ӡ�����Ʒ���к󣬲���һ��������״̬�������������
			//�൱�ڽ�����Ʒ�ӱ�����ȡ����������ڸ���Ʒ֮���Ԫ�س��Է��뱳��
			seq.erase(find(seq.begin(), seq.end(), i));
			visit[i] = false;
		}
	}
	//��forѭ��������˵�����ҵ�����Ʒi��ʼ�ĵ�һ����Ʒ����
	if (seq.size() > 0) {//�޳�Ϊ�յ����
		result(currentWeight, seq);//��ӡ���
	}
	preNode--;//ǰһ����Ʒ����ż�һ
	return;
}

void result(int currentWeight, vector<int>seq) {
	int sumVal = 0;
	int j = 1;
	for (int i = 0; i < SUM; i++) {
		if (visit[i])
			sumVal += goods[i].value;
	}

	cout << "������װ�����ƷΪ��";
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
	cout << "��\t������Ϊ��" << currentWeight << "��";
	cout << "\t�ܼ�ֵΪ��" << sumVal << "\n";
}

int main() {
	vector<int> seq;
	char tempL[20];//��ʱ�����û�������
	cout << "\n--------------------����������Ϊ" << WEIGHT << "����Ʒ����Ϊ" << SUM << "-------------------\n\n";
	//��ȡ�û�����������ͼ�ֵ
	for (int i = 0; i < SUM; i++)
	{
		cout << "�������" << i + 1 << "����Ʒ��������";
		cin >> tempL;
		goods[i].weight = examine(tempL);//�����û�����
		if (!flag) {
			i--;
		}
	}
	cout << "\n";
	for (int j = 0; j < SUM; j++)
	{
		cout << "�������" << j + 1 << "����Ʒ�ļ�ֵ��";
		cin >> tempL;
		goods[j].value = examine(tempL);//�����û�����
		if (!flag) {
			j--;
		}
	}
	cout << "\n--------------------------------------------------------\n";
	traverse(0, seq);//ִ�б����㷨
	cout << "\n--------------------------------------------------------\n";
	cout << "��ǰ������װ����Ʒ������ֵΪ" << maxValue << "���õ�����Ʒ���Ϊ��\n";
	for (int i = 0; allPath[i][0] != 0; i++) {//��ӡ����ֵ����Ʒ���
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