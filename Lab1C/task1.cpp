#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include "graph.h"

using namespace std;

struct FlowEdge
{
    int capacity = 0;
    int flow = 0;
};

int dfs(Graph<int, FlowEdge> &graph, const string &u, const string &sink,
        int pushed, unordered_map<string, string> &parent,
        unordered_set<string> &visited)
{
    if (u == sink)
        return pushed;

    visited.insert(u);

    for (auto it = graph.get_neighbors(u); it.has_next(); ++it)
    {
        const string &v = it.to();
        int residual = it.data().capacity - it.data().flow;

        if (residual > 0 && visited.find(v) == visited.end())
        {
            parent[v] = u;
            int result = dfs(graph, v, sink, min(pushed, residual), parent, visited);
            if (result > 0)
                return result;
        }
    }

    return 0;
}

int ford_fulkerson(Graph<int, FlowEdge> &graph, const string &source, const string &sink)
{
    if (!graph.has_vertex(source) || !graph.has_vertex(sink))
        return 0;

    int max_flow = 0;
    unordered_map<string, string> parent;
    unordered_set<string> visited;
    int bottleneck;

    do
    {
        parent.clear();
        visited.clear();
        bottleneck = dfs(graph, source, sink, INT_MAX, parent, visited);
        max_flow += bottleneck;
        string cur = sink;
        while (bottleneck > 0 && cur != source)
        {
            string p = parent[cur];
            graph.get_edge_data(p, cur).flow += bottleneck;
            graph.get_edge_data(cur, p).flow -= bottleneck;
            cur = p;
        }
    }
    while (bottleneck > 0);

    return max_flow;
}

int main(int argc, char **argv)
{
    istream *in = &cin;
    ifstream file;
    if (argc > 1)
    {
        file.open(argv[1]);
        if (!file.is_open())
        {
            cerr << "Error opening input file: " << argv[1] << "\n";
            return 1;
        }
        in = &file;
    }

    string source, sink;
    if (!(*in >> source >> sink))
    {
        return 1;
    }

    Graph<int, FlowEdge> graph;
    graph.add_vertex(source);
    graph.add_vertex(sink);

    size_t edge_count = 0;
    if (*in >> edge_count)
    {
        for (size_t i = 0; i < edge_count; ++i)
        {
            string from, to;
            int cap;
            if (*in >> from >> to >> cap)
            {
                graph.add_vertex(from);
                graph.add_vertex(to);
                if (graph.has_edge(from, to))
                {
                    graph.get_edge_data(from, to).capacity += cap;
                }
                else
                {
                    graph.add_edge(from, to, FlowEdge{cap, 0});
                }

                if (!graph.has_edge(to, from))
                {
                    graph.add_edge(to, from, FlowEdge{0, 0});
                }
            }
        }
    }

    cout << "Max flow: " << ford_fulkerson(graph, source, sink) << "\n";

    return 0;
}
