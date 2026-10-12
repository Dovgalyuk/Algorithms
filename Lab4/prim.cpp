#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "graph.h"

typedef Graph<int, std::string> WeightedGraph;

struct EdgeCandidate
{
    int weight;
    size_t from;
    size_t to;
};

struct GreaterWeight
{
    bool operator()(const EdgeCandidate &left, const EdgeCandidate &right) const
    {
        return left.weight > right.weight;
    }
};

typedef std::vector<EdgeCandidate> EdgeList;
typedef std::priority_queue<EdgeCandidate, EdgeList, GreaterWeight> EdgeQueue;

static void add_edges_from(
    const WeightedGraph &graph,
    size_t from,
    const std::vector<bool> &visited,
    EdgeQueue &edges)
{
    for (size_t to = 0; to < graph.size(); ++to)
    {
        if (visited[to])
            continue;
        if (graph.has_edge(from, to))
            edges.push({graph.edge_label(from, to), from, to});
        else if (graph.has_edge(to, from))
            edges.push({graph.edge_label(to, from), from, to});
    }
}

static bool minimum_spanning_tree(
    const WeightedGraph &graph,
    std::vector<EdgeCandidate> &tree)
{
    if (graph.size() == 0)
        return false;

    std::vector<bool> visited(graph.size(), false);
    EdgeQueue edges;
    visited[0] = true;
    size_t visited_count = 1;
    add_edges_from(graph, 0, visited, edges);

    while (visited_count < graph.size())
    {
        bool found_edge = false;
        while (!edges.empty())
        {
            EdgeCandidate edge = edges.top();
            edges.pop();
            if (!visited[edge.to])
            {
                visited[edge.to] = true;
                ++visited_count;
                tree.push_back(edge);
                add_edges_from(graph, edge.to, visited, edges);
                found_edge = true;
                break;
            }
        }
        if (!found_edge)
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Prim <input-file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    WeightedGraph graph;
    if (!input || !graph.read(input))
    {
        std::cerr << "Invalid graph input\n";
        return 1;
    }

    std::vector<EdgeCandidate> tree;
    if (!minimum_spanning_tree(graph, tree))
    {
        std::cout << "No spanning tree\n";
        return 0;
    }
    for (size_t i = 0; i < tree.size(); ++i)
    {
        std::cout << graph.vertex_label(tree[i].from) << " -- "
                  << graph.vertex_label(tree[i].to) << " : " << tree[i].weight << "\n";
    }
    long long total_weight = 0;
    for (size_t i = 0; i < tree.size(); ++i)
        total_weight += tree[i].weight;
    std::cout << "Minimum spanning tree weight: " << total_weight << "\n";
}
