#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

void bfs_step(int n, const int *matrix, Queue *q, int *dist_current, const int *dist_other, int &min_dist, bool forward)
{
    int u = queue_get(q);
    queue_remove(q);

    for (int v = 0; v < n; ++v)
    {
        bool has_edge = forward ? (matrix[u * n + v] != 0) : (matrix[v * n + u] != 0);
        if (has_edge)
        {
            if (dist_current[v] == -1)
            {
                dist_current[v] = dist_current[u] + 1;
                queue_insert(q, v);
            }

            if (dist_other[v] != -1)
            {
                int total = dist_current[u] + 1 + dist_other[v];
                if (min_dist == -1 || total < min_dist)
                {
                    min_dist = total;
                }
            }
        }
    }
}

int find_shortest_path(int n, int start, int target, const int *matrix)
{
    if (start == target)
    {
        return 0;
    }

    int *dist_fwd = new int[n];
    int *dist_bwd = new int[n];
    for (int i = 0; i < n; ++i)
    {
        dist_fwd[i] = -1;
        dist_bwd[i] = -1;
    }

    Queue *q_fwd = queue_create();
    Queue *q_bwd = queue_create();

    dist_fwd[start] = 0;
    queue_insert(q_fwd, start);

    dist_bwd[target] = 0;
    queue_insert(q_bwd, target);

    int min_dist = -1;

    while (!queue_empty(q_fwd) && !queue_empty(q_bwd))
    {
        if (min_dist != -1)
        {
            int front_fwd = queue_get(q_fwd);
            int front_bwd = queue_get(q_bwd);
            if (dist_fwd[front_fwd] + dist_bwd[front_bwd] >= min_dist)
            {
                break;
            }
        }

        bfs_step(n, matrix, q_fwd, dist_fwd, dist_bwd, min_dist, true);
        bfs_step(n, matrix, q_bwd, dist_bwd, dist_fwd, min_dist, false);
    }

    delete[] dist_fwd;
    delete[] dist_bwd;
    queue_delete(q_fwd);
    queue_delete(q_bwd);

    return min_dist;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "usage: " << argv[0] << " input.txt [output.txt]\n";
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cout << "cannot open file " << argv[1] << "\n";
        return 1;
    }

    int n = 0, start = 0, target = 0;
    if (!(input >> n >> start >> target))
    {
        cout << "invalid input data\n";
        return 1;
    }

    int *matrix = new int[n * n];
    for (int i = 0; i < n * n; ++i)
    {
        input >> matrix[i];
    }

    ofstream output;
    if (argc > 2)
    {
        output.open(argv[2]);
    }

    if (start < 1 || start > n || target < 1 || target > n)
    {
        cout << "IMPOSSIBLE\n";
        if (output.is_open())
        {
            output << "IMPOSSIBLE\n";
        }
    }
    else
    {
        int dist = find_shortest_path(n, start - 1, target - 1, matrix);
        if (dist == -1)
        {
            cout << "IMPOSSIBLE\n";
            if (output.is_open())
            {
                output << "IMPOSSIBLE\n";
            }
        }
        else
        {
            cout << dist << "\n";
            if (output.is_open())
            {
                output << dist << "\n";
            }
        }
    }

    delete[] matrix;
    return 0;
}
