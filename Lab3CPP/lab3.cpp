#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

// Координаты клетки
struct Cell
{
    int row;
    int column;

    Cell(int r = -1, int c = -1)
        : row(r), column(c)
    {
    }
};

typedef std::vector<std::string> Maze;
typedef std::vector<std::vector<Cell>> CellTable;
typedef std::vector<std::vector<int>> NumberTable;
typedef std::vector<Cell> Path;

bool sameCell(Cell a, Cell b)
{
    return a.row == b.row && a.column == b.column;
}

// Данные поиска с одной стороны
struct Search
{
    Queue<Cell> queue;
    CellTable previous;
    int layerSize;

    Search(int rows, int columns, Cell start)
        : previous(rows, std::vector<Cell>(columns)),
          layerSize(1)
    {
        queue.insert(start);
        previous[start.row][start.column] = start;
    }

    bool visited(Cell cell) const
    {
        return previous[cell.row][cell.column].row != -1;
    }
};

// Проверка границ лабиринта
bool inside(const Maze &maze, Cell cell)
{
    return cell.row >= 0
        && cell.row < static_cast<int>(maze.size())
        && cell.column >= 0
        && cell.column < static_cast<int>(maze[0].size());
}

// Чтение лабиринта и поиск начальной и конечной клеток
bool readMaze(std::ifstream &input, Maze &maze,
              Cell &start, Cell &finish)
{
    std::string line;

    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        maze.push_back(line);
    }

    if (maze.empty() || maze[0].empty())
    {
        return false;
    }

    int startCount = 0;
    int finishCount = 0;

    for (int row = 0; row < static_cast<int>(maze.size()); ++row)
    {
        if (maze[row].size() != maze[0].size())
        {
            return false;
        }

        for (int column = 0;
             column < static_cast<int>(maze[row].size());
             ++column)
        {
            char symbol = maze[row][column];

            if (symbol == 'Q')
            {
                start = Cell(row, column);
                ++startCount;
            }
            else if (symbol == 'E')
            {
                finish = Cell(row, column);
                ++finishCount;
            }
            else if (symbol != '#' && symbol != '.')
            {
                return false;
            }
        }
    }

    return startCount == 1 && finishCount == 1;
}

// Расширение одной стороны поиска на один слой
bool makeStep(const Maze &maze, Search &current,
              const Search &other, Cell &meeting)
{
    const int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},         { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    int nextLayerSize = 0;

    for (int i = 0; i < current.layerSize; ++i)
    {
        Cell cell = current.queue.get();
        current.queue.remove();

        for (int direction = 0; direction < 8; ++direction)
        {
            int dr = directions[direction][0];
            int dc = directions[direction][1];

            Cell next(cell.row + dr, cell.column + dc);

            while (inside(maze, next)
                   && maze[next.row][next.column] != '#')
            {
                if (!current.visited(next))
                {
                    current.previous[next.row][next.column] = cell;
                    current.queue.insert(next);
                    ++nextLayerSize;

                    if (other.visited(next))
                    {
                        meeting = next;
                        return true;
                    }
                }

                // Посещённая клетка не мешает двигаться дальше
                next.row += dr;
                next.column += dc;
            }
        }
    }

    current.layerSize = nextLayerSize;
    return false;
}

// Восстановление пути через клетку встречи
Path restorePath(const Search &fromStart,
                 const Search &fromFinish,
                 Cell start, Cell finish, Cell meeting)
{
    Path path;
    Cell cell = meeting;

    // Идём от встречи назад к старту
    while (!sameCell(cell, start))
    {
        path.push_back(cell);
        cell = fromStart.previous[cell.row][cell.column];
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    // Добавляем участок от встречи до финиша
    cell = meeting;

    while (!sameCell(cell, finish))
    {
        cell = fromFinish.previous[cell.row][cell.column];
        path.push_back(cell);
    }

    return path;
}

// Встречный поиск с двумя нашими очередями
Path findPath(const Maze &maze, Cell start, Cell finish)
{
    int rows = static_cast<int>(maze.size());
    int columns = static_cast<int>(maze[0].size());

    Search fromStart(rows, columns, start);
    Search fromFinish(rows, columns, finish);

    Cell meeting;

    while (!fromStart.queue.empty() && !fromFinish.queue.empty())
    {
        if (makeStep(maze, fromStart, fromFinish, meeting))
        {
            return restorePath(
                fromStart, fromFinish, start, finish, meeting);
        }

        if (makeStep(maze, fromFinish, fromStart, meeting))
        {
            // Порядок таблиц всегда один: от старта, затем от финиша
            return restorePath(
                fromStart, fromFinish, start, finish, meeting);
        }
    }

    return Path();
}

// Вывод лабиринта с номерами позиций ферзя.
void printPath(const Maze &maze, const Path &path)
{
    NumberTable numbers(
        maze.size(), std::vector<int>(maze[0].size(), -1));

    for (int i = 0; i < static_cast<int>(path.size()); ++i)
    {
        numbers[path[i].row][path[i].column] = i;
    }

    for (int row = 0; row < static_cast<int>(maze.size()); ++row)
    {
        for (int column = 0;
             column < static_cast<int>(maze[row].size());
             ++column)
        {
            if (numbers[row][column] == -1)
            {
                std::cout << maze[row][column];
            }
            else
            {
                std::cout << numbers[row][column];
            }
        }

        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab3CPP input.txt\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    Maze maze;
    Cell start;
    Cell finish;

    if (!readMaze(input, maze, start, finish))
    {
        std::cerr << "Invalid maze\n";
        return 1;
    }

    Path path = findPath(maze, start, finish);

    if (path.empty())
    {
        std::cout << "No path\n";
    }
    else
    {
        printPath(maze, path);
    }

    return 0;
}