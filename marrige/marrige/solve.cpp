#include <iostream>
using namespace std;
int girl[100][100] = { -1 };//����Ůʿ��ϲ�ñ�
int man[100][100] = { -1 };//������ʿ��ϲ�ñ�
int match[100] = { -1 };//�������ƥ����(��ʿ���)
int num = 0;//����������ƥ���Ůʿ/��ʿ����
int mans_girl[100] = { 0 };//����ÿ����ʿ�ĺøж��б�ı����̶�
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

void getUserInput() {//��ȡ�û��������/Ůʿ�øж�
	int sence = -1;
	char tempL[20];//��ʱ�����û�������
	cout << "��������ʿ/Ůʿ�����������ܳ���100����";
	cin >> tempL;
	num = examine(tempL);//�����û�����
	while (!flag || num > 100) {//�����û�����
		if (num > 100) {
			cout << "��ʿ/Ůʿ���������ܳ���100\n";
		}
		cout << "��������ʿ/Ůʿ�����������ܳ���100����";
		cin >> tempL;
		num = examine(tempL);
	}
	cout << "���壺������1~" << num << "��ʾ�øжȣ�����Խ�󣬺øж�Խ���Һøж�ҪΨһ��";
	cout << "\n-----------------------------------------------------\n";
	cout << "          *����Ůʿ�øж�*           \n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << "�������" << i + 1 << "λŮʿ�Ե�" << j + 1 << "λ��ʿ�ĺøжȣ�";
			cin >> tempL;
			girl[i][j] = examine(tempL);//�����û�����
			if (!flag || girl[i][j] > num) {
				if (girl[i][j] > num)
					cout << "�øжȲ��ܴ���" << num << "\n";
				j--;
			}
			for (int y = 0; y < j; y++) {
				if (girl[i][y] == girl[i][j]) {
					cout << "�øж�ҪΨһ\n";
					j--;
					break;
				}
			}
		}
		cout << "\n";
	}
	cout << "          *������ʿ�øж�*           \n";
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			bool test = true;
			cout << "�������" << i + 1 << "λ��ʿ�Ե�" << j + 1 << "λŮʿ�ĺøжȣ�";
			cin >> tempL;
			sence = examine(tempL);//�����û�����
			if (!flag || sence > num) {
				if (sence > num)
					cout << "�øжȲ��ܴ���" << num << "\n";
				j--;
				test = false;
			}
			else if (man[i][num - sence] != -1) {
				cout << "�øж�ҪΨһ";
				j--;
				test = false;
				break;
			}
			if (test) {
				man[i][num - sence] = j;//����øж�Ϊsence��Ůʿ�����(�ڵ�0λ������ϲ����Ůʿ���)
			}

		}
		cout << "\n";
	}
	cout << "\n-----------------------------------------------------\n";
}

void matching() {
	bool matchGirl[100] = { 0 };//����Ůʿ�Ƿ񱻷���
	bool matchMan[100] = { 0 };//������ʿ�Ƿ񱻷���
	int matchingMan = 0;//���汻�������ʿ����
	int temp = -1;
	while (matchingMan < num) {//����ʿû�б�ȫ������ʱ��ִ��ѭ��
		for (int i = 0; i < num; i++) {
			if (matchMan[i] == false) {//������ʿ(���Ϊi)û�л��䣬Ϊ��ѡ��������
				for (int j = mans_girl[i]; j < num&&matchMan[i] == false; j++) {
					int temp = man[i][j];//����Ŀǰ�øж�����Ůʿ���
					if (matchGirl[temp] == false) {//����Ůʿδ�����䣬ֱ�ӽ���Ůʿ���������ʿ
						match[temp] = i;//�ڻ���ƥ�������д�����ʿ���
						mans_girl[i] = j + 1;//�������Ůʿ�����ߣ���һ�����б��j+1������
						matchGirl[temp] = true;//�ı��Ůʿ����״̬
						matchMan[i] = true;//�ı����ʿ����״̬
						matchingMan++;//���������ʿ����+1
					}
					else {//��Ůʿ������ż�������Ůʿ�Ե�ǰ��ż�͸���ʿ�ĺøж�
						if (girl[temp][match[temp]] < girl[temp][i]) {//����Ůʿ�Ը���ʿ�ĺøи��ߣ�������ż�滻
							matchMan[match[temp]] = false;//�ı��Ůʿ��ż�ķ���״̬
							matchMan[i] = true;////�ı����ʿ����״̬
							match[temp] = i;//���»���ƥ������
							mans_girl[i] = j + 1;//�������Ůʿ�����ߣ���һ�����б��j+1������
						}
					}
				}
			}
		}
	}
}


void printResult() {//��ӡ����ƥ����
	cout << "�����\n";
	for (int i = 0; i < num; i++) {
		cout << "��" << i + 1 << "λŮʿ" << "---" << "��" << match[i] + 1 << "λ��ʿ\n";
	}
}

int main() {
	for (int ii = 0; ii < 100; ii++) {
		for (int jj = 0; jj < 100; jj++) {
			man[ii][jj] = -1;
		}
	}
	getUserInput();//��ȡ�û�����
	matching();//ƥ�����
	printResult();//��ӡ���
	system("pause");
	return 0;
}