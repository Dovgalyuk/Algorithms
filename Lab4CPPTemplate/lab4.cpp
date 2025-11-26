#include <iostream>
#include <string>
#include <fstream>
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
            parent.set(i, i);
            rank.set(i, 0);
        }
    }

    size_t find_set(size_t v) {
        if (v == parent.get(v))
            return v;
        size_t root = find_set(parent.get(v));
        parent.set(v, root);
        return root;
    }

    bool union_sets(size_t a, size_t b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank.get(a) < rank.get(b))
                std::swap(a, b);
            parent.set(b, a);
            if (rank.get(a) == rank.get(b))
                rank.set(a, rank.get(a) + 1);
            return true;
        }
        return false;
    }
};

// Функция сортировки пузырьком (так как std::sort требует итераторов, а у нас Vector)
// Для лабораторной сойдёт, но на больших данных лучше QuickSort
void sort_edges(Vector<EdgeInfo>& edges) {
    size_t n = edges.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (edges.get(j).weight > edges.get(j + 1).weight) {
                EdgeInfo temp = edges.get(j);
                edges.set(j, edges.get(j + 1));
                edges.set(j + 1, temp);
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
    file >> n >> m;

    Graph<std::string, int> graph(n);
    Vector<std::string> names; 
    names.resize(n);

    for (size_t i = 0; i < n; ++i) {
        std::string name;
        file >> name;
        graph.set_vertex_label(i, name);
        names.set(i, name);
    }

    Vector<EdgeInfo> all_edges;
    Vector<EdgeInfo> mst_edges;
    size_t edge_idx = 0; 
    all_edges.resize(m);

    for (int i = 0; i < m; ++i) {
        std::string u_name, v_name;
        int w;
        file >> u_name >> v_name >> w;

        size_t u = (size_t)-1;
        size_t v = (size_t)-1;
        for (size_t k = 0; k < n; ++k) {
            if (names.get(k) == u_name) u = k;
            if (names.get(k) == v_name) v = k;
        }

        if (u != -1 && v != -1) {
            graph.add_edge(u, v, w);
            
            EdgeInfo e;
            e.u = u; 
            e.v = v; 
            e.weight = w;
            all_edges.set(edge_idx++, e);
        }
    }

    // Алгоритм Крускала
    sort_edges(all_edges);
    
    DSU dsu(n);
    long long mst_weight = 0;
    
    // Т.к. мы заранее выделили память под m ребер, edge_idx хранит реальное кол-во
    for (size_t i = 0; i < edge_idx; ++i) {
        EdgeInfo e = all_edges.get(i);
        if (dsu.union_sets(e.u, e.v)) {
            mst_weight += e.weight;
            
            // Добавляем ребро в ответ
            // Т.к. mst_edges еще пустой, надо ресайзить по одному или сразу (n-1)
            size_t current_mst_size = mst_edges.size();
            mst_edges.resize(current_mst_size + 1);
            mst_edges.set(current_mst_size, e);
        }
    }

    std::cout << "MST Weight: " << mst_weight << "\n";
    std::cout << "Edges:\n";
    for (size_t i = 0; i < mst_edges.size(); ++i) {
        EdgeInfo e = mst_edges.get(i);
        std::cout << graph.get_vertex_label(e.u) << " - " 
                  << graph.get_vertex_label(e.v) << " : " 
                  << e.weight << "\n";
    }

    return 0;
}
