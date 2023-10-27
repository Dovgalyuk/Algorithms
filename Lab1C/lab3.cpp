#include "queue.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//координаты лабиринта
struct Point
{
    int x, y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

vector<vector<char>> maze;//Лабиринт
vector<vector<bool>> visited;//Посещенные ячейки
vector<vector<int>> path;//Расстояние от стартовой точки до каждой ячейки

//Направления движения (вверх, вниз, влево, вправо)
const vector<Point> directions = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};
//Волновой алгоритм
void bfs(Point start)
{
    size_t rows = maze.size();
    size_t cols = maze[0].size();
    //очередь точек
    Queue* q = queue_create();
    queue_insert(q, static_cast<Data>(start.x * cols + start.y));
    visited[start.x][start.y] = true;
    path[start.x][start.y] = 0;
    //обработка каждой точки
    while (!queue_empty(q))
    {
        size_t curVal = queue_get(q);
        queue_remove(q);
        size_t curX = curVal / cols;
        size_t curY = curVal % cols;

        //Проверяем каждое направление на возможность
        //продвижения дальше
        for (auto dir : directions)
        {
            int newX = int(curX) + dir.x;
            int newY = int(curY) + dir.y;
            //Если точка доступна и не была отмечена раньше, добавляем
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY] && maze[newX][newY] != '#')
            {
                visited[newX][newY] = true;
                path[newX][newY] = path[curX][curY] + 1;
                queue_insert(q, static_cast<Data>(newX * cols + newY));
            }
        }
    }

    queue_delete(q);
}

char find_nearest_number(Point start)
{
    size_t rows = maze.size();
    size_t cols = maze[0].size();

    bfs(start);
    char nearestNumber = 'a';//Значение по умолчанию, если число не найдено
    int minpathance = INT_MAX;

    //Проверяем каждую ячейку на кратчайший путь
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (maze[i][j] >= '0' && maze[i][j] <= '9' && visited[i][j] && path[i][j] < minpathance)
            {
                minpathance = path[i][j];
                nearestNumber = maze[i][j];
            }
        }
    }
    return nearestNumber;
}

int main()
{
    ifstream inputFile("input.txt");
    Point start(-1, -1);
    string line;

    //Считывание лабиринта из файла
    while (getline(inputFile, line))
    {
        maze.push_back(vector<char>(line.begin(), line.end()));
        visited.push_back(vector<bool>(line.size(), false));
        path.push_back(vector<int>(line.size(), 0));

        //Поиск стартовой позиции "X"
        for (int j = 0; j < line.size(); ++j)
        {
            if (line[j] == 'X')
            {
                start = Point(int(maze.size()) - 1, j);
            }
        }
    }

    if (start.x == -1)
    {
        cout << "Start point not found" << endl;
        return 1;
    }
    //Ищем ближайшее число для вывода результата 
    char result = find_nearest_number(start);
    if (result >= '0' && result <= '9')
    {
        cout << result << endl;
    }
    else
    {
        cout << "No number found" << endl;
    }

    return 0;
}
