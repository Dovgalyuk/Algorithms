#include <iostream>
#include <string>
#include <fstream>

#include "../LibraryCPPTemplate/graph.h"

using namespace std;

static const int INF = 1000000000;

static bool FindIndex(const string* names, size_t n, const string& name, size_t& outIndex)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (names[i] == name)
        {
            outIndex = i;
            return true;
        }
    }
    return false;
}

static void PrintPath(const string* names, size_t n, int** next, size_t i, size_t j)
{
    if (next[i][j] < 0)
    {
        cout << "NO PATH\n";
        return;
    }

    size_t u = i;
    cout << names[u];

    size_t steps = 0;
    while (u != j)
    {
        int nu = next[u][j];
        if (nu < 0) { cout << " -> ?\n"; return; }
        u = (size_t)nu;

        cout << " -> " << names[u];

        if (++steps > n) { cout << " (cycle?)\n"; return; }
    }
    cout << "\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open())
    {
        cerr << "Failed to open " << argv[1] << "\n";
        return 1;
    }


    size_t n = 0;
    if (!(fin >> n) || n == 0)
    {
        cerr << "Failed to read vertex count\n";
        return 1;
    }

    string* names = new string[n];
    for (size_t i = 0; i < n; ++i)
    {
        fin >> names[i];
        if (!fin)
        {
            cerr << "Failed to read vertex name\n";
            delete[] names;
            return 1;
        }
    }

    Graph<string, int> g(n);
    for (size_t i = 0; i < n; ++i)
        g.SetVertexLabel(i, names[i]);

    size_t m = 0;
    if (!(fin >> m))
    {
        cerr << "Failed to read edge count m\n";
        delete[] names;
        return 1;
    }

    int** dist = new int* [n];
    int** next = new int* [n];
    for (size_t i = 0; i < n; ++i)
    {
        dist[i] = new int[n];
        next[i] = new int[n];
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            dist[i][j] = (i == j) ? 0 : INF;
            next[i][j] = (i == j) ? (int)i : -1;
        }
    }


    for (size_t e = 0; e < m; ++e)
    {
        string fromName, toName;
        int w = 0;

        fin >> fromName >> toName >> w;
        if (!fin)
        {
            cerr << "Failed to read edge " << e << " (expected: from to w)\n";

            for (size_t i = 0; i < n; ++i) { delete[] dist[i]; delete[] next[i]; }
            delete[] dist; delete[] next; delete[] names;
            return 1;
        }

        size_t from = 0, to = 0;
        if (!FindIndex(names, n, fromName, from) || !FindIndex(names, n, toName, to))
        {
            cerr << "Unknown vertex name in edge: " << fromName << " " << toName << "\n";
            for (size_t i = 0; i < n; ++i) { delete[] dist[i]; delete[] next[i]; }
            delete[] dist; delete[] next; delete[] names;
            return 1;
        }

        g.AddEdge(from, to, w);

        if (w < dist[from][to])
        {
            dist[from][to] = w;
            next[from][to] = (int)to;
        }
    }

    for (size_t k = 0; k < n; ++k)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (dist[i][k] >= INF) continue;
            for (size_t j = 0; j < n; ++j)
            {
                if (dist[k][j] >= INF) continue;

                int cand = dist[i][k] + dist[k][j];
                if (cand < dist[i][j])
                {
                    dist[i][j] = cand;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            cout << names[i] << " -> " << names[j] << " : ";
            PrintPath(names, n, next, i, j);
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        delete[] dist[i];
        delete[] next[i];
    }
    delete[] dist;
    delete[] next;
    delete[] names;


}