#include "queue.h"

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

void bfsStep(const Vector *graph, int size, int v, int level,
                   Vector *distThis, Vector *distOther,
                   Queue *q, bool forward, int &best)
{
    for (int u = 0; u < size; ++u)
    {
        int hasEdge = forward
            ? vector_get(graph, (size_t)v * size + u)
            : vector_get(graph, (size_t)u * size + v);
        if (hasEdge == 0) continue;
        if (vector_get(distThis, (size_t)u) != -1) continue;

        vector_set(distThis, (size_t)u, level + 1);
        int otherDist = vector_get(distOther, (size_t)u);
        if (otherDist != -1)
        {
            int path = level + 1 + otherDist;
            if (path < best)
                best = path;
        }
        queue_insert(q, u);
    }
}

int bidirectionalSearch(const Vector *graph, int size, int start, int finish)
{
    if (start == finish) return 0;

    Vector *distStart  = vector_create();
    Vector *distFinish = vector_create();
    vector_resize(distStart,  (size_t)size);
    vector_resize(distFinish, (size_t)size);
    for (int v = 0; v < size; ++v)
    {
        vector_set(distStart,  (size_t)v, -1);
        vector_set(distFinish, (size_t)v, -1);
    }

    Queue *qStart  = queue_create();
    Queue *qFinish = queue_create();

    vector_set(distStart,  (size_t)start,  0);
    vector_set(distFinish, (size_t)finish, 0);
    queue_insert(qStart,  start);
    queue_insert(qFinish, finish);

    int best = INT_MAX;
    while (!queue_empty(qStart) && !queue_empty(qFinish))
    {
        int levelStart  = vector_get(distStart,  (size_t)queue_get(qStart));
        int levelFinish = vector_get(distFinish, (size_t)queue_get(qFinish));
        if (levelStart + levelFinish >= best) break;

        if (levelStart <= levelFinish)
        {
            int v = queue_get(qStart);
            queue_remove(qStart);
            bfsStep(graph, size, v, levelStart,
                   distStart, distFinish, qStart, true, best);
        }
        else
        {
            int v = queue_get(qFinish);
            queue_remove(qFinish);
            bfsStep(graph, size, v, levelFinish,
                   distFinish, distStart, qFinish, false, best);
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