#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <locale>

#include "list.h"
#include "queue.h"

using namespace std;
typedef vector<int> MazeRow;
typedef vector<MazeRow> Maze;
typedef vector<bool> VisitedRow;
typedef vector<VisitedRow> Visited;

struct Cell
{
    int row;
    int col;
};

typedef vector<Cell> CellList;

static Maze read_maze(istream &in)
{
    vector<int> values;
    int value;
    while (in >> value)
    {
        values.push_back(value);
    }

    size_t total = values.size();
    Maze maze;
    if (total == 0)
        return maze;

    vector<size_t> lengths;
    size_t used = 0;
    int width = 1;

    // возрастающая часть до пика
    while (true)
    {
        if (used + static_cast<size_t>(width) > total)
            return maze;

        size_t after = used + static_cast<size_t>(width);
        size_t remaining = total - after;

        // сумма убывающей части после этого пика: (width-2)+(width-4)+...+1
        size_t desc_sum = 0;
        for (int w = width - 2; w >= 1; w -= 2)
            desc_sum += static_cast<size_t>(w);

        if (remaining == desc_sum)
        {
            lengths.push_back(static_cast<size_t>(width));
            used += static_cast<size_t>(width);
            break;
        }
        if (remaining < desc_sum)
            return maze;

        lengths.push_back(static_cast<size_t>(width));
        used += static_cast<size_t>(width);
        width += 2;
    }

    // убывающая часть
    for (int w = width - 2; w >= 1 && used < total; w -= 2)
    {
        if (used + static_cast<size_t>(w) > total)
            break;
        lengths.push_back(static_cast<size_t>(w));
        used += static_cast<size_t>(w);
    }

    if (used != total)
        return maze;

    size_t index = 0;
    for (size_t len : lengths)
    {
        MazeRow row;
        for (size_t i = 0; i < len; ++i)
        {
            row.push_back(values[index++]);
        }
        maze.push_back(row);
    }
    return maze;
}

static bool inside(const Maze &maze, int row, int col)
{
    return row >= 0 && row < static_cast<int>(maze.size()) &&
           col >= 0 && col < static_cast<int>(maze[row].size());
}

static CellList neighbors(const Maze &maze, Cell cell)
{
    CellList result;
    int row = cell.row;
    int col = cell.col;

    result.push_back({row, col - 1});
    result.push_back({row, col + 1});

    size_t current_size = maze[static_cast<size_t>(row)].size();

    // строка выше
    if (row > 0)
    {
        size_t upper_size = maze[static_cast<size_t>(row - 1)].size();

        if (upper_size < current_size)
        {
            result.push_back({row - 1, col - 1});
        }
        else if (upper_size > current_size)
        {
            result.push_back({row - 1, col + 1});
        }
    }

    // строка ниже
    if (row + 1 < static_cast<int>(maze.size()))
    {
        size_t lower_size = maze[static_cast<size_t>(row + 1)].size();

        if (lower_size < current_size)
        {
            result.push_back({row + 1, col - 1});
        }
        else if (lower_size > current_size)
        {
            result.push_back({row + 1, col + 1});
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ifstream input(argv[1]);
    if (argc < 2)
    {
        cerr << "Использование: " << argv[0] << "\n";
        return 1;
    }
    if (!input)
    {
        cerr << "Не удалось открыть входной файл\n";
        return 1;
    }

    Maze maze = read_maze(input);

    if (maze.empty())
    {
        cerr << "Некорректный лабиринт\n";
        return 1;
    }

    Visited reachable;
    reachable.reserve(maze.size());

    for (const auto &row : maze)
    {
        reachable.push_back(VisitedRow(row.size(), false));
    }

    int start_row = static_cast<int>(maze.size() / 2);
    int start_col = 0;

    Queue *queue = queue_create();
    queue_insert(queue, start_row);
    queue_insert(queue, start_col);
    reachable[start_row][start_col] = true;

    while (!queue_empty(queue))
    {
        int row = queue_get(queue);
        queue_remove(queue);
        int col = queue_get(queue);
        queue_remove(queue);
        int current = maze[row][col];

        for (Cell next : neighbors(maze, {row, col}))
        {
            if (!inside(maze, next.row, next.col))
                continue;

            if (reachable[next.row][next.col])
                continue;

            int value = maze[next.row][next.col];

            if (value == current - 1 || value == current + 1)
            {
                reachable[next.row][next.col] = true;
                queue_insert(queue, next.row);
                queue_insert(queue, next.col);
            }
        }
    }
    queue_delete(queue);

    for (size_t row = 0; row < maze.size(); ++row)
    {
        for (size_t col = 0; col < maze[row].size(); ++col)
        {
            if (col != 0)
                cout << ' ';

            if (reachable[row][col])
                cout << maze[row][col];
            else
                cout << '#';
        }
        cout << '\n';
    }
    return 0;
}