#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "vector.h"
#include "pqueue.h"

using namespace std;

size_t find_vertex(const string* names, size_t n, const string& name)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (names[i] == name)
            return i;
    }
    return static_cast<size_t>(-1);
}

int main(int argc, char* argv[]) {
    ifstream input;
    if (argc > 1)
    {
        input.open(argv[1]);
    }
    size_t N, M;
    input >> N >> M;

    Graph<string, int> g(N);

    string* names = new string[N];
    for (size_t i = 0; i < N; ++i)
    {
        input >> names[i];
        g.set_vertex_label(i, names[i]);
    }

    for (size_t i = 0; i < M; ++i)
    {
        string uName, vName;
        int w;
        input >> uName >> vName >> w;

        size_t u = find_vertex(names, N, uName);
        size_t v = find_vertex(names, N, vName);

        g.add_edge(u, v, w);
    }

    string startName, finishName;
    input >> startName >> finishName;

    size_t start = find_vertex(names, N, startName);
    size_t finish = find_vertex(names, N, finishName);

    const int INF = 1000000000;

    int* dist = new int[N];
    int* parent = new int[N];

    for (size_t i = 0; i < N; ++i)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;

    PriorityQueue* pq = pqueue_create();
    pqueue_push(pq, static_cast<int>(start), dist);

    while (!pqueue_empty(pq))
    {
        int u = pqueue_pop(pq, dist);

        auto it = g.neighbors(static_cast<size_t>(u));
        while (it.valid())
        {
            size_t v = it.vertex_id();
            int w = it.edge_label();

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pqueue_push(pq, static_cast<int>(v), dist);
            }

            it.next();
        }
    }

    if (dist[finish] == INF)
    {
        cout << "No path\n";

        pqueue_delete(pq);
        delete[] dist;
        delete[] parent;
        delete[] names;
        return 0;
    }

    size_t* path = new size_t[N];
    size_t len = 0;

    size_t cur = finish;
    while (true)
    {
        path[len++] = cur;
        if (cur == start)
            break;
        cur = static_cast<size_t>(parent[cur]);
    }

    for (size_t i = 0; i < len / 2; ++i)
    {
        size_t j = len - 1 - i;
        size_t tmp = path[i];
        path[i] = path[j];
        path[j] = tmp;
    }

    cout << dist[finish] << "\n";

    for (size_t i = 0; i < len; ++i)
    {
        cout << names[path[i]];
        if (i + 1 < len)
            cout << " ";
    }
    cout << "\n";

    pqueue_delete(pq);
    delete[] dist;
    delete[] parent;
    delete[] path;
    delete[] names;

    return 0;
}