#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "graph.h"

struct WeightedEdge
{
    size_t u;
    size_t v;
    int weight;

    bool operator<(const WeightedEdge &other) const
    {
        if (weight != other.weight)
        {
            return weight < other.weight;
        }
        if (u != other.u)
        {
            return u < other.u;
        }
        return v < other.v;
    }
};

struct DSU
{
    std::vector<size_t> parent;
    std::vector<size_t> rank;

    explicit DSU(size_t n)
        : parent(n), rank(n, 0)
    {
        for (size_t i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    size_t find(size_t x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(size_t a, size_t b)
    {
        size_t root_a = find(a);
        size_t root_b = find(b);
        if (root_a == root_b)
        {
            return false;
        }
        if (rank[root_a] < rank[root_b])
        {
            parent[root_a] = root_b;
        }
        else if (rank[root_a] > rank[root_b])
        {
            parent[root_b] = root_a;
        }
        else
        {
            parent[root_b] = root_a;
            ++rank[root_a];
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    std::istream *in = &std::cin;
    std::ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        if (!file.is_open())
        {
            return 1;
        }
        in = &file;
    }

    Graph<std::string, int> graph;
    graph.read(*in);

    size_t n = graph.vertex_count();
    if (n == 0)
    {
        return 0;
    }

    std::vector<WeightedEdge> edges;
    for (size_t u = 0; u < n; ++u)
    {
        for (auto it = graph.neighbors_begin(u); it != graph.neighbors_end(u); ++it)
        {
            edges.push_back({u, *it, it.edge_label()});
        }
    }

    std::sort(edges.begin(), edges.end());

    DSU dsu(n);
    std::vector<WeightedEdge> mst;
    long long total_weight = 0;

    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (dsu.unite(edges[i].u, edges[i].v))
        {
            mst.push_back(edges[i]);
            total_weight += edges[i].weight;
        }
    }

    if (mst.size() + 1 < n)
    {
        std::cout << "No spanning tree\n";
    }
    else
    {
        for (size_t i = 0; i < mst.size(); ++i)
        {
            std::cout << graph.get_vertex_label(mst[i].u) << " "
                      << graph.get_vertex_label(mst[i].v) << " "
                      << mst[i].weight << "\n";
        }
        std::cout << "Total: " << total_weight << "\n";
    }

    return 0;
}