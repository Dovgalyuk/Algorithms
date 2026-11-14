#include <climits>
#include <iostream>
#include <vector>
#include "graph.h"
using namespace std;
int main() {
    Graph<long long, int> g;
    if (!g.Read(cin)) {
        cerr << "input error\n";
        return 1;
    }

    const long long INF = LLONG_MAX / 4;
    const size_t n = g.Size();
    vector<vector<long long>> d(n, vector<long long>(n, INF));
    vector<vector<int>> nxt(n, vector<int>(n, -1));

    // начальная матрица расстояний из рёбер графа
    for (size_t i = 0; i < n; ++i) {
        d[i][i] = 0;
        nxt[i][i] = static_cast<int>(i);
        for (auto it = g.NeighborsOf(i); it.Valid(); it.Next()) {
            size_t j = it.To();
            if (it.Label() < d[i][j]) {
                d[i][j] = it.Label();
                nxt[i][j] = static_cast<int>(j);
            }
        }
    }

    // алгоритм Флойда
    for (size_t k = 0; k < n; ++k)
        for (size_t i = 0; i < n; ++i) {
            if (d[i][k] >= INF) continue;           // в k из i не попасть
            for (size_t j = 0; j < n; ++j) {
                if (d[k][j] >= INF) continue;
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }

    //  отрицательный цикл делает кратчайшие пути бессмысленными
    for (size_t i = 0; i < n; ++i)
        if (d[i][i] < 0) {
            cerr << "negative cycle\n";
            return 1;
        }

    //  самый длинный из кратчайших путей
    bool found = false;
    long long best = 0;
    size_t bi = 0, bj = 0;
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            if (i != j && d[i][j] < INF && (!found || d[i][j] > best)) {
                found = true;
                best = d[i][j];
                bi = i;
                bj = j;
            }

    if (!found) {
       cout << "no paths\n";
        return 0;
    }

    // вывод длины и пути по матрице nxt
    cout << best << "\n";
    size_t u = bi;
    cout << g.NameOf(u);
    while (u != bj) {
        u = static_cast<size_t>(nxt[u][bj]);
        cout << " " << g.NameOf(u);
    }
    cout << "\n";
    return 0;
}