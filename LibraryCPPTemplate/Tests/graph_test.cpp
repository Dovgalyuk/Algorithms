#include "graph.h"
#include <iostream>
#include <sstream>
#include <string>

bool check(bool flag, const char *case_name)
{
    if (!flag)
        std::cerr << "FAILED: " << case_name << '\n';
    return flag;
}

int main()
{
    Graph<int, std::string> graph;
    if (!check(graph.add_vertex("A", "alpha"), "add vertex")) return 1;
    if (!check(graph.add_vertex("B", "beta"), "add second vertex")) return 1;
    if (!check(!graph.add_vertex("A", "duplicate"), "reject duplicate vertex")) return 1;
    if (!check(graph.add_edge("A", "B", 4), "add directed edge")) return 1;
    if (!check(graph.has_edge("A", "B") && !graph.has_edge("B", "A"), "directed adjacency")) return 1;

    int edge_label = 0;
    std::string vertex_label;
    if (!check(graph.get_edge_label("A", "B", edge_label) && edge_label == 4, "read edge label")) return 1;
    if (!check(graph.set_edge_label("A", "B", 7), "change edge label")) return 1;
    if (!check(graph.get_vertex_label("A", vertex_label) && vertex_label == "alpha", "read vertex label")) return 1;
    if (!check(graph.set_vertex_label("A", "start"), "change vertex label")) return 1;

    const Vector<std::string> labels = graph.vertex_labels();
    if (!check(labels.size() == 2 && labels.get(0) == "start" && labels.get(1) == "beta", "all vertex labels")) return 1;

    Graph<int, std::string>::NeighborIterator neighbor = graph.neighbors_begin("A");
    if (!check(neighbor.hasNext() && neighbor.next() == "B" && !neighbor.hasNext(), "neighbor iterator")) return 1;
    if (!check(graph.remove_edge("A", "B") && !graph.has_edge("A", "B"), "remove edge")) return 1;
    if (!check(graph.add_edge("B", "A", 3), "add incoming edge")) return 1;
    if (!check(graph.remove_vertex("A") && !graph.has_vertex("A") && !graph.has_edge("B", "A"), "remove vertex and incoming edge")) return 1;

    Graph<int, std::string> grid(2, 3);
    if (!check(grid.size() == 6 && grid.has_vertex("1_2"), "grid initialization")) return 1;
    grid.resize(2);
    if (!check(grid.size() == 2, "resize by vertex count")) return 1;

    std::istringstream valid_input("2 1 X x-ray Y yellow X Y 9");
    Graph<int, std::string> loaded;
    if (!check(loaded.read(valid_input) && loaded.has_edge("X", "Y"), "read graph")) return 1;
    std::istringstream invalid_input("2 1 X x-ray Z missing X Q 1");
    if (!check(!loaded.read(invalid_input) && loaded.has_edge("X", "Y"), "failed read keeps old graph")) return 1;

    std::cout << "All graph tests passed!\n";
    return 0;
}
