#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "queue.h"

typedef std::vector<std::vector<int>> Maze;
typedef std::vector<std::vector<bool>> Visited;

struct Cell
{
    int r;
    int c;
};

typedef std::vector<Cell> Neighbors;

Maze ReadMaze(const std::string& filename)
{
    std::ifstream f(filename);
    if (!f)
        return Maze();

    Maze maze;
    std::string line;
    while (std::getline(f, line))
    {
        std::vector<int> row;
        std::istringstream input(line);
        int value;
        while (input >> value)
            row.push_back(value);

        if (!row.empty())
            maze.push_back(row);
    }
    return maze;
}

Neighbors GetNeighbors(const Maze& maze, int r, int c)
{
    Neighbors result;
    int rows = static_cast<int>(maze.size());
    int center = rows / 2;

    if (c > 0)
        result.push_back({r, c - 1});

    if (r > 0)
    {
        int nr = r - 1;
        int nc = (r <= center) ? (c - 1) : (c + 1);
        if (nc >= 0 && nc < static_cast<int>(maze[nr].size()))
            result.push_back({nr, nc});
    }

    if (c < static_cast<int>(maze[r].size()) - 1)
        result.push_back({r, c + 1});

    if (r < rows - 1)
    {
        int nr = r + 1;
        int nc = (r < center) ? (c + 1) : (c - 1);
        if (nc >= 0 && nc < static_cast<int>(maze[nr].size()))
            result.push_back({nr, nc});
    }
    return result;
}

Visited FindReachable(const Maze& maze)
{
    int rows = static_cast<int>(maze.size());
    int center = rows / 2;
    int start_r = center;
    int start_c = 0;

    Visited visited(rows);
    for (int i = 0; i < rows; ++i)
        visited[i].assign(maze[i].size(), false);

    Queue* q = queue_create();
    queue_insert(q, start_r * 100 + start_c);
    visited[start_r][start_c] = true;

    while (!queue_empty(q))
    {
        int packed = queue_get(q);
        queue_remove(q);

        int r = packed / 100;
        int c = packed % 100;

        for (auto& nb : GetNeighbors(maze, r, c))
        {
            int nr = nb.r;
            int nc = nb.c;

            if (!visited[nr][nc] && std::abs(maze[nr][nc] - maze[r][c]) == 1)
            {
                visited[nr][nc] = true;
                queue_insert(q, nr * 100 + nc);
            }
        }
    }

    queue_delete(q);
    return visited;
}

void PrintMaze(const Maze& maze, const Visited& visited)
{
    int rows = static_cast<int>(maze.size());
    int center = rows / 2;

    for (int r = 0; r < rows; ++r)
    {
        int offset = std::abs(r - center);
        for (int i = 0; i < offset; ++i)
            std::cout << "  ";

        for (int c = 0; c < static_cast<int>(maze[r].size()); ++c)
        {
            if (c > 0) std::cout << " ";
            if (visited[r][c])
                std::cout << maze[r][c];
            else
                std::cout << "#";
        }
        std::cout << "\n";
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    Maze maze = ReadMaze(argv[1]);
    if (maze.empty())
        return 1;

    Visited visited = FindReachable(maze);
    PrintMaze(maze, visited);
}