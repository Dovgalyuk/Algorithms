#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>
#include "graph.h"

using GraphType = Graph<std::string, int>;
using SizeType = std::size_t;
using NeighborIt = GraphType::NeighborIterator;

struct Edge {
    int to, rev;
    int capacity;
};

class FordFulkerson {
private:
    int n;
    std::vector<std::vector<Edge>> adj;

public:
    FordFulkerson(int vertices) : n(vertices), adj(vertices) {}

    void add_edge(int from, int to, int cap) {
        Edge a{to, (int)adj[to].size(), cap};
        Edge b{from, (int)adj[from].size(), 0};
        adj[from].push_back(a);
        adj[to].push_back(b);
    }

    int max_flow(int s, int t) {
        int total_flow = 0;

        while (true) {
            std::vector<int> parent(n, -1);
            std::vector<int> parent_edge(n, -1);
            std::queue<int> q;
            q.push(s);
            parent[s] = s;

            while (!q.empty() && parent[t] == -1) {
                int v = q.front();
                q.pop();
                for (int i = 0; i < (int)adj[v].size(); ++i) {
                    Edge& edge = adj[v][i];
                    if (edge.capacity > 0 && parent[edge.to] == -1) {
                        parent[edge.to] = v;
                        parent_edge[edge.to] = i;
                        q.push(edge.to);
                    }
                }
            }

            if (parent[t] == -1) break;

            int pushed = INT_MAX;
            int v = t;
            while (v != s) {
                int p = parent[v];
                int idx = parent_edge[v];
                pushed = std::min(pushed, adj[p][idx].capacity);
                v = p;
            }

            v = t;
            while (v != s) {
                int p = parent[v];
                int idx = parent_edge[v];
                adj[p][idx].capacity -= pushed;
                adj[v][adj[p][idx].rev].capacity += pushed;
                v = p;
            }

            total_flow += pushed;
        }

        return total_flow;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file> [source sink]\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    GraphType g;
    if (!in || !g.read(in)) {
        std::cerr << "Cannot read graph\n";
        return 1;
    }

    std::string source_name = "S";
    std::string sink_name = "T";
    if (argc >= 4) {
        source_name = argv[2];
        sink_name = argv[3];
    }

    SizeType source = 0, sink = 0;
    bool found_source = false, found_sink = false;

    for (SizeType i = 0; i < g.vertex_count(); ++i) {
        if (g.vertex_label(i) == source_name) {
            source = i;
            found_source = true;
        }
        if (g.vertex_label(i) == sink_name) {
            sink = i;
            found_sink = true;
        }
    }

    if (!found_source || !found_sink) {
        std::cerr << "Source or sink not found in graph\n";
        return 1;
    }

    int n = (int)g.vertex_count();
    FordFulkerson ff(n);

    for (SizeType u = 0; u < g.vertex_count(); ++u) {
        for (NeighborIt it = g.begin(u); it != g.end(u); ++it) {
            auto p = *it;
            if (!g.has_edge(p.first, u) || u < p.first) {
                ff.add_edge((int)u, (int)p.first, p.second);
            }
        }
    }

    std::cout << "Max flow: " << ff.max_flow((int)source, (int)sink) << "\n";
    return 0;
}