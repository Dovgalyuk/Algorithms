#include <fstream>
#include <iostream>
#include <string>
#include <climits>
#include "queue.h"
#include "vector.h"

using namespace std;

void print_maze(const Vector* maze, int rows, int columns)
{
    for (int column = 0; column < columns; ++column)
    {
        cout << " / \\";
    }
    cout << '\n';

    for (int row = 0; row < rows; ++row)
    {
        cout << string(static_cast<size_t>(row) * 2, ' ') << '|';

        for (int column = 0; column < columns; ++column)
        {
            char cell = static_cast<char>(vector_get(maze, row * columns + column));

            if (cell == '.')
            {
                cell = ' ';
            }

            cout << ' ' << cell << " |";
        }

        cout << '\n';


        cout << string(static_cast<size_t>(row) * 2 + 1, ' ');

        for (int column = 0; column < columns; ++column)
        {
            cout << "\\ /";

            if (column + 1 < columns)
            {
                cout << ' ';
            }
        }

        if (row + 1 < rows)
        {
            cout << " \\";
        }

        cout << '\n';
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: Maze <input_file>\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        cerr << "Cannot open file\n";
        return 1;
    }

    Vector* maze = vector_create();
    int rows = 0;
    int columns = 0;
    string line;

    while (getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
        {
            cerr << "Empty maze row\n";
            vector_delete(maze);
            return 1;
        }

        if (rows != 0 && line.size() != static_cast<size_t>(columns))
        {
            cerr << "Different row lengths\n";
            vector_delete(maze);
            return 1;
        }

        if (line.size() > static_cast<size_t>(INT_MAX) - vector_size(maze))
        {
            cerr << "Maze is too large\n";
            vector_delete(maze);
            return 1;
        }

        if (rows == 0)
        {
            columns = static_cast<int>(line.size());
        }

        vector_resize(maze, vector_size(maze) + line.size());

        for (int column = 0; column < columns; ++column)
        {
            vector_set(maze, rows * columns + column, line[column]);
        }

        ++rows;
    }

    if (rows == 0)
    {
        cerr << "Maze is empty\n";
        vector_delete(maze);
        return 1;
    }

    int start = -1;
    int finish = -1;

    int start_count = 0;
    int finish_count = 0;

    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            char cell = static_cast<char>(vector_get(maze, row * columns + column));

            if (cell == 'S')
            {
                start = row * columns + column;
                ++start_count;
            }
            else if (cell == 'E')
            {
                finish = row * columns + column;
                ++finish_count;
            }
            else if (cell != '#' && cell != '.')
            {
                cerr << "Invalid maze character\n";
                vector_delete(maze);
                return 1;
            }
        }
    }

    if (start_count != 1 || finish_count != 1)
    {
        cerr << "Maze must contain exactly one S and one E\n";
        vector_delete(maze);
        return 1;
    }

    Vector* parent = vector_create();
    vector_resize(parent, vector_size(maze));

    for (size_t i = 0; i < vector_size(parent); ++i)
    {
        vector_set(parent, i, -1);
    }

    Queue* queue = queue_create();

    vector_set(parent, start, start);
    queue_insert(queue, start);

    int dr[6] = {0, 0, -1, -1, 1, 1};
    int dc[6] = {-1, 1, 0, 1, -1, 0};

    while (!queue_empty(queue))
    {
        int current = queue_get(queue);
        queue_remove(queue);

        if (current == finish)
        {
            break;
        }

        int row = current / columns;
        int column = current % columns;

        for (int i = 0; i < 6; ++i)
        {
            int next_row = row + dr[i];
            int next_column = column + dc[i];

            if (next_row < 0 || next_row >= rows || next_column < 0 || next_column >= columns)
            {
                continue;
            }

            int next = next_row * columns + next_column;

            if (vector_get(maze, next) == '#')
            {
                continue;
            }

            if (vector_get(parent, next) != -1)
            {
                continue;
            }

            vector_set(parent, next, current);
            queue_insert(queue, next);
        }
    }

    queue_delete(queue);

    if (vector_get(parent, finish) == -1)
    {
        cout << "No path found\n";
        vector_delete(parent);
        vector_delete(maze);
        return 0;
    }

    int current = finish;

    while (current != start)
    {
        if (vector_get(maze, current) == '.')
        {
            vector_set(maze, current, 'x');
        }

        current = vector_get(parent, current);
    }

    print_maze(maze, rows, columns);

    vector_delete(parent);
    vector_delete(maze);

    return 0;
}
