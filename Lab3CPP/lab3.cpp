#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: Lab3CPP input.txt\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in)
    {
        cout << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    // читаем лабиринт построчно
    vector<string> maze;
    string line;
    while (getline(in, line))
    {
        // на случай файла из Windows убираем '\r'
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
        if (!line.empty())
            maze.push_back(line);
    }

    int rows = maze.size();
    if (rows == 0)
    {
        cout << "Empty maze\n";
        return 1;
    }
    int cols = maze[0].size(); // лабиринт прямоугольный

    // ищем стартовую клетку X
    int start_r = -1;
    int start_c = -1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'X')
            {
                start_r = i;
                start_c = j;
            }
        }
    }
    if (start_r == -1)
    {
        cout << "No start position\n";
        return 1;
    }

    // Поиск в ширину (волновой алгоритм).
    // В очереди храним номер клетки: r * cols + c
    Queue *queue = queue_create();
    queue_insert(queue, start_r * cols + start_c);
    maze[start_r][start_c] = 'x'; // стартовая клетка тоже достижима

    // смещения для соседей: вверх, вниз, влево, вправо
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int count = 1; // сколько клеток достижимо (стартовая X тоже считается)
    while (!queue_empty(queue))
    {
        int cell = queue_get(queue);
        queue_remove(queue);
        int r = cell / cols;
        int c = cell % cols;

        for (int k = 0; k < 4; k++)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];
            // за пределы лабиринта выходить нельзя
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            // идём только в пустые клетки, где ещё не были
            if (maze[nr][nc] != '.')
                continue;
            maze[nr][nc] = 'x'; // отмечаем как посещённую
            count++;
            queue_insert(queue, nr * cols + nc);
        }
    }
    queue_delete(queue);

    cout << count << "\n";
    for (int i = 0; i < rows; i++)
        cout << maze[i] << "\n";

    return 0;
}
