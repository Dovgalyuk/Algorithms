#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../LibraryCPPTemplate/graph.h"


using namespace std;

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

    size_t n;
    if (!(fin >> n))
    {
        cerr << "Failed to read vertex count\n";
        return 1;
    }


    vector<string> names(n);
    for (size_t i = 0; i < n; ++i)
    {
        fin >> names[i];
        if (!fin)
        {
            cerr << "Failed to read vertex name\n";
            return 1;
        }
    }

    Graph<string, int> g(n);
    for (size_t i = 0; i < n; ++i)
    {
        g.SetVertexLabel(i, names[i]);
    }

    const int INF = 1000000000;
    vector<vector<int>> dist(n, vector<int>(n, INF));


    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            int w;
            fin >> w;
            if (!fin)
            {
                cerr << "Not enough weights in input.txt\n";
                return 1;
            }

            if (i == j)
            {
                dist[i][j] = 0;
            }
            else if (w >= 0)
            {
                g.AddEdge(i, j, w);
                dist[i][j] = w;
            }
            else
            {
                dist[i][j] = INF;
            }
        }
    }



    for (size_t k = 0; k < n; ++k)
    {
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }


    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            cout << names[i] << " -> " << names[j] << " : ";
            if (dist[i][j] >= INF)
                cout << "NO PATH\n";
            else
                cout << dist[i][j] << "\n";
        }
    }


}