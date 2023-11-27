#include <iostream>
#include <vector>
#include "queue.h"
#include <fstream>
#include <string>
#include <array>
using namespace std;

//����� ��������� 
class Point
{
public:
	int x;
	int y;
	Point(int yourX, int yourY)
	{
		x = yourX;
		y = yourY;
	}
};


array <Point, 4> directions   //������� ��� ������� (����������� ��������)
{
  {
	{0,1},
	{0,-1},
	{1,0},
	{-1,0}
  }
};
//����� ����� �����(����������) �� ������ �� ���������. ����� ������������ � ���� ���������� ������������� �������.
int** road_map_of_maze(vector<string>& maze, int x, int y) {
	int** paths = new int* [maze.size()];

	for (size_t i = 0; i < maze.size(); i++)
	{
		paths[i] = new int[maze[i].size()];
		for (size_t l = 0; l < maze[i].size(); l++)
		{
			paths[i][l] = 0;
		}
	}
	paths[x][y] = 1;
	return paths;
}
void Wave_Algorithm(Queue* queue, int** paths, vector<string>& maze)
{

	while (!queue_empty(queue))
	{
		//�������� ������� x �  y �� �������
		int CurX = queue_get(queue);
		queue_remove(queue);
		int CurY = queue_get(queue);
		queue_remove(queue);
		//�������� �� ���� ������������ 
		for (auto dir : directions)
		{
			int newX = CurX + dir.x;
			int newY = CurY + dir.y;
			//�������� �� ���������� ��������� � �������� ���������
			if (newX >= 0 && newX < static_cast<int>(maze.size()) && newY >= 0 && newY < static_cast<int>(maze[1].size()))
			{
				if (paths[newX][newY] == 0 && maze[newX][newY] != '#')
				{
					//����� ���������� �� ������� ����� 
					paths[newX][newY] = paths[CurX][CurY] + 1;
					//��������� ���������� � �������
					queue_insert(queue, static_cast<Data>(newX));
					queue_insert(queue, static_cast<Data>(newY));
				}
			}
		}
	}
	
}
//�������� �������� ������ ����� 
void Answer_Print(int** paths, vector<string>& maze, int EndX, int EndY)
{
	if (paths[EndX][EndY]) //���� �� ����
	{
		while (paths[EndX][EndY] - 1 != 1) // ���� �� ��������� �� ������ ���������
		{

			for (auto dir : directions)
			{
				int CurrX = EndX + dir.x;
				int CurrY = EndY + dir.y;

				//���c������ �� 1 ������ �� ������� ������� ���������� 'x' � ������� ������� ����������� �� ��� �������
				if (paths[EndX][EndY] - 1 == paths[CurrX][CurrY])
				{
					maze[CurrX][CurrY] = 'x';
					EndX = CurrX;
					EndY = CurrY;
				}
			}
		}
		//����� ���� ���������
		for (size_t i = 0; i < maze.size(); i++)
		{
			cout << maze[i] << endl;
		}

	}
	//���� ���� ���
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}
	

}
int main()
{

	Queue* queue = queue_create(); //������ �������
	//������������� ��������� ����� � ������ �� ���������
	Point start(-1, -1);
	Point end(-1, -1);
	//����� �������������

	//���� ���������
	vector<string> maze; //��������
	string buffer;
	ifstream getinfo("maze.txt");
	int counter = 0;
	while (getline(getinfo, buffer))
	{
		maze.push_back(buffer);
		for (size_t i = 0; i < maze[counter].size(); i++)
		{
			if (maze[counter][i] == 'X')
			{
				start = Point(int(maze.size()) - 1, i);
				queue_insert(queue, start.x);
				queue_insert(queue, start.y);
			}
			if (maze[counter][i] == 'Y')
			{
				end = Point(int(maze.size()) - 1, i);
			}
		}
		counter++;
	}
	getinfo.close();
	//����� ����� 


	int** paths = road_map_of_maze(maze, start.x, start.y); //����� �����
	Wave_Algorithm(queue, paths, maze);  //�������� �������� ������ ����� 
	Answer_Print(paths, maze, end.x, end.y);  //����� ������ � �������� ������� � ������ ���������

	//�������� �������
	queue_delete(queue);
	//�������� ������� �����
	for (size_t i = 0; i < maze.size(); i++)
	{
		delete[] paths[i];
	}

	delete[] paths;
	return 0;
}