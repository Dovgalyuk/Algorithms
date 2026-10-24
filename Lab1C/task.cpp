#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

struct Point
{
    int r;
    int c;
};

const int DR[6] = {0, 0, -1, -1, 1, 1};
const int DC[6] = {-1, 1, 0, 1, -1, 0};

int to_id(Point p, int cols)
{
    return p.r * cols + p.c;
}

Point from_id(int id, int cols)
{
    return {id / cols, id % cols};
}

Point find_char(const vector<string> &maze, char target)
{
    int rows = (int)maze.size();
    int cols = (int)maze[0].size();
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (maze[r][c] == target)
            {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

void solve_maze(vector<string> &maze)
{
    Point start = find_char(maze, 'S');
    Point finish = find_char(maze, 'E');

    if (start.r == -1 || finish.r == -1) return;

    int rows = (int)maze.size();
    int cols = (int)maze[0].size();

    vector<vector<Point>> parent(rows, vector<Point>(cols, {-1, -1}));

    Queue *q = queue_create();

    parent[start.r][start.c] = start;
    queue_insert(q, to_id(start, cols));

    bool found = false;

    while (!queue_empty(q))
    {
        Point cur = from_id(queue_get(q), cols);
        queue_remove(q);

        if (cur.r == finish.r && cur.c == finish.c)
        {
            found = true;
            break;
        }

        for (int i = 0; i < 6; ++i)
        {
            Point next = {cur.r + DR[i], cur.c + DC[i]};

            if (next.r >= 0 && next.r < rows && next.c >= 0 && next.c < cols)
            {
                if (maze[next.r][next.c] != '#' && parent[next.r][next.c].r == -1)
                {
                    parent[next.r][next.c] = cur;        
                    queue_insert(q, to_id(next, cols));  
                }
            }
        }
    }

    queue_delete(q);

    if (found)
    {
        Point cur = parent[finish.r][finish.c];
        while (!(cur.r == start.r && cur.c == start.c))
        {
            maze[cur.r][cur.c] = 'x';
            cur = parent[cur.r][cur.c];
        }
    }
}

void print_hex_maze(const vector<string> &maze, ostream &out)
{
    if (maze.empty() || maze[0].empty()) return;
    int rows = (int)maze.size();
    int cols = (int)maze[0].size();

    for (int c = 0; c < cols; ++c)
    {
        out << " / \\";
    }
    out << "\n";

    for (int r = 0; r < rows; ++r)
    {
        out << string(2 * r, ' ');
        for (int c = 0; c < cols; ++c)
        {
            char ch = (maze[r][c] == '.') ? ' ' : maze[r][c];
            out << "| " << ch << " ";
        }
        out << "|\n";

        out << string(2 * r + 1, ' ');
        if (r < rows - 1)
        {
            for (int c = 0; c < cols; ++c)
            {
                out << "\\ / ";
            }
            out << "\\\n";
        }
        else
        {
            for (int c = 0; c < cols; ++c)
            {
                out << "\\ /" << (c + 1 < cols ? " " : "");
            }
            out << "\n";
        }
    }
}

int main(int argc, char *argv[])
{
    istream *in = &cin;
    ifstream fin;
    if (argc >= 2)
    {
        fin.open(argv[1]);
        if (!fin.is_open()) return 1;
        in = &fin;
    }

    ostream *out = &cout;
    ofstream fout;
    if (argc >= 3)
    {
        fout.open(argv[2]);
        if (!fout.is_open()) return 1;
        out = &fout;
    }

    vector<string> maze;
    string line;
    while (getline(*in, line))
    {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' '))
            line.pop_back();
        if (!line.empty())
            maze.push_back(line);
    }

    solve_maze(maze);

    print_hex_maze(maze, *out);

    return 0;
}
