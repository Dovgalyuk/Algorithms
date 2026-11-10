#include "queue.h"
#include "vector.h"

#include <iostream>
#include <fstream>

using namespace std;

int bidirectionalSearch(const Vector *graph, int size, int start, int finish)
{
    if (start == finish)
        return 0;
    Vector *distStart = vector_create();
    Vector *distFinish = vector_create();
    vector_resize(distStart, (size_t)size);
    vector_resize(distFinish, (size_t)size);
    for (int v = 0; v < size; ++v)
    {
        vector_set(distStart, (size_t)v, -1);
        vector_set(distFinish, (size_t)v, -1);
    }
    Queue *qStart = queue_create();
    Queue *qFinish = queue_create();
    vector_set(distStart, (size_t)start, 0);
    vector_set(distFinish, (size_t)finish, 0);
    queue_insert(qStart, start);
    queue_insert(qFinish, finish);

    int best = INT_MAX;
    while (!queue_empty(qStart) and !queue_empty(qFinish))
    {
        int levelStart = vector_get(distStart, (size_t)queue_get(qStart));
        int levelFinish = vector_get(distFinish, (size_t)queue_get(qFinish));
        if (levelStart + levelFinish >= best)
            break;
        if (levelStart <= levelFinish)
        {
            int v = queue_get(qStart);
            queue_remove(qStart);

            for (int u = 0; u < size; ++u)
            {
                if (vector_get(graph, (size_t)v * size + u) == 0)
                    continue;
                if (vector_get(distStart, (size_t)u) == -1)
                {
                    vector_set(distStart, (size_t)u, levelStart + 1);
                    if (vector_get(distFinish, (size_t)u) != -1)
                    {
                        int path = levelStart + 1 + vector_get(distFinish, (size_t)u);
                        if (path < best) best = path;
                    }
                    queue_insert(qStart, u);
                }
            }
        }
        else
        {
            int v = queue_get(qFinish);
            queue_remove(qFinish);
            for (int u = 0; u < size; ++u)
            {
                if (vector_get(graph, (size_t)u * size + v) == 0)
                    continue;
                if (vector_get(distFinish, (size_t)u) == -1)
                {
                    vector_set(distFinish, (size_t)u, levelFinish + 1);
                    if (vector_get(distStart, (size_t)u) != -1)
                    {
                        int path = levelFinish + 1 + vector_get(distStart, (size_t)u);
                        if (path < best) best = path;
                    }
                    queue_insert(qFinish, u);
                }
            }
        }
    }

    queue_delete(qStart);
    queue_delete(qFinish);
    vector_delete(distStart);
    vector_delete(distFinish);
    return best;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin)
    {
        cout << "Error\n";
        return 1;
    }
    int size, start, finish;
    if (!(fin >> size >> start >> finish))
    {
        cout << "Error\n";
        return 1;
    }
    if (size <= 0)
    {
        cout << "Error\n";
        return 1;
    }
    if (start < 1 || start > size || finish < 1 || finish > size)
    {
        cout << "Error\n";
        return 1;
    }

    --start;
    --finish;
    Vector *graph = vector_create();
    vector_resize(graph, (size_t)size * size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int weight = 0;
            if (!(fin >> weight))
            {
                cout << "Error\n";
                vector_delete(graph);
                return 1;
            }
            vector_set(graph, (size_t)i * size + j, weight);
        }
    }
    fin.close();

    int best = bidirectionalSearch(graph, size, start, finish);
    if (best == INT_MAX)
        cout << "IMPOSSIBLE\n";
    else
        cout << best << "\n";

    vector_delete(graph);
}