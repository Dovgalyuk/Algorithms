#include "queue.h"
#include "vector.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>

struct Maze
{
    Vector *cells;
    int width;
    int height;
    int start;
};

static bool is_exit(int cell)
{
    return cell >= '0' && cell <= '9';
}

static const char *read_maze(std::ifstream &input, Maze &maze)
{
    size_t width = 0;
    size_t start = 0;
    size_t start_count = 0;

    // Записываем строки подряд в один вектор.
    while (input.peek() != EOF)
    {
        size_t row_start = vector_size(maze.cells);
        size_t end = row_start;
        char cell;
        while (input.get(cell) && cell != '\n')
        {
            vector_resize(maze.cells, end + 1);
            vector_set(maze.cells, end, cell);
            ++end;
        }

        if (input.bad())
            break;

        // Поддерживаем переводы строк Windows.
        if (end > row_start && vector_get(maze.cells, end - 1) == '\r')
        {
            --end;
            vector_resize(maze.cells, end);
        }

        size_t row_width = end - row_start;
        if (row_width == 0 || (width != 0 && row_width != width))
            return "Лабиринт должен быть непустым и прямоугольным";
        width = row_width;

        for (size_t i = row_start; i < end; ++i)
        {
            int value = vector_get(maze.cells, i);
            if (value == 'X')
            {
                start = i;
                ++start_count;
            }
            else if (value != '#' && value != '.' && !is_exit(value))
                return "Недопустимый символ в лабиринте";
        }
    }

    if (input.bad() || start_count != 1)
        return "В лабиринте должна быть ровно одна клетка X";

    size_t cell_count = vector_size(maze.cells);
    if (cell_count > static_cast<size_t>(std::numeric_limits<Data>::max()))
        return "Лабиринт слишком большой";

    maze.width = static_cast<int>(width);
    maze.height = static_cast<int>(cell_count / width);
    maze.start = static_cast<int>(start);
    return nullptr;
}

static int find_exit(Maze &maze)
{
    Queue *queue = queue_create();
    queue_insert(queue, maze.start);
    vector_set(maze.cells, maze.start, '#');

    // Смотрим соседей по порядку: вверх, вправо, вниз, влево.
    const int row_step[] = {-1, 0, 1, 0};
    const int col_step[] = {0, 1, 0, -1};

    while (!queue_empty(queue))
    {
        int position = queue_get(queue);
        queue_remove(queue);
        int row = position / maze.width;
        int col = position % maze.width;

        for (int i = 0; i < 4; ++i)
        {
            int next_row = row + row_step[i];
            int next_col = col + col_step[i];
            if (next_row < 0 || next_row >= maze.height ||
                next_col < 0 || next_col >= maze.width)
                continue;

            int next = next_row * maze.width + next_col;
            int cell = vector_get(maze.cells, next);
            if (cell == '#')
                continue;

            // Первый найденный выход находится на минимальном расстоянии.
            if (is_exit(cell))
            {
                queue_delete(queue);
                return cell - '0';
            }

            // Отмечаем клетку сразу, чтобы не добавить её дважды.
            vector_set(maze.cells, next, '#');
            queue_insert(queue, next);
        }
    }

    queue_delete(queue);
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Укажите файл лабиринта при запуске, например Maze input.txt\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Не удалось открыть файл лабиринта\n";
        return 1;
    }

    Maze maze{vector_create(), 0, 0, 0};
    const char *error = read_maze(input, maze);
    if (error != nullptr)
    {
        std::cerr << error << '\n';
        vector_delete(maze.cells);
        return 1;
    }

    std::cout << find_exit(maze) << '\n';
    vector_delete(maze.cells);
    return 0;
}
