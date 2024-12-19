#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm> // Include this header for the reverse function
#include "graph.h"

using namespace std;

template <typename V, typename E>
vector<size_t> dijkstra(Graph<V, E>& graph, size_t start, size_t end) {
    size_t n = graph.getSize();
    vector<E> dist(n, numeric_limits<E>::max());
    vector<size_t> prev(n, numeric_limits<size_t>::max());
    priority_queue<pair<E, size_t>, vector<pair<E, size_t>>, greater<pair<E, size_t>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        size_t u = pq.top().second;
        pq.pop();

        if (u == end) {
            // Reconstruct the path
            vector<size_t> path;
            for (size_t at = end; at != numeric_limits<size_t>::max(); at = prev[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto i = graph.begin(u); i != graph.end(u); ++i) {
            size_t v = (*i).path;
            E weight = (*i).sign;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {};
}

bool test1(const vector<size_t>& result) {
    vector<size_t> expected_path = {0,4,1,2};
    if (result != expected_path) {
        for (size_t v : result) {
            cout << v << " ";
        }
        cout << endl;
        return true;
    }
    for (size_t v : result) {
        cout << v << " ";
    }
    cout << endl;
    return false;
}

int main(int argc, char **argv) {
    ifstream f(argv[1]);
    if(!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
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

    vector<size_t> result = dijkstra(graph, start, end);
    if(test1(result)) {
        return 1;
    }
    return 0;
}
