#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "graph.h"
#include "vector.h"

struct EdgeInfo {
    size_t u;
    size_t v;
    int weight;
};

struct DSU {
    Vector<size_t> parent;
    Vector<size_t> rank;

    DSU(size_t n) {
        parent.resize(n);
        rank.resize(n);
        for (size_t i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    size_t find_set(size_t v) {
        if (v == parent[v])
            return v;
        size_t root = find_set(parent[v]);
        parent[v] = root;
        return root;
    }

    bool union_sets(size_t a, size_t b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
            return true;
        }
        return false;
    }
};

void sort_edges(Vector<EdgeInfo>& edges, size_t count) {
    if (count == 0) return;
    for (size_t i = 0; i < count - 1; ++i) {
        for (size_t j = 0; j < count - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                EdgeInfo temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }

    size_t n;
    int m;
    if (!(file >> n >> m)) {
        std::cout << "Error reading n and m\n";
        return 1;
    }

    Graph<std::string, int> graph(n);
    Vector<std::string> names;
    names.resize(n);

    for (size_t i = 0; i < n; ++i) {
        std::string name;
        file >> name;
        graph.set_vertex_label(i, name);
        names[i] = name;
    }

    const size_t NOT_FOUND = std::numeric_limits<size_t>::max();

    for (int i = 0; i < m; ++i) {
        std::string u_name, v_name;
        int w;
        file >> u_name >> v_name >> w;

        size_t u = NOT_FOUND;
        size_t v = NOT_FOUND;

        for (size_t k = 0; k < n; ++k) {
            if (names[k] == u_name) u = k;
            if (names[k] == v_name) v = k;
        }

        if (u != NOT_FOUND && v != NOT_FOUND) {
            graph.add_edge(u, v, w);
            graph.add_edge(v, u, w);
        }
    }

    Vector<EdgeInfo> all_edges;
    all_edges.resize(m * 2); 
    size_t edge_count = 0;

    for (size_t i = 0; i < graph.vertex_count(); ++i) {
        auto it = graph.get_neighbor_iterator(i);
        while (it.has_next()) {
            size_t neighbor = it.next();
            if (i < neighbor) {
                EdgeInfo e;
                e.u = i;
                e.v = neighbor;
                e.weight = graph.get_edge_label(i, neighbor);

                if (edge_count < all_edges.size()) {
                    all_edges[edge_count] = e;
                    edge_count++;
                }
            }
        }
    }

    sort_edges(all_edges, edge_count);

    DSU dsu(n);
    long long mst_weight = 0;
    Vector<EdgeInfo> mst_result;
    mst_result.resize(n - 1);
    size_t mst_count = 0;

    for (size_t i = 0; i < edge_count; ++i) {
        EdgeInfo e = all_edges[i];
        if (dsu.union_sets(e.u, e.v)) {
            mst_weight += e.weight;
            
            if (mst_count < mst_result.size()) {
                mst_result[mst_count] = e;
                mst_count++;
            }
        }
    }

    std::cout << "MST Weight: " << mst_weight << "\n";
    std::cout << "Edges:\n";
    for (size_t i = 0; i < mst_count; ++i) {
        EdgeInfo e = mst_result[i];
        std::cout << graph.get_vertex_label(e.u) << " - " 
                  << graph.get_vertex_label(e.v) << " (" 
                  << e.weight << ")\n";
    }

    return 0;
}
