#include <iostream>
#include <sstream>
#include <string>
#include "graph.h"

typedef Graph<int, std::string> TestGraph;

int main()
{
    TestGraph grid(2, 2);
    if (grid.size() != 4)
        return 1;

    TestGraph graph(3);
    graph.set_vertex_label(0, "A");
    graph.set_vertex_label(1, "B");
    graph.set_vertex_label(2, "C");
    graph.add_edge(0, 1, 7);
    graph.add_edge(0, 2, 4);
    graph.add_edge(1, 0, 7);
    if (!graph.has_edge(0, 1) || graph.edge_label(0, 1) != 7
        || graph.vertex_label(1) != "B")
        return 1;
    graph.set_edge_label(0, 1, 6);
    if (graph.edge_label(0, 1) != 6)
        return 1;

    size_t neighbors = 0;
    for (TestGraph::NeighborIterator it = graph.begin(0);
         it != graph.end(0); ++it)
    {
        ++neighbors;
    }
    if (neighbors != 2)
        return 1;

    graph.remove_edge(0, 1);
    if (graph.has_edge(0, 1))
        return 1;
    graph.remove_vertex(1);
    if (graph.size() != 2 || graph.vertex_label(1) != "C" || !graph.has_edge(0, 1))
        return 1;
    graph.resize(3);
    if (graph.size() != 3 || graph.vertex_label(0) != "A")
        return 1;
    size_t added_vertex = graph.add_vertex();
    graph.set_vertex_label(added_vertex, "D");
    if (graph.vertex_label(added_vertex) != "D")
        return 1;

    std::istringstream input("3 2 A B C A B 5 B C 8");
    TestGraph parsed;
    if (!parsed.read(input) || parsed.size() != 3 || parsed.edge_label(1, 2) != 8
        || parsed.vertex_labels().get(2) != "C")
        return 1;

    std::istringstream invalid_input("2 1 A B A Z 3");
    if (parsed.read(invalid_input))
        return 1;

    std::cout << "Graph tests passed\n";
}
