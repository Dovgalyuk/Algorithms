#include <iostream>
#include <sstream>
#include "graph.h"

using namespace std;

static int failures = 0;

static void check(bool condition, const char *message)
{
    if (!condition)
    {
        cout << "FAIL: " << message << "\n";
        failures++;
    }
}

int main()
{
    // --- Basic vertex operations ---
    Graph<string, int> graph;

    check(graph.add_vertex("A", "DataA"),   "add_vertex A");
    check(graph.add_vertex("B", "DataB"),   "add_vertex B");
    check(graph.add_vertex("C", "DataC"),   "add_vertex C");
    check(!graph.add_vertex("A"),           "add_vertex A duplicate");
    check(graph.vertex_count() == 3,        "vertex_count == 3");

    check(graph.get_vertex_data("A") == "DataA", "get_vertex_data A");
    graph.set_vertex_data("A", "UpdatedA");
    check(graph.get_vertex_data("A") == "UpdatedA", "set_vertex_data A");

    // --- Edge operations ---
    check(graph.add_edge("A", "B", 10), "add_edge A->B");
    check(graph.add_edge("A", "C", 20), "add_edge A->C");
    check(graph.add_edge("B", "C", 30), "add_edge B->C");
    check(graph.has_edge("A", "B"),     "has_edge A->B");
    check(graph.has_edge("A", "C"),     "has_edge A->C");
    check(graph.has_edge("B", "C"),     "has_edge B->C");
    check(!graph.has_edge("C", "A"),    "no edge C->A");

    check(graph.get_edge_data("A", "B") == 10, "get_edge_data A->B == 10");
    graph.set_edge_data("A", "B", 15);
    check(graph.get_edge_data("A", "B") == 15, "set_edge_data A->B = 15");

    // --- Neighbor iterator ---
    {
        int neighbor_count = 0;
        int sum_weights = 0;
        for (auto it = graph.get_neighbors("A"); it.has_next(); ++it)
        {
            neighbor_count++;
            sum_weights += it.data();
            check(it.to() == "B" || it.to() == "C", "neighbor of A is B or C");
        }
        check(neighbor_count == 2,      "neighbor_count A == 2");
        check(sum_weights == 15 + 20,   "sum of weights A == 35");
    }

    // --- get_all_vertex_data ---
    {
        auto all_data = graph.get_all_vertex_data();
        check(all_data.size() == 3, "get_all_vertex_data size == 3");
    }

    // --- Remove edge ---
    check(graph.remove_edge("A", "B"),   "remove_edge A->B");
    check(!graph.has_edge("A", "B"),     "edge A->B gone");
    check(!graph.remove_edge("A", "B"),  "remove_edge A->B again returns false");

    // --- Remove vertex ---
    check(graph.add_edge("C", "B", 40), "add_edge C->B");
    check(graph.has_edge("C", "B"),     "has_edge C->B");
    check(graph.remove_vertex("B"),     "remove_vertex B");
    check(!graph.has_vertex("B"),       "vertex B gone");
    check(graph.vertex_count() == 2,    "vertex_count == 2 after remove");
    check(!graph.has_edge("C", "B"),    "edge C->B gone after remove_vertex B");

    // --- Grid graph ---
    {
        Graph<int, int> grid_graph(2, 3, true, 1);
        check(grid_graph.vertex_count() == 6,                 "grid vertex_count == 6");
        check(grid_graph.has_vertex("(0,0)"),                 "grid has (0,0)");
        check(grid_graph.has_vertex("(1,2)"),                 "grid has (1,2)");
        check(grid_graph.has_edge("(0,0)", "(0,1)"),          "grid edge (0,0)->(0,1)");
        check(grid_graph.has_edge("(0,0)", "(1,0)"),          "grid edge (0,0)->(1,0)");
        check(!grid_graph.has_edge("(0,0)", "(1,2)"),         "no grid edge (0,0)->(1,2)");
    }

    // --- Read from stream ---
    {
        string input =
            "3\n"
            "Node1 Node2 Node3\n"
            "2\n"
            "Node1 Node2 50\n"
            "Node2 Node3 100\n";
        stringstream ss(input);
        Graph<int, int> stream_graph;
        stream_graph.read(ss);

        check(stream_graph.vertex_count() == 3,                      "stream vertex_count == 3");
        check(stream_graph.has_vertex("Node1"),                      "stream has Node1");
        check(stream_graph.has_vertex("Node2"),                      "stream has Node2");
        check(stream_graph.has_vertex("Node3"),                      "stream has Node3");
        check(stream_graph.has_edge("Node1", "Node2"),               "stream edge Node1->Node2");
        check(stream_graph.get_edge_data("Node1", "Node2") == 50,    "stream edge data 50");
        check(stream_graph.has_edge("Node2", "Node3"),               "stream edge Node2->Node3");
        check(stream_graph.get_edge_data("Node2", "Node3") == 100,   "stream edge data 100");
    }

    if (failures == 0)
        cout << "All graph tests passed successfully!\n";

    return failures;
}
