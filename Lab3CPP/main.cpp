#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

typedef vector<string> Maze;
typedef vector<int> IntArray;

const int ROW_SHIFT[6] = {0, 0, -1, -1, 1, 1};
const int COL_SHIFT[6] = {-1, 1, 0, 1, -1, 0};

int find_neighbor(const Maze &maze, int cell, int dir)
{
    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze[0].size());

    int row = cell / width + ROW_SHIFT[dir];
    int col = cell % width + COL_SHIFT[dir];

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return -1;
    }

    if (maze[row][col] == '#')
    {
        return -1;
    }

    return row * width + col;
}

void mark_chain(Maze &maze, const IntArray &parent, int cell)
{
    int width = static_cast<int>(maze[0].size());

    while (cell != -1)
    {
        char &symbol = maze[cell / width][cell % width];

        if (symbol != 'S' && symbol != 'E')
        {
            symbol = 'x';
        }

        cell = parent[cell];
    }
}

bool mark_shortest_path(Maze &maze, int start, int finish)
{
    if (start == -1 || finish == -1)
    {
        return false;
    }

    int cell_count = static_cast<int>(maze.size() * maze[0].size());
    IntArray parent(cell_count, -1);
    IntArray visited(cell_count, 0);
    Queue *queue = queue_create();

    visited[start] = 1;
    queue_insert(queue, start);

    while (!queue_empty(queue) && !visited[finish])
    {
        int cell = queue_get(queue);
        queue_remove(queue);

        for (int dir = 0; dir < 6; dir++)
        {
            int next = find_neighbor(maze, cell, dir);

            if (next != -1 && !visited[next])
            {
                visited[next] = 1;
                parent[next] = cell;
                queue_insert(queue, next);
            }
        }
    }

    queue_delete(queue);

    if (!visited[finish])
    {
        return false;
    }

    mark_chain(maze, parent, finish);
    return true;
}

void print_maze(const Maze &maze, ostream &out)
{
    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze[0].size());

    string top = " ";

    for (int col = 0; col < width; col++)
    {
        top += "/ \\";
    }

    out << top << "\n";

    for (int row = 0; row < height; row++)
    {
        string cells = string(2 * row, ' ') + "|";

        for (int col = 0; col < width; col++)
        {
            char c = maze[row][col];

            if (c != '#' && c != 'S' && c != 'E' && c != 'x')
            {
                c = ' ';
            }

            cells += " ";
            cells += c;
            cells += " |";
        }

        out << cells << "\n";

        string bottom = string(2 * row + 1, ' ');

        for (int col = 0; col < width; col++)
        {
            bottom += "\\ / ";
        }

        if (row < height - 1)
        {
            bottom += "\\";
        }
        else
        {
            bottom.pop_back();
        }

        out << bottom << "\n";
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input> [output]" << endl;
        return 1;
    }

    ifstream in(argv[1]);

    if (!in)
    {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    Maze maze;
    string line;

    while (getline(in, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (!line.empty())
        {
            maze.push_back(line);
        }
    }

    int start = -1;
    int finish = -1;

    for (size_t row = 0; row < maze.size(); row++)
    {
        for (size_t col = 0; col < maze[row].size(); col++)
        {
            int cell = static_cast<int>(row * maze[0].size() + col);

            if (maze[row][col] == 'S')
            {
                start = cell;
            }

            if (maze[row][col] == 'E')
            {
                finish = cell;
            }
        }
    }

    ofstream file_out;

    if (argc >= 3)
    {
        file_out.open(argv[2]);

        if (!file_out)
        {
            cerr << "Cannot open output file" << endl;
            return 1;
        }
    }

    ostream &out = (argc >= 3) ? file_out : cout;

    if (!maze.empty() && mark_shortest_path(maze, start, finish))
    {
        print_maze(maze, out);
    }
    else
    {
        out << "NO PATH" << endl;
    }

    return 0;
}
