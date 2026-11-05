#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

int main(int argc, char *argv[])
{
    std::istream *in = &std::cin;
    std::ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        if (!file.is_open())
        {
            return 1;
        }
        in = &file;
    }

    std::vector<std::string> maze;
    std::string line;
    while (std::getline(*in, line))
    {
        while (!line.empty() && (line.back() == '\r' || line.back() == ' '))
        {
            if (line.back() == '\r')
            {
                line.pop_back();
            }
            else
            {
                break;
            }
        }
        if (!line.empty())
        {
            maze.push_back(line);
        }
    }

    if (maze.empty())
    {
        return 0;
    }

    int rows = static_cast<int>(maze.size());
    int cols = static_cast<int>(maze[0].size());

    int start_r = -1;
    int start_c = -1;
    int end_r = -1;
    int end_c = -1;

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (maze[r][c] == 'Q')
            {
                start_r = r;
                start_c = c;
            }
            else if (maze[r][c] == 'E')
            {
                end_r = r;
                end_c = c;
            }
        }
    }

    if (start_r == -1 || end_r == -1)
    {
        return 1;
    }

    if (start_r == end_r && start_c == end_c)
    {
        maze[start_r][start_c] = '0';
        for (int r = 0; r < rows; ++r)
        {
            std::cout << maze[r] << "\n";
        }
        return 0;
    }

    int total_cells = rows * cols;
    std::vector<int> dist(total_cells, -1);
    std::vector<int> parent(total_cells, -1);

    Queue *queue = queue_create();

    int start_id = start_r * cols + start_c;
    int end_id = end_r * cols + end_c;

    dist[start_id] = 0;
    queue_insert(queue, start_id);

    const int dr[8] = {-1, -1, -1, 1, 1, 0, 1, 0};
    const int dc[8] = {-1, 0, 1, -1, 0, 1, 1, -1};

    while (!queue_empty(queue))
    {
        int curr = queue_get(queue);
        queue_remove(queue);

        if (curr == end_id)
        {
            break;
        }

        int r = curr / cols;
        int c = curr % cols;

        for (int d = 0; d < 8; ++d)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            while (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != '#')
            {
                int next_id = nr * cols + nc;
                if (dist[next_id] == -1)
                {
                    dist[next_id] = dist[curr] + 1;
                    parent[next_id] = curr;
                    queue_insert(queue, next_id);
                }
                nr += dr[d];
                nc += dc[d];
            }
        }
    }

    queue_delete(queue);

    if (dist[end_id] != -1)
    {
        std::vector<int> path;
        int curr = end_id;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }

        for (size_t i = 0; i < path.size(); ++i)
        {
            int step = static_cast<int>(path.size() - 1 - i);
            int pr = path[i] / cols;
            int pc = path[i] % cols;
            char step_char = (step < 10) ? static_cast<char>('0' + step) : static_cast<char>('A' + (step - 10));
            maze[pr][pc] = step_char;
        }

        for (int r = 0; r < rows; ++r)
        {
            std::cout << maze[r] << "\n";
        }
    }
    else
    {
        std::cout << "No path\n";
    }

    return 0;
}