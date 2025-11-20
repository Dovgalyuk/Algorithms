#include <iostream>
#include "queue.h"
using namespace std;

int main(int argc, char** argv)
{
    if (argc > 1)
        freopen(argv[1], "r", stdin);

    int n, s, f;
    cin >> n >> s >> f;
    s--; f--;

    int g[200][200];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    int dist[200];
    for (int i = 0; i < n; i++) 
        dist[i] = -1;

    Queue* q = queue_create();
    dist[s] = 0;
    queue_insert(q, s);

    while (!queue_empty(q))
    {
        int v = queue_get(q);
        queue_remove(q);

        for (int to = 0; to < n; to++)
        {
            if (g[v][to] != 0 && dist[to] == -1) 
            {
                dist[to] = dist[v] + 1;
                queue_insert(q, to);
            }
        }
    }

    queue_delete(q);

    if (dist[f] == -1)
        cout << "IMPOSSIBLE\n";
    else
        cout << dist[f] << "\n";
}