#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

const int ROW_SHIFT[6] = {0, 0, -1, -1, 1, 1};
const int COL_SHIFT[6] = {-1, 1, 0, 1, -1, 0};

struct Search
{
    vector<int> owner;
    vector<int> dist;
    vector<int> parent;
    Queue *queue[2];
    int best_length = -1;
    int best_cell_a = -1;
    int best_cell_b = -1;
};

int find_neighbor(const vector<string> &maze, int cell, int dir)
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

void expand_level(const vector<string> &maze, Search &s, int side)
{
    Queue *q = s.queue[side];
    int depth = s.dist[queue_get(q)];

    while (!queue_empty(q) && s.dist[queue_get(q)] == depth)
    {
        int cell = queue_get(q);
        queue_remove(q);

        for (int dir = 0; dir < 6; dir++)
        {
            int next = find_neighbor(maze, cell, dir);
            if (next == -1)
            {
                continue;
            }

            if (s.owner[next] == -1)
            {
                s.owner[next] = side;
                s.dist[next] = depth + 1;
                s.parent[next] = cell;
                queue_insert(q, next);
            }
            else if (s.owner[next] != side)
            {
                int length = s.dist[cell] + 1 + s.dist[next];
                if (s.best_length == -1 || length < s.best_length)
                {
                    s.best_length = length;
                    s.best_cell_a = cell;
                    s.best_cell_b = next;
                }
            }
        }
    }
}

void mark_chain(vector<string> &maze, const vector<int> &parent, int cell)
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

bool mark_shortest_path(vector<string> &maze, int start, int finish)
{
    if (start == -1 || finish == -1)
    {
        return false;
    }

    int cell_count = static_cast<int>(maze.size() * maze[0].size());

    Search s;
    s.owner.assign(cell_count, -1);
    s.dist.assign(cell_count, 0);
    s.parent.assign(cell_count, -1);
    s.queue[0] = queue_create();
    s.queue[1] = queue_create();

    s.owner[start] = 0;
    s.owner[finish] = 1;
    queue_insert(s.queue[0], start);
    queue_insert(s.queue[1], finish);

    while (s.best_length == -1 && !queue_empty(s.queue[0]) && !queue_empty(s.queue[1]))
    {
        expand_level(maze, s, 0);
        if (s.best_length == -1)
        {
            expand_level(maze, s, 1);
        }
    }

    bool found = s.best_length != -1;
    if (found)
    {
        mark_chain(maze, s.parent, s.best_cell_a);
        mark_chain(maze, s.parent, s.best_cell_b);
    }

    queue_delete(s.queue[0]);
    queue_delete(s.queue[1]);
    return found;
}

void print_maze(const vector<string> &maze, ostream &out)
{
    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze[0].size());

    string top = " ";
    for (int col = 0; col < width; col++)
    {
        top += "/ \\ ";
    }
    top.pop_back();
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

    vector<string> maze;
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