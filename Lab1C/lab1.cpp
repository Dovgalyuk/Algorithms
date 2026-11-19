#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

using namespace std;

int main(int argc, char *argv[])
{
    const char *input_name = (argc > 1) ? argv[1] : "input.txt";
    const char *output_name = (argc > 2) ? argv[2] : "output.txt";

    ifstream in(input_name);
    ofstream out(output_name);

    if (!in)
    {
        cerr << "Cannot open input file\n";
        return 1;
    }

    size_t n;
    in >> n;

    Vector *adj = vector_create();
    vector_resize(adj, n * n);
    for (size_t i = 0; i < n * n; i++)
    {
        int x;
        in >> x;
        vector_set(adj, i, x);
    }

    Vector *dist = vector_create();
    vector_resize(dist, n);
    for (size_t i = 0; i < n; i++)
        vector_set(dist, i, -1);
    vector_set(dist, 0, 0);

    Queue *queue = queue_create();
    queue_insert(queue, (Data)0);

    while (!queue_empty(queue))
    {
        size_t v = (size_t)queue_get(queue);
        queue_remove(queue);

        for (size_t u = 0; u < n; u++)
        {
            if (vector_get(adj, v * n + u) != 0 &&
                vector_get(dist, u) == -1)
            {
                vector_set(dist, u, vector_get(dist, v) + 1);
                queue_insert(queue, (Data)u);
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        out << vector_get(dist, i);
        if (i + 1 < n)
            out << " ";
        else
            out << "\n";
    }

    for (size_t i = 0; i < n; i++)
    {
        cout << vector_get(dist, i);
        if (i + 1 < n)
            cout << " ";
    }
    cout << "\n";

    queue_delete(queue);
    vector_delete(dist);
    vector_delete(adj);
    return 0;
}
