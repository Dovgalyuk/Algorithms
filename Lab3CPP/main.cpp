#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "queue.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: Lab3CPP <input_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Cannot open file\n";
        return 1;
    }

    std::vector<std::string> maze;
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
            maze.push_back(line);
    }

    if (maze.empty() || maze[0].empty())
    {
        std::cout << "Invalid maze\n";
        return 1;
    }

    const size_t rows = maze.size();
    const size_t cols = maze[0].size();

    if (rows > static_cast<size_t>(std::numeric_limits<int>::max()) ||
        cols > static_cast<size_t>(std::numeric_limits<int>::max()) ||
        rows > static_cast<size_t>(std::numeric_limits<int>::max()) / cols)
    {
        std::cout << "Invalid maze\n";
        return 1;
    }

    int start = -1;
    int finish = -1;
    int startCount = 0;
    int finishCount = 0;

    for (size_t r = 0; r < rows; ++r)
    {
        if (maze[r].size() != cols)
        {
            std::cout << "Invalid maze\n";
            return 1;
        }

        for (size_t c = 0; c < cols; ++c)
        {
            char cell = maze[r][c];

            if (cell == 'Q')
            {
                start = static_cast<int>(r * cols + c);
                ++startCount;
            }
            else if (cell == 'E')
            {
                finish = static_cast<int>(r * cols + c);
                ++finishCount;
            }
            else if (cell != '.' && cell != '#')
            {
                std::cout << "Invalid maze\n";
                return 1;
            }
        }
    }

    if (startCount != 1 || finishCount != 1)
    {
        std::cout << "Invalid maze\n";
        return 1;
    }

    const size_t total = rows * cols;
    std::vector<int> dist(total, -1);
    std::vector<unsigned long long> ways(total, 0);

    const int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    const int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    Queue* queue = queue_create();

    dist[start] = 0;
    ways[start] = 1;
    queue_insert(queue, start);

    while (!queue_empty(queue))
    {
        int current = queue_get(queue);
        queue_remove(queue);

        int r = current / static_cast<int>(cols);
        int c = current % static_cast<int>(cols);

        for (int k = 0; k < 8; ++k)
        {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 || nc < 0 ||
                nr >= static_cast<int>(rows) ||
                nc >= static_cast<int>(cols))
                continue;

            if (maze[nr][nc] == '#')
                continue;

            int next = nr * static_cast<int>(cols) + nc;

            if (dist[next] == -1)
            {
                dist[next] = dist[current] + 1;
                ways[next] = ways[current];
                queue_insert(queue, next);
            }
            else if (dist[next] == dist[current] + 1)
            {
                ways[next] += ways[current];
            }
        }
    }

    queue_delete(queue);

    std::cout << ways[finish] << '\n';
    return 0;
}

