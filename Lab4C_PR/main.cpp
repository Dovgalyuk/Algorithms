#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "graph.h"

using namespace std;

struct EdgeU { int u, v, w; };

// DSU: структура для объединения компонент (для Крускала).

struct DSU {
    vector<int> p, r;
    explicit DSU(int n = 0) : p(n), r(n, 0) { for (int i = 0; i < n; ++i) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);

        if (a == b)
            return false;
        if (r[a] < r[b])
            swap(a, b);

        p[b] = a;

        if (r[a] == r[b])
            ++r[a];

        return true;
    }
};

int main(int argc, char** argv) {
    int N, M;

    ifstream fin;
    istream& in = (argc > 1 && (fin.open(argv[1]), fin)) ? static_cast<std::istream&>(fin) : cin;

    if (!(in >> N >> M))
        return 0;

    vector<string> names(N);
    map<string, int> id;

    for (int i = 0; i < N; ++i) {
        in >> names[i];
        id[names[i]] = i;
    }

    Graph<string, int> g(N);

    for (int i = 0; i < N; ++i)
        g.set_vertex_label(i, names[i]);

    vector<EdgeU> edges; edges.reserve(M);

    for (int i = 0; i < M; ++i) {
        string su, sv; int w;
        in >> su >> sv >> w;
        int u = id[su], v = id[sv];

        edges.push_back({ u,v,w });
        g.add_edge(u, v, w);
        g.add_edge(v, u, w);
    }

    // Сортировка по весу (Крускал).

    sort(edges.begin(), edges.end(), [](const EdgeU& a, const EdgeU& b) { return a.w < b.w; });
    DSU dsu(N);
    int total = 0;
    vector<EdgeU> mst;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            mst.push_back(e);
        }
    }

    cout << "MST weight = " << total << "\n";

    for (auto& e : mst)
        cout << names[e.u] << " - " << names[e.v] << " (" << e.w << ")\n";

    return 0;
}