#include <bits/stdc++.h>
#include <fstream>
#include "graph.h"

Graph<int, int> prime(Graph<int, int> in_graph, int size) {
    Graph<int, int> out_graph(size);

    std::vector<int> minEdgeWeight(size, INT_MAX);
    std::vector<int> parent(size, -1);
    std::vector<bool> inMST(size, false);

    minEdgeWeight[0] = 0;

    for (int i = 0; i < size; ++i) {
        int u = -1;
        
        for (int v = 0; v < size; ++v) {
            if (!inMST[v] && (u == -1 || minEdgeWeight[v] < minEdgeWeight[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        if (parent[u] != -1) {
            out_graph.add_edge(parent[u], u, minEdgeWeight[u]);
            out_graph.add_edge(u, parent[u], minEdgeWeight[u]);
        }

        for (auto it = in_graph.begin(u); it != in_graph.end(u); ++it) {
            int v = (*it).to;
            int weight = (*it).mark;

            if (!inMST[v] && weight < minEdgeWeight[v]) {
                minEdgeWeight[v] = weight;
                parent[v] = u;
            }
        }
    }

    return out_graph;
}

void out(Graph<int, int> graph, std::ofstream& output) {
    std::vector<int> verts = graph.get_all_vertex_marks();
    for(size_t i = 0; i < verts.size(); i++) {
        output << i << std::endl;
        for (auto it(graph.begin(i)); it != graph.end(i); ++it) {
            output << (*it).to << " ";
        }
        output << "\n\n";
    }
}


void solve(std::ifstream& input, std::ofstream& output) {
    int n, k; input >> n >> k;

    Graph<int, int> graph(n);
    for(int i = 0; i < n; i++) {
        graph.set_vertex_mark(i, i);
    }
    for(int i = 0; i < k; i++) {
        int from, to, mark; 
        input >> from >> to >> mark;

        graph.add_edge(from, to, mark);
    }

    Graph<int, int> out_graph = prime(graph, n);

    out(out_graph, output);

}

int main(int argc, char **argv) {

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    size_t t;
    input >> t;

    while(t--) {
        solve(input, output);
    }

    return 0;
}
