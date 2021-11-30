#include <iostream>
#include "queue.h"
#include "list.h"
#include <math.h>
#include <iomanip>

using namespace std;

const static unsigned int MAX_LINE = 100;
unsigned int xMax, yMax;

void showMatrix(int** mat)
{
	cout << endl;

	int max = 0;

	for (int i = 0; i < xMax; i++)
		for (int j = 0; j < yMax; j++)
			if (mat[i][j] > max)
				max = mat[i][j];

	int out = max == 0 ? 1 : int(log10(max) + 1);

	for (int i = 0; i <= MAX_LINE; i++)
		cout << "-";

	cout << endl;

	for (unsigned int i = 0; i < xMax; i++)
	{
		for (unsigned int j = 0; j < yMax; j++)
			cout << setw(3) << mat[i][j] << " ";
		cout << endl;
	}
}

int setMatrix(int** mat, Queue* qu)
{
	int index = queue_get(qu);
	queue_remove(qu);
	int xpos = queue_get(qu);
	queue_remove(qu);
	int ypos = queue_get(qu);
	queue_remove(qu);


	if (((xpos + 1) < xMax) && (mat[xpos + 1][ypos] == 0))
	{
		mat[xpos + 1][ypos] = index + 1;
		queue_insert(qu, index + 1);
		queue_insert(qu,xpos + 1);
		queue_insert(qu, ypos);
	}
	if (((ypos + 1) < yMax) && (mat[xpos][ypos + 1] == 0))
	{
		mat[xpos][ypos + 1] = index + 1;
		queue_insert(qu, index + 1);
		queue_insert(qu, xpos);
		queue_insert(qu, ypos + 1);
	}
	if (((xpos - 1) < xMax) && (mat[xpos - 1][ypos] == 0))
	{
		mat[xpos - 1][ypos] = index + 1;
		queue_insert(qu, index + 1);
		queue_insert(qu, xpos - 1);
		queue_insert(qu, ypos);
	}
	if (((ypos - 1) < yMax) && (mat[xpos][ypos - 1] == 0))
	{
		mat[xpos][ypos - 1] = index + 1;
		queue_insert(qu, index + 1);
		queue_insert(qu, xpos);
		queue_insert(qu, ypos - 1);
	}

	for (unsigned int x = 0; x < xMax; x++)
		for (unsigned int y = 0; y < yMax; y++)
			if (mat[x][y] == 0)
			{
				index = setMatrix(mat, qu);
			}
	return index;
}

int main()
{
	setlocale(0, "");

	Queue* que = queue_create();

	cout << "Введите размеры матрицы" << endl;

	cout << "X: ";
	cin >> xMax;

	cout << "Y: ";
	cin >> yMax;

	int** matrix = new int* [xMax];
	for (unsigned int i = 0; i < xMax; ++i)
		matrix[i] = new int[yMax];

	for (int i = 0; i < xMax; i++)
		for (int j = 0; j < yMax; j++)
			matrix[i][j] = 0;

	unsigned int posNum;

	cout << "Колличество начальных позиций:";
	cin >> posNum;

	for (unsigned int i = 0; i < posNum; i++)
	{
		unsigned int xPos, yPos;

		cout << i + 1 << ")----------" << endl;

		while (true)
		{
			cout << "X: ";
			cin >> xPos;

			if ((xPos < xMax) && (xPos >= 0))
				break;
			else
				cout << "Неправильное значение начальной позиции." << endl;
		}

		while (true)
		{
			cout << "Y: ";
			cin >> yPos;

			if ((yPos < yMax) && (yPos >= 0))
				break;
			else
				cout << "Неправильное значение начальной позиции." << endl;
		}

		matrix[xPos][yPos] = 1;
		queue_insert(que, matrix[xPos][yPos]);
		queue_insert(que, xPos);
		queue_insert(que, yPos);
	}

	int res = setMatrix(matrix, que);
	showMatrix(matrix);

	cout << "Колличество ходов: " << res+1;
}