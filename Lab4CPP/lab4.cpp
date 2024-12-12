#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <fstream>
#include "graph.h"

using namespace std;

template <typename V, typename E>
int dijkstra(Graph<V, E>& graph, size_t start, size_t end) {
    size_t n = graph.getSize();
    vector<E> dist(n, numeric_limits<E>::max());
    set<pair<E, size_t>> pq;

    dist[start] = 0;
    pq.insert({0, start});

    while (!pq.empty()) {
        size_t u = pq.begin()->second;
        E d = pq.begin()->first;
        pq.erase(pq.begin());

        if (u == end) {
            return d;
        }

        for (auto i = graph.begin(u); i != graph.end(u); ++i) {
            size_t v = (*i).path;
            E weight = (*i).sign;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.insert({dist[v], v});
            }
        }
    }

    return 0;
}

bool test1(int result) {
    if (result != 9) {
        cout << result << endl;
        return true;
    }
    cout << result << endl;
    return false;
}

int main(int argc, char **argv) {
    ifstream f(argv[1]);
    if(!f.is_open()) {
        cout << "Error opening file" << endl;
    }

    size_t n, m;
    f >> n >> m;

    Graph<int, int> graph(n);

    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        int w;
        f >> u >> v >> w;
        graph.addEdge(u, v, w);
        graph.addEdge(v, u, w);
    }

    size_t start, end;
    f >> start >> end;

    int result = dijkstra(graph, start, end);
    if(test1(result)) {
        return 1;
    }
    return 0;
}
