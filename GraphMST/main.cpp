#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

struct Edge { size_t from; size_t to; int weight; };

class DisjointSet
{
public:
    explicit DisjointSet(size_t size) : parent(size), rank(size, 0)
    { for (size_t i = 0; i < size; i++) parent[i] = i; }

    size_t find(size_t x)
    {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(size_t a, size_t b)
    {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
};

int main(int argc, char *argv[])
{
    std::ifstream file;
    std::istream *input = &std::cin;
    if (argc > 1) { file.open(argv[1]); input = &file; }

    Graph<int, std::string> graph;
    if (!graph.read(*input)) { std::cout << "IMPOSSIBLE\n"; return 0; }

    std::vector<Edge> edges;
    for (size_t i = 0; i < graph.size(); i++) {
        std::string from = graph.vertex_name(i);
        auto it = graph.neighbors(from);
        while (it.valid()) {
            size_t to = graph.vertex_index(it.vertex_name());
            edges.push_back({i, to, it.edge_mark()});
            it.next();
        }
    }
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) { return a.weight < b.weight; });

    DisjointSet sets(graph.size());
    std::vector<Edge> tree;
    int total = 0;
    for (const Edge &edge : edges) {
        if (sets.unite(edge.from, edge.to)) {
            tree.push_back(edge);
            total += edge.weight;
        }
    }

    if (graph.size() > 0 && tree.size() + 1 != graph.size()) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    std::cout << "Weight: " << total << '\n';
    for (const Edge &edge : tree)
        std::cout << graph.vertex_name(edge.from) << " - " << graph.vertex_name(edge.to) << ": " << edge.weight << '\n';
}
