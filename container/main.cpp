#define MAX_LEN_STRING 12

#include <clocale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <set>
#include <string>

#include "interface.h"
#include "avltree.h"

using namespace std;

//������� ����������
void demoInterface(Interface &container) {
	cout << "������������ ������ ����������:" << endl;
	string s1 = "abcd";
	string s2 = "ef";
	string s3 = "xyz";
	string s4 = "hi";

	//���������� �����
	container.addValue(&s1);
	cout << s1 << " ���������." << endl;
	container.addValue(&s2);
	cout << s2 << " ���������." << endl;
	container.addValue(&s3);
	cout << s3 << " ���������." << endl;

	//����� ������
	if (container.findValue(&s4) == true)
		cout << s4 << " �������." << endl;
	else
		cout << s4 << " �� ������� � ����������." << endl;

	if (container.findValue(&s1) == true)
		cout << s1 << " �������." << endl;
	else
		cout << s1 << " �� ������� � ����������." << endl;


	//�������� �����
	if (container.deleteValue(&s4) == true)
		cout << s4 << " �������." << endl;
	else
		cout << s4 << " �� �������, ��� ��� ��� � ����������." << endl;

	if (container.deleteValue(&s2) == true)
		cout << s2 << " �������." << endl;
	else
		cout << s2 << " �� �������, ��� ��� ��� � ����������." << endl;
}

//��������� ������� ������ ���������� ������ ��� ������ AVL ���������� � ������ � ����
void generatorData() {
	srand((unsigned int)time(NULL));	//��������� ���������
	int numString = rand() + 1;				//���������� �����. ��������� �� 1 �� 32768.
	int lenString;						//����� ������� ������			
	ofstream out("InputData.txt");
	if (out.is_open()) {
		for (int i = 0;i < numString;i++) {
			lenString = rand() % MAX_LEN_STRING;
			for (int j = 0; j < lenString;j++) {
				out.put(rand() % 26 + 97);
			}
			out.put('\n');
		}
	}
	out.close();
}

//������ ������ � ���������
void readDataInContainer(Interface &container) {
	string str;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		while (getline(in, str, '\n')) {
			container.addValue(&str);
		}
		clock_t finish = clock();
		cout << "����� ���������� � ��������� ��������� ����������� �����: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "���� InputData.txt �� ������ ��� �� ������� �������." << endl;
	}
	in.close();
}

//������ ������ � set
void readDataInSet(set <string> &containerSet) {
	//char *str = (char*)malloc(sizeof(char));
	string str;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		//while (in.getline(str, MAX_LEN_STRING)) {
		while (getline(in, str)) {
			containerSet.insert(str);
			//char *str = (char*)malloc(sizeof(char));
		}
		clock_t finish = clock();
		cout << "����� ���������� � ��������� set ����������� ����� (���): " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "���� InputData.txt �� ������ ��� �� ������� �������." << endl;
	}
	in.close();
}

//������� �������
int main() {
	setlocale(LC_ALL, "Russian");

	//1. ������������ ������ ����������
	AVLTree container;
	demoInterface(container);

	//4. ��������� ������� ������ ���������� ������ ��� ������ AVL ����������.
	cout << "��������� ��������� �������� ���������� � ����������:" << endl;
	//4.1. ���������� ������ � ���������� � ����
	generatorData();

	//4.2. C������� ���������� �������� ���������� � ��������� ����������� �����
	AVLTree container2;
	readDataInContainer(container2);

	//4.3. C������� ���������� �������� ���������� � ��������� std:set
	set <string> containerSet;
	readDataInSet(containerSet);

	system("pause");
	return 0;
}