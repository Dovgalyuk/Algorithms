#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include "list.h"
#include "queue.h"

// Волновой алгоритм (BFS) на основе очереди Queue из LibraryCPP.
// Клетка кодируется числом: idx = row * W + col.

static char cell_at(const std::vector<std::string>& maze, int r, int c, int W)
{
    if (c >= static_cast<int>(maze[r].size()))
        return '#'; // не хватает символов в строке — считаем стеной
    return maze[r][c];
}

int main(int argc, char** argv)
{
    // Вход: файл из аргумента командной строки (для ctest)
    // либо stdin (для ручного запуска с перенаправлением).
    std::istream* in = &std::cin;
    std::ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "Cannot open file: " << argv[1] << '\n';
            return 1;
        }
        in = &file;
    }

    std::vector<std::string> maze;
    std::string line;
    while (std::getline(*in, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back(); // Windows-перенос строки
        if (line.empty())
            continue;
        maze.push_back(line);
    }

    const int H = static_cast<int>(maze.size());
    int W = 0;
    for (const auto& row : maze)
        W = std::max(W, static_cast<int>(row.size()));

    // Поиск стартовой позиции X
    int start = -1;
    for (int r = 0; r < H && start == -1; ++r)
        for (int c = 0; c < W; ++c)
            if (cell_at(maze, r, c, W) == 'X')
            {
                start = r * W + c;
                break;
            }

    char answer = 0;

    if (start != -1 && H > 0 && W > 0)
    {
        std::vector<int> dist(H * W, -1); // -1 = клетка не посещена
        Queue* q = queue_create();

        dist[start] = 0;
        queue_insert(q, static_cast<Data>(start));

        const int dr[4] = { -1, 1, 0, 0 };
        const int dc[4] = { 0, 0, -1, 1 };

        while (!queue_empty(q))
        {
            int cur = queue_get(q);
            queue_remove(q);

            int r = cur / W;
            int c = cur % W;
            char cell = cell_at(maze, r, c, W);

            // Первая найденная финишная клетка при BFS — ближайшая.
            if (std::isdigit(static_cast<unsigned char>(cell)))
            {
                answer = cell;
                break;
            }

            for (int k = 0; k < 4; ++k)
            {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr < 0 || nr >= H || nc < 0 || nc >= W)
                    continue; // за пределы лабиринта выходить нельзя

                int idx = nr * W + nc;
                if (dist[idx] != -1)
                    continue; // уже посещена
                if (cell_at(maze, nr, nc, W) == '#')
                    continue; // стена

                dist[idx] = dist[cur] + 1;
                queue_insert(q, static_cast<Data>(idx));
            }
        }

        queue_delete(q);
    }

    if (answer != 0)
        std::cout << answer << '\n';
    else
        std::cout << "No path" << '\n';

    return 0;
}