#include <iostream>
#include <sstream>
#include "graph.h"

int main()
{
    Graph<int, std::string> graph(2);
    graph.set_vertex_mark("v0", "start");
    graph.add_vertex("C", "end");
    graph.add_edge("v0", "C", 7);
    if (!graph.has_edge("v0", "C") || graph.edge_mark("v0", "C") != 7) return 1;
    graph.set_edge_mark("v0", "C", 4);
    if (graph.edge_mark("v0", "C") != 4) return 1;
    auto it = graph.neighbors("v0");
    if (!it.valid() || it.vertex_name() != "C" || it.edge_mark() != 4) return 1;
    graph.remove_edge("v0", "C");
    if (graph.has_edge("v0", "C")) return 1;
    graph.add_edge("v0", "C", 3);
    Vector<std::string> marks = graph.vertex_marks();
    if (marks.size() != graph.size() || marks.get(0) != "start") return 1;
    graph.remove_vertex("v0");
    if (graph.size() != 2 || graph.has_edge("v0", "C")) return 1;

    Graph<int, int> shifted(3);
    shifted.add_edge("v2", "v1", 8);
    shifted.remove_vertex("v0");
    if (!shifted.has_edge("v2", "v1") || shifted.edge_mark("v2", "v1") != 8) return 1;

    std::istringstream input("2 1\nA red\nB blue\nA B 9\n");
    Graph<int, std::string> loaded;
    if (!loaded.read(input) || !loaded.has_edge("A", "B") || loaded.vertex_mark("B") != "blue") return 1;

    Graph<int, int> grid(2, 3);
    if (grid.size() != 6 || grid.vertex_name(4) != "(1,1)") return 1;
    std::cout << "Graph tests passed\n";
}
