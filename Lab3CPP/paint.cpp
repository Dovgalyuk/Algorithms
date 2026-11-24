#include <fstream>
#include <iostream>
#include "array.h"
#include "queue.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " input output\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    int n, m;
    if (!(input >> n >> m) || n <= 0 || m <= 0)
    {
        std::cerr << "Can't read board size\n";
        return 1;
    }

    Array *color = array_create((size_t)n * m);
    Queue *queue = queue_create();

    int r, c;
    while (input >> r >> c)
    {
        if (r < 1 || r > n || c < 1 || c > m)
            continue;
        int cell = (r - 1) * m + (c - 1);
        if (array_get(color, cell) == 0)
        {
            array_set(color, cell, 1);
            queue_insert(queue, cell);
        }
    }

    const int dr[] = { -1, 1, 0, 0 };
    const int dc[] = { 0, 0, -1, 1 };
    int colors = 0;
    while (!queue_empty(queue))
    {
        int cell = queue_get(queue);
        queue_remove(queue);
        int k = array_get(color, cell);
        if (k > colors)
            colors = k;
        int row = cell / m;
        int col = cell % m;
        for (int d = 0 ; d < 4 ; ++d)
        {
            int nr = row + dr[d];
            int nc = col + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
            int next = nr * m + nc;
            if (array_get(color, next) == 0)
            {
                array_set(color, next, k + 1);
                queue_insert(queue, next);
            }
        }
    }

    std::ofstream output(argv[2]);
    output << colors << '\n';

    queue_delete(queue);
    array_delete(color);
}
