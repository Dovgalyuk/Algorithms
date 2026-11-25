#include <iostream>
#include <sstream>
#include <string>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph graph(3);
    if (graph.vertex_count() != 3)
    {
        std::cout << "Invalid vertex count\n";
        return 1;
    }

    graph.set_vertex_label(0, "A");
    graph.set_vertex_label(1, "B");
    graph.set_vertex_label(2, "C");

    if (graph.get_vertex_label(0) != "A" || graph.get_vertex_label(1) != "B" || graph.get_vertex_label(2) != "C")
    {
        std::cout << "Invalid vertex label\n";
        return 1;
    }

    Vector<std::string> labels = graph.get_vertex_labels();
    if (labels.size() != 3 || labels.get(0) != "A" || labels.get(1) != "B" || labels.get(2) != "C")
    {
        std::cout << "Invalid vertex labels vector\n";
        return 1;
    }

    size_t idx = graph.add_vertex("D");
    if (idx != 3 || graph.vertex_count() != 4 || graph.get_vertex_label(3) != "D")
    {
        std::cout << "Invalid add_vertex\n";
        return 1;
    }

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 20);
    graph.add_edge(1, 3, 30);
    graph.add_edge(2, 3, 40);

    if (!graph.has_edge(0, 1) || graph.has_edge(1, 0))
    {
        std::cout << "Invalid directed edge check\n";
        return 1;
    }

    if (graph.get_edge_label(0, 1) != 10 || graph.get_edge_label(0, 2) != 20)
    {
        std::cout << "Invalid edge label\n";
        return 1;
    }

    graph.set_edge_label(0, 1, 15);
    if (graph.get_edge_label(0, 1) != 15)
    {
        std::cout << "Invalid set_edge_label\n";
        return 1;
    }

    size_t neighbor_sum = 0;
    int weight_sum = 0;
    for (auto it = graph.neighbors_begin(0); it != graph.neighbors_end(0); ++it)
    {
        neighbor_sum += *it;
        weight_sum += it.edge_label();
    }
    if (neighbor_sum != 3 || weight_sum != 35)
    {
        std::cout << "Invalid neighbor iterator\n";
        return 1;
    }

    graph.remove_edge(0, 1);
    if (graph.has_edge(0, 1))
    {
        std::cout << "Invalid remove_edge\n";
        return 1;
    }

    auto it = graph.neighbors_begin(0);
    if (!it.has_next() || it.vertex() != 2 || it.edge_label() != 20)
    {
        std::cout << "Invalid neighbor iterator after remove_edge\n";
        return 1;
    }
    ++it;
    if (it.has_next())
    {
        std::cout << "Expected end of neighbors\n";
        return 1;
    }

    graph.remove_vertex(1);
    if (graph.vertex_count() != 3 || graph.get_vertex_label(0) != "A" || graph.get_vertex_label(1) != "C" || graph.get_vertex_label(2) != "D")
    {
        std::cout << "Invalid remove_vertex labels\n";
        return 1;
    }

    if (!graph.has_edge(0, 1) || graph.get_edge_label(0, 1) != 20 || !graph.has_edge(1, 2) || graph.get_edge_label(1, 2) != 40)
    {
        std::cout << "Invalid remove_vertex edges\n";
        return 1;
    }

    MyGraph copy(graph);
    MyGraph assigned;
    assigned = copy;
    if (assigned.vertex_count() != 3 || !assigned.has_edge(1, 2) || assigned.get_edge_label(1, 2) != 40)
    {
        std::cout << "Invalid copy or assignment\n";
        return 1;
    }

    std::istringstream iss("3 2\nX Y Z\nX Y 5\nY Z 8\n");
    MyGraph stream_graph;
    stream_graph.read(iss);
    if (stream_graph.vertex_count() != 3 || !stream_graph.has_edge(0, 1) || stream_graph.get_edge_label(0, 1) != 5 || !stream_graph.has_edge(1, 2) || stream_graph.get_edge_label(1, 2) != 8 || stream_graph.has_edge(2, 0))
    {
        std::cout << "Invalid read from stream\n";
        return 1;
    }

    std::cout << "All Graph tests passed\n";
    return 0;
}