#include <iostream>
#include <fstream>
#include <locale>
#include "queue.h"
using namespace std;

//������� ������ ������ �� �����
char** readFile(int &numCol, int &numRow) {
	numCol = 0, numRow = 0;
	int i = 0;
	char **labir = NULL;	//������������� ���������� ������� ��� ���������
	string line;			//������, ������� ����� �������������� ��� ������ �� �����
	ifstream in("input.txt");	//������� ����
	if (in.is_open())	//���� ���� ������� �������
	{
		while (getline(in, line)) {	//��������� ���� ��� �������� ����� ������ numRow
			numRow++;
		}
		numCol = line.size();	//����� �������
		labir = new char*[numRow];	//�������� ������ ��� ���������

		cout << "������� ��������������:" << numCol << '*' << numRow << endl;
		cout << "����:" << endl;
		in.clear();				//���������� in ��� ���������� ������ �����
		in.seekg(0, ios::beg);	//
		//��������� ������ �� ����� � ���������� � ������ labir
		while (getline(in, line)) {
			labir[i] = new char[numCol];
			for (int j = 0; j < line.size(); j++) {
				labir[i][j] = line[j];
				cout << labir[i][j];
			}
			cout << endl;
			i++;
		}
	}
	else {
		cout << "���� input.txt �� ������ ��� �� ������� �������." << endl;
	}
	in.close();	//��������� ����
	return labir;	//���������� ������ � ���������� � ������� ������� main
}

//������� ���������� ����������� ���� � ������� ��������� ���������
void findPath(bool &mark, int numCol, int numRow, char **labir, int **visited, int **path, queue &q) {
	int xStartX, yStartX, xEndY, yEndY;	//���������� ������ � ������
	int x, y;	//���������� ��������� ������
	for (int i = 0; i < numRow; i++) {
		visited[i] = new int[numCol];	//�������� ������ ��� �������
		path[i] = new int[numCol];		//�������� ������ ��� �������
		for (int j = 0; j < numCol; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;
			if (labir[i][j] == 'X') { /* ������� ������ ����*/
				xStartX = i;
				yStartX = j;
				q.push(i);  /* ������� ��������� ������ */
				q.push(j);  /* � ���� ��������� */
				path[i][j] = 1;
			}
			else if (labir[i][j] == 'Y') { /* ������� �������� ����� */
				xEndY = i;
				yEndY = j;
			}
		}
	}

	//���� ������� ��������� ������
	while (q.empty() == false) {	//���� ������� �� ������, ������
		x = q.front();	//���� ���������� x ������� �������� �������
		q.pop();		//������� ��� �� �������
		y = q.front();	//���� ���������� y ������� �������� �������
		q.pop();		//������� ��� �� �������

		if (!visited[x][y]) {	//���� ��� �� �������� ������ ������, �� ������ ��� ��� �������� ������
			//��������� �� ����� �� �� ������� ���������, �������� �� �������� ������, ����� �� ������ ����� ����.
			if ((x + 1) < numRow && (x + 1) >= 0 && !visited[x + 1][y] &&
				(labir[x + 1][y] == '.' || labir[x + 1][y] == 'Y')) {
				path[x + 1][y] = path[x][y] + 1;
				q.push(x + 1);
				q.push(y);
			}
			if ((x - 1) < numRow && (x - 1) >= 0 && !visited[x - 1][y] &&
				(labir[x - 1][y] == '.' || labir[x - 1][y] == 'Y')) {
				path[x - 1][y] = path[x][y] + 1;
				q.push(x - 1);
				q.push(y);
			}
			if ((y + 1) < numRow && (y + 1) >= 0 && !visited[x][y + 1] &&
				(labir[x][y + 1] == '.' || labir[x][y + 1] == 'Y')) {
				path[x][y + 1] = path[x][y] + 1;
				q.push(x);
				q.push(y + 1);
			}
			if ((y - 1) < numRow && (y - 1) >= 0 && !visited[x][y - 1] &&
				(labir[x][y - 1] == '.' || labir[x][y - 1] == 'Y')) {
				path[x][y - 1] = path[x][y] + 1;
				q.push(x);
				q.push(y - 1);
			}
			visited[x][y] = 1;	//�������� ��� �������� � ������ ������
		}

		if (visited[xEndY][yEndY]) {	//���� �������� �������� ������
			mark = true;
			x = xEndY;	//x ����� ���������� � ������ Y
			y = yEndY;	//y ����� ���������� y ������ Y
			//�������������� ����������� ����
			while (path[x][y] != 2) {
				if ((x - 1) >= 0 && (x - 1) < numRow && (path[x - 1][y] == path[x][y] - 1)) {
					x = x - 1;
					labir[x][y] = 'x';
				}
				else if ((x + 1) >= 0 && (x + 1) < numRow && (path[x + 1][y] == path[x][y] - 1)) {
					x = x + 1;
					labir[x][y] = 'x';
				}
				else if ((y - 1) >= 0 && (y - 1) < numRow && (path[x][y - 1] == path[x][y] - 1)) {
					y = y - 1;
					labir[x][y] = 'x';
				}
				else if ((y + 1) >= 0 && (y + 1) < numRow && (path[x][y + 1] == path[x][y] - 1)) {
					y = y + 1;
					labir[x][y] = 'x';
				}
			}
		}
	}
}

//������� ������ ������ � ����
void writeFile(bool &mark, int &numCol, int &numRow, char **labir){
	ofstream out("output.txt");	//�������� ����
	if (out.is_open())	//���� ���� ������� �������
	{
		cout << endl;
		cout << "�����:" << endl;
		if (mark == true) {	//���� ����������
			//���������� �������� �� ������� � ����
			for (int i = 0; i < numRow; i++) {
				for (int j = 0; j < numCol; j++) {
					out << labir[i][j];
					cout << labir[i][j];
				}
				out << endl;
				cout << endl;
			}
		}
		else {	//���� �� ����������
			cout << "IMPOSSIBLE" << endl;
			out << "IMPOSSIBLE";
		}
	}
	out.close();
}

//������� �������
int main() {
	setlocale(LC_ALL, "Russian");	//��� ������ ������� ����
	int numCol;	//������ ���������: ����� �������
	int numRow;	//������ ���������: ����� ����(������)
	bool mark = false;	//���� true, �� ���� ����������
	char **labir;	//��������� ������ �������� ��������
	int **visited;	//��������� ������ �������� ���������� ������ ���������
	int **path;		//��������� ������ �������� ���� � ���������
	queue q;		//������� ��������� ������ (������ ����)

	//������� ������ ������ �� �����. ������ �������� ��� �������� � ������ labir
	labir = readFile(numCol, numRow);
	
	visited = new int* [numRow];	//�������� ������ ��� ��������. ������ �� �����������
	path = new int* [numRow];		//

	//������� ������ ����������� ����
	findPath(mark, numCol, numRow, labir, visited, path, q);

	//������� ������ ������ (���������������� ���������) � ����. 
	writeFile(mark,numCol, numRow, labir);

	system("pause");
	return 0;
}