#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <cstdio>
#include "graph.h"
using namespace std;

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (freopen(argv[1], "r", stdin) == nullptr)
        {
            cerr << "Error opening file: " << argv[1] << endl;
            return 1;
        }
    }

    int n;
    if (!(cin >> n))
    {
        cerr << "No input\n";
        return 1;
    }

    vector<string> names(n);
    for (int i = 0; i < n; i++)
    {
        cin >> names[i];
    }

    map<string, int> index;
    for (int i = 0; i < n; i++)
    {
        index[names[i]] = i;
    }

    Graph<string, int> g(static_cast<size_t>(n));
    for (int i = 0; i < n; i++)
    {
        g.setVertexData(static_cast<size_t>(i), names[i]);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        string from, to;
        int w;
        cin >> from >> to >> w;

        int u = index[from];
        int v = index[to];

        g.addEdge(static_cast<size_t>(u), static_cast<size_t>(v));
        g.setEdgeData(static_cast<size_t>(u), static_cast<size_t>(v), w);
    }

    size_t N = g.verticesCount();
    const int INF = numeric_limits<int>::max() / 4;

    vector<vector<int>> dist(N, vector<int>(N, INF));
    vector<vector<int>> next(N, vector<int>(N, -1));

    for (size_t i = 0; i < N; i++)
    {
        dist[i][i] = 0;
        next[i][i] = static_cast<int>(i);
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (g.hasEdge(i, j))
            {
                dist[i][j] = g.getEdgeData(i, j);
                next[i][j] = static_cast<int>(j);
            }
        }
    }

    for (size_t k = 0; k < N; k++)
    {
        for (size_t i = 0; i < N; i++)
        {
            if (dist[i][k] == INF)
                continue;
            for (size_t j = 0; j < N; j++)
            {
                if (dist[k][j] == INF)
                    continue;
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    cout << "All-pairs shortest paths:\n";
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (i == j)
                continue;

            cout << g.getVertexData(i) << " -> " << g.getVertexData(j) << ": ";
            if (next[i][j] == -1)
            {
                cout << "no path\n";
            }
            else
            {
                size_t u = i;
                cout << g.getVertexData(u);
                while (u != j)
                {
                    int v = next[u][j];
                    u = static_cast<size_t>(v);
                    cout << " " << g.getVertexData(u);
                }
                cout << " (" << dist[i][j] << ")\n";
            }
        }
    }
}
