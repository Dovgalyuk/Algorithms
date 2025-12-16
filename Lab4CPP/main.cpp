#include "graph.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
        return 0;

    ifstream fin(argv[1]);
    if (!fin)
        return 0;

    size_t n, m;
    fin >> n >> m;

    Graph<double, string> g(n);

    map<string, size_t> indexByName;
    vector<string> names(n);
    for (size_t i = 0; i < n; ++i)
    {
        fin >> names[i];
        indexByName[names[i]] = i;
        g.setVertexLabel(i, names[i]);
    }

    for (size_t i = 0; i < m; ++i)
    {
        string a, b;
        double w;
        fin >> a >> b >> w;
        g.addEdge(indexByName[a], indexByName[b], w);
    }

    string startName, finishName;
    fin >> startName >> finishName;

    size_t start = indexByName[startName];
    size_t finish = indexByName[finishName];

    size_t N = g.vertexCount();
    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(N, INF);
    vector<size_t> parent(N, N);
    vector<bool> used(N, false);

    priority_queue<pair<double,size_t>, vector<pair<double,size_t>>, greater<pair<double,size_t>>> pq;
    dist[start] = 0.0;
    pq.push({0.0, start});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        size_t v = cur.second;
        if (used[v])
            continue;
        used[v] = true;
        if (v == finish)
            break;

        for (auto it = g.neighborsBegin(v); it != g.neighborsEnd(v); ++it)
        {
            size_t to = *it;
            double w = g.getEdgeLabel(v, to);
            if (dist[v] + w < dist[to])
            {
                dist[to] = dist[v] + w;
                parent[to] = v;
                pq.push({dist[to], to});
            }
        }
    }

    if (dist[finish] == INF)
    {
        cout << "No path\n";
        return 0;
    }

    vector<size_t> path;
    for (size_t v = finish; ; )
    {
        path.push_back(v);
        if (v == start)
            break;
        v = parent[v];
        if (v == N)
        {
            cout << "No path\n";
            return 0;
        }
    }

    reverse(path.begin(), path.end());

    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "Distance: " << dist[finish] << '\n';
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i > 0) cout << ' ';
        cout << g.getVertexLabel(path[i]);
    }
    cout << '\n';

    return 0;
}
