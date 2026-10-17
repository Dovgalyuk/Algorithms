#include <iostream>
#include <fstream>
#include <limits>
#include "queue.h"
#include "vector.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Use: " << argv[0] << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open())
    {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    Data n = 0;
    Data start = 0;
    Data finish = 0;
    if (!(fin >> n >> start >> finish))
    {
        return 1;
    }

    const Data UNVISITED = std::numeric_limits<Data>::max();

    const size_t size_n = static_cast<size_t>(n);

    Vector* matrix = vector_create();
    vector_resize(matrix, size_n * size_n);
    for (Data i = 0; i < n; ++i)
    {
        for (Data j = 0; j < n; ++j)
        {
            Data v = 0;
            fin >> v;
            vector_set(matrix,
                static_cast<size_t>(i) * size_n + static_cast<size_t>(j),
                v);
        }
    }
    fin.close();

    Vector* dist = vector_create();
    vector_resize(dist, size_n);
    for (Data i = 0; i < n; ++i)
    {
        vector_set(dist, static_cast<size_t>(i), UNVISITED);
    }

    const Data s = start - 1;
    const Data f = finish - 1;

    Queue* q = queue_create();

    vector_set(dist, static_cast<size_t>(s), static_cast<Data>(0));
    queue_insert(q, s);

    while (!queue_empty(q))
    {
        Data u = queue_get(q);
        queue_remove(q);

        if (u == f)
        {
            break;
        }

        const size_t u_row = static_cast<size_t>(u) * size_n;

        for (Data v = 0; v < n; ++v)
        {
            const size_t v_idx = static_cast<size_t>(v);

            if (vector_get(matrix, u_row + v_idx) != 0 &&
                vector_get(dist, v_idx) == UNVISITED)
            {
                vector_set(dist, v_idx,
                    vector_get(dist, static_cast<size_t>(u)) + static_cast<Data>(1));
                queue_insert(q, v);
            }
        }
    }

    const Data answer = vector_get(dist, static_cast<size_t>(f));

    if (answer == UNVISITED)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        cout << answer;
    }

    queue_delete(q);
    vector_delete(dist);
    vector_delete(matrix);

    return 0;
}