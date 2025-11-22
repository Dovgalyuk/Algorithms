#include <iostream>
#include <string>

#include "graph.h"

using TestGraph = Graph<std::string, int>;

int main()
{
    TestGraph graph;

    auto start = graph.add_vertex("start");
    auto mid = graph.add_vertex("mid");
    auto goal = graph.add_vertex("goal");

    if (graph.get_vertex_label(start) != "start" || graph.vertex_labels().size() != 3)
    {
        std::cout << "vertex create failed\n";
        return 1;
    }

    graph.add_edge(start, mid, 1);
    graph.add_edge(mid, goal, 2);
    graph.add_edge(start, goal, 5);

    if (!graph.has_edge(start, mid) || graph.get_edge_label(mid, goal) != 2)
    {
        std::cout << "edge create failed\n";
        return 1;
    }

    graph.set_edge_label(start, goal, 3);
    if (graph.get_edge_label(start, goal) != 3)
    {
        std::cout << "edge relabel failed\n";
        return 1;
    }

    graph.set_vertex_label(mid, "middle");
    if (graph.get_vertex_label(mid) != "middle")
    {
        std::cout << "vertex relabel failed\n";
        return 1;
    }

    auto it = graph.neighbors(start);
    int edge_count = 0;
    while (it.valid())
    {
        ++edge_count;
        it.next();
    }
    if (edge_count != 2)
    {
        std::cout << "neighbor iteration failed\n";
        return 1;
    }

    graph.remove_edge(start, mid);
    if (graph.has_edge(start, mid))
    {
        std::cout << "edge removal failed\n";
        return 1;
    }

    graph.remove_vertex(mid);
    auto labels = graph.vertex_labels();
    if (labels.size() != 2)
    {
        std::cout << "vertex removal failed\n";
        return 1;
    }
    TestGraph::VertexIndex goal_index = labels.size();
    for (TestGraph::VertexIndex i = 0; i < labels.size(); ++i)
    {
        if (labels[i] == "goal")
        {
            goal_index = i;
            break;
        }
    }
    if (goal_index >= labels.size() || !graph.has_edge(start, goal_index))
    {
        std::cout << "edge adjustment failed\n";
        return 1;
    }

    std::cout << "Graph tests passed\n";
    return 0;
}
