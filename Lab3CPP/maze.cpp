#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

using namespace std;

typedef vector<string> Maze;

const int ROW_STEP[4] = {-1, 0, 1, 0};
const int COLUMN_STEP[4] = {0, 2, 0, -2};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Использование: Lab3CPPMaze входной_файл.txt\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cerr << "Ошибка: не удалось открыть входной файл\n";
        return 1;
    }

    Maze maze;
    string line;
    size_t width = 0;

    while (getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.find_first_not_of(' ') == string::npos)
            continue;

        for (char symbol : line)
        {
            if (symbol != ' ' && (symbol < '0' || symbol > '9'))
            {
                cerr << "Ошибка: неверный лабиринт\n";
                return 1;
            }
        }

        if (line.size() > width)
            width = line.size();
        maze.push_back(line);
    }

    if (maze.empty())
    {
        cerr << "Ошибка: пустой лабиринт\n";
        return 1;
    }

    if (width > INT_MAX || maze.size() > INT_MAX / width)
    {
        cerr << "Ошибка: слишком большой лабиринт\n";
        return 1;
    }

    int rows = static_cast<int>(maze.size());
    int columns = static_cast<int>(width);
    int start = -1;
    int finish = -1;

    for (int row = 0; row < rows; ++row)
    {
        maze[row].resize(width, ' ');
        for (int column = 0; column < columns; ++column)
        {
            if (maze[row][column] == ' ')
                continue;

            int cell = row * columns + column;
            if (start == -1 || column < start % columns)
                start = cell;
            if (finish == -1 || column > finish % columns)
                finish = cell;
        }
    }

    vector<int> previous(rows * columns, -1);
    Queue *queue = queue_create();
    previous[start] = start;
    queue_insert(queue, start);

    while (!queue_empty(queue) && previous[finish] == -1)
    {
        int cell = queue_get(queue);
        queue_remove(queue);
        int row = cell / columns;
        int column = cell % columns;

        for (int direction = 0; direction < 4; ++direction)
        {
            int next_row = row + ROW_STEP[direction];
            int next_column = column + COLUMN_STEP[direction];
            if (next_row < 0 || next_row >= rows || next_column < 0 || next_column >= columns)
                continue;

            if (maze[next_row][next_column] == ' ')
                continue;

            int next = next_row * columns + next_column;
            int difference = maze[next_row][next_column] - maze[row][column];
            if (previous[next] == -1 && (difference == 1 || difference == -1))
            {
                previous[next] = cell;
                queue_insert(queue, next);
            }
        }
    }

    queue_delete(queue);

    if (previous[finish] == -1)
    {
        cout << "Путь не найден\n";
        return 0;
    }

    for (int cell = finish; cell != start; cell = previous[cell])
        maze[cell / columns][cell % columns] = '#';
    maze[start / columns][start % columns] = '#';

    for (const string &row : maze)
        cout << row.substr(0, row.find_last_not_of(' ') + 1) << '\n';

    return 0;
}
