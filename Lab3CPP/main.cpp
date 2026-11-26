#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#include "queue.h"

// Координаты клетки (строка r и столбец c)
struct Cell
{
    int r;
    int c;
};

// Тип для представления ромбического лабиринта (двумерный вектор чисел)
typedef std::vector<std::vector<int>> Maze;

// Тип для таблицы посещенных клеток (двумерный вектор флагов)
typedef std::vector<std::vector<bool>> Visited;

// Функция 1: Чтение ромбического лабиринта из файла
bool read_maze(const std::string &filename, Maze &maze)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<int> row;
        int val;
        while (iss >> val)
            row.push_back(val);
        if (!row.empty())
            maze.push_back(row);
    }
    return true;
}

// Функция 2: Поиск соседних клеток (слева, справа, сверху, снизу)
std::vector<Cell> get_neighbors(const Maze &maze, int r, int c)
{
    std::vector<Cell> neighbors;
    int rows = (int)maze.size();
    int center = rows / 2;

    // В ромбе каждая строка имеет отступ |r - center| позиций от края.
    // Поэтому абсолютная позиция (колонка) элемента в сетке равна:
    int col = std::abs(r - center) + c;

    // 1. Сосед слева в той же строке
    if (c > 0)
        neighbors.push_back({r, c - 1});

    // 2. Сосед справа в той же строке
    if (c + 1 < (int)maze[r].size())
        neighbors.push_back({r, c + 1});

    // 3. Сосед сверху (в строке r - 1 в той же колонке col)
    if (r > 0)
    {
        int nr = r - 1;
        int nc = col - std::abs(nr - center);
        if (nc >= 0 && nc < (int)maze[nr].size())
            neighbors.push_back({nr, nc});
    }

    // 4. Сосед снизу (в строке r + 1 в той же колонке col)
    if (r + 1 < rows)
    {
        int nr = r + 1;
        int nc = col - std::abs(nr - center);
        if (nc >= 0 && nc < (int)maze[nr].size())
            neighbors.push_back({nr, nc});
    }

    return neighbors;
}

// Функция 3: Поиск в ширину (BFS) с использованием очереди Queue
Visited find_reachable(const Maze &maze)
{
    int rows = (int)maze.size();
    int center = rows / 2;

    // Создаём таблицу флагов посещения (изначально все false)
    Visited visited(rows);
    for (int i = 0; i < rows; ++i)
        visited[i].assign(maze[i].size(), false);

    // Создаём очередь из LibraryCPP
    Queue *q = queue_create();

    // Самая левая клетка лабиринта — нулевой элемент центральной строки
    // Координаты (r, c) упаковываем в одно число: r * 1000 + c
    queue_insert(q, center * 1000 + 0);
    visited[center][0] = true;

    while (!queue_empty(q))
    {
        int packed = queue_get(q);
        queue_remove(q);

        int r = packed / 1000;
        int c = packed % 1000;

        for (const Cell &next : get_neighbors(maze, r, c))
        {
            // Переходить можно, только если разница чисел ровно 1 (на 1 больше или на 1 меньше)
            if (!visited[next.r][next.c] && std::abs(maze[next.r][next.c] - maze[r][c]) == 1)
            {
                visited[next.r][next.c] = true;
                queue_insert(q, next.r * 1000 + next.c);
            }
        }
    }

    queue_delete(q);
    return visited;
}

// Функция 4: Вывод лабиринта (посещенные — числами, недостижимые — '#')
void print_maze(std::ostream &out, const Maze &maze, const Visited &visited)
{
    int rows = (int)maze.size();
    int center = rows / 2;

    for (int r = 0; r < rows; ++r)
    {
        // Печатаем начальный отступ: по 2 пробела на единицу смещения |r - center|
        std::string row_str(std::abs(r - center) * 2, ' ');

        for (size_t c = 0; c < maze[r].size(); ++c)
        {
            if (c > 0)
                row_str += ' ';
            row_str += visited[r][c] ? std::to_string(maze[r][c]) : "#";
        }
        row_str += '\n';
        out << row_str;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> [output_file]\n";
        return 1;
    }

    // 1. Читаем лабиринт
    Maze maze;
    if (!read_maze(argv[1], maze) || maze.empty())
        return 1;

    // 2. Находим достижимые клетки с помощью BFS
    Visited visited = find_reachable(maze);

    // 3. Выводим результат в консоль
    print_maze(std::cout, maze, visited);

    // 4. Если указан второй аргумент — записываем в файл для тестов
    if (argc >= 3)
    {
        std::ofstream fout(argv[2], std::ios::binary);
        if (fout.is_open())
            print_maze(fout, maze, visited);
    }

    return 0;
}
