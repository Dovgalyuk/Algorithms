#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

typedef Graph<string, int> MyGraph;
const long long INF = 1000000000000000000LL;
bool hasNegativeCycle(const vector<vector<long long> > &dist)
{
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Cannot open " << argv[1] << "\n";
        return 1;
    }
    MyGraph g;
    g.read(in);
    if (in.fail())
    {
        cerr << "Invalid graph description\n";
        return 1;
    }

    size_t n = g.vertexCount();
    vector<vector<long long> > dist(n, vector<long long>(n, INF));
    vector<vector<size_t> > nextStep(n, vector<size_t>(n, n));
    for (size_t i = 0; i < n; i++)
    {
        dist[i][i] = 0;
        nextStep[i][i] = i;
    }

    for (size_t u = 0; u < n; u++)
    {
        for (MyGraph::NeighborIterator it = g.neighbors(u); it.valid(); it.next())
        {
            size_t v = it.vertex();
            long long w = it.label();
            if (w < dist[u][v])
            {
                dist[u][v] = w;
                nextStep[u][v] = v;
            }
        }
    }
    if (hasNegativeCycle(dist))
    {
        cerr << "Negative cycle detected\n";
        return 1;
    }
    for (size_t k = 0; k < n; k++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (dist[i][k] == INF)
                continue;
            for (size_t j = 0; j < n; j++)
            {
                if (dist[k][j] == INF)
                    continue;
                long long candidate = dist[i][k] + dist[k][j];
                if (candidate < dist[i][j])
                {
                    dist[i][j] = candidate;
                    nextStep[i][j] = nextStep[i][k];
                }
            }
        }

        if (hasNegativeCycle(dist))
        {
            cerr << "Negative cycle detected\n";
            return 1;
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << g.getVertexLabel(i) << " -> " << g.getVertexLabel(j) << ": ";
            if (dist[i][j] == INF)
            {
                cout << "INF\n";
                continue;
            }

            cout << dist[i][j] << "; " << g.getVertexLabel(i);
            size_t current = i;
            while (current != j)
            {
                current = nextStep[current][j];
                cout << " -> " << g.getVertexLabel(current);
            }
            cout << "\n";
        }
    }
    return 0;
}