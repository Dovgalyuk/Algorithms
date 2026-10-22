#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "graph.h"

using GraphType = Graph<std::string, int>;
using SizeType = std::size_t;
using AdjacentPair = std::pair<SizeType, int>;
using NeighborIt = GraphType::NeighborIterator;
using EdgeList = std::vector<struct WeightedEdge>;

struct WeightedEdge
{
    SizeType from;
    SizeType to;
    int weight;
};

class DisjointSet
{
public:
    explicit DisjointSet(SizeType n) : parent_(n), rank_(n, 0)
    {
        for (SizeType i = 0; i < n; ++i) parent_[i] = i;
    }

    SizeType find(SizeType x)
    {
        while (parent_[x] != x)
        {
            parent_[x] = parent_[parent_[x]];
            x = parent_[x];
        }
        return x;
    }

    bool unite(SizeType a, SizeType b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) std::swap(a, b);
        parent_[b] = a;
        if (rank_[a] == rank_[b]) ++rank_[a];
        return true;
    }

private:
    std::vector<SizeType> parent_;
    std::vector<SizeType> rank_;
};

static bool same_orientation(SizeType u, SizeType v, const GraphType &g)
{
    return u < v || !g.has_edge(v, u);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: kruskal_mst <input-file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    GraphType g;
    if (!in || !g.read(in))
    {
        std::cerr << "Cannot read graph\n";
        return 1;
    }

    SizeType n = g.vertex_count();
    if (n == 0)
    {
        std::cout << "Minimum spanning tree weight: 0\n";
        return 0;
    }

    EdgeList edges;
    for (SizeType u = 0; u < n; ++u)
        for (NeighborIt it = g.begin(u); it != g.end(u); ++it)
        {
            AdjacentPair p = *it;
            if (same_orientation(u, p.first, g))
                edges.push_back(WeightedEdge{u, p.first, p.second});
        }

    std::sort(edges.begin(), edges.end(),
              [](const WeightedEdge &a, const WeightedEdge &b) {
                  return a.weight < b.weight;
              });

    DisjointSet dsu(n);
    EdgeList tree;
    long long total = 0;

    for (SizeType i = 0; i < edges.size(); ++i)
        if (dsu.unite(edges[i].from, edges[i].to))
        {
            tree.push_back(edges[i]);
            total += edges[i].weight;
        }

    if (tree.size() + 1 != n)
    {
        std::cout << "No spanning tree\n";
        return 0;
    }

    for (SizeType i = 0; i < tree.size(); ++i)
        std::cout << g.vertex_label(tree[i].from) << " -- "
                  << g.vertex_label(tree[i].to) << " : " << tree[i].weight << "\n";
    std::cout << "Minimum spanning tree weight: " << total << "\n";
    return 0;
}