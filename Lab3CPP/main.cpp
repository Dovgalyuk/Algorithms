#include <iostream>
#include <string>
#include "queue.h"

int main()
{
    std::string board[8];
    int start = -1;
    int finish = -1;

    for (int row = 0; row < 8; ++row)
    {
        if (!(std::cin >> board[row]) || board[row].size() != 8)
            return 1;

        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col] == 'K')
                start = row * 8 + col;
            if (board[row][col] == 'E')
                finish = row * 8 + col;
        }
    }

    if (start == -1 || finish == -1)
        return 1;

    int parent[64];
    for (int i = 0; i < 64; ++i)
        parent[i] = -1;

    const int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    const int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    Queue *queue = queue_create();
    queue_insert(queue, start);
    parent[start] = start;

    while (!queue_empty(queue) && parent[finish] == -1)
    {
        int cell = queue_get(queue);
        queue_remove(queue);
        int row = cell / 8;
        int col = cell % 8;

        for (int move = 0; move < 8; ++move)
        {
            int new_row = row + dr[move];
            int new_col = col + dc[move];

            if (new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
                continue;
            if (board[new_row][new_col] == '#')
                continue;

            int next = new_row * 8 + new_col;
            if (parent[next] != -1)
                continue;

            parent[next] = cell;
            queue_insert(queue, next);
        }
    }

    queue_delete(queue);

    int steps[64];
    for (int i = 0; i < 64; ++i)
        steps[i] = -1;

    if (parent[finish] != -1)
    {
        int path[64];
        int length = 0;
        for (int cell = finish; cell != start; cell = parent[cell])
            path[length++] = cell;
        path[length++] = start;

        for (int i = length - 1; i >= 0; --i)
        {
            int cell = path[i];
            steps[cell] = length - 1 - i;
        }
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            int cell = row * 8 + col;
            if (steps[cell] >= 0)
                std::cout << steps[cell];
            else
                std::cout << board[row][col];
        }
        std::cout << '\n';
    }
}
