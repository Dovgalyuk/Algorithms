#include <iostream>
#include <sstream>
#include <cassert>
#include "graph.h"

using namespace std;

int main()
{
    Graph<string, int> graph;

    assert(graph.add_vertex("A", "DataA"));
    assert(graph.add_vertex("B", "DataB"));
    assert(graph.add_vertex("C", "DataC"));
    assert(!graph.add_vertex("A"));
    assert(graph.vertex_count() == 3);

    assert(graph.get_vertex_data("A") == "DataA");
    graph.set_vertex_data("A", "UpdatedA");
    assert(graph.get_vertex_data("A") == "UpdatedA");

    assert(graph.add_edge("A", "B", 10));
    assert(graph.add_edge("A", "C", 20));
    assert(graph.add_edge("B", "C", 30));
    assert(graph.has_edge("A", "B"));
    assert(graph.has_edge("A", "C"));
    assert(graph.has_edge("B", "C"));
    assert(!graph.has_edge("C", "A"));

    assert(graph.get_edge_data("A", "B") == 10);
    graph.set_edge_data("A", "B", 15);
    assert(graph.get_edge_data("A", "B") == 15);

    {
        int neighbor_count = 0;
        int sum_weights = 0;
        for (auto it = graph.get_neighbors("A"); it.has_next(); ++it)
        {
            neighbor_count++;
            sum_weights += it.data();
            assert(it.to() == "B" || it.to() == "C");
        }
        assert(neighbor_count == 2);
        assert(sum_weights == 15 + 20);
    }

    {
        auto all_data = graph.get_all_vertex_data();
        assert(all_data.size() == 3);
    }

    assert(graph.remove_edge("A", "B"));
    assert(!graph.has_edge("A", "B"));
    assert(!graph.remove_edge("A", "B"));

    assert(graph.add_edge("C", "B", 40));
    assert(graph.has_edge("C", "B"));
    assert(graph.remove_vertex("B"));
    assert(!graph.has_vertex("B"));
    assert(graph.vertex_count() == 2);
    assert(!graph.has_edge("C", "B"));

    {
        Graph<int, int> grid_graph(2, 3, true, 1);
        assert(grid_graph.vertex_count() == 6);
        assert(grid_graph.has_vertex("(0,0)"));
        assert(grid_graph.has_vertex("(1,2)"));
        assert(grid_graph.has_edge("(0,0)", "(0,1)"));
        assert(grid_graph.has_edge("(0,0)", "(1,0)"));
        assert(!grid_graph.has_edge("(0,0)", "(1,2)"));
    }

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

        assert(stream_graph.vertex_count() == 3);
        assert(stream_graph.has_vertex("Node1"));
        assert(stream_graph.has_vertex("Node2"));
        assert(stream_graph.has_vertex("Node3"));
        assert(stream_graph.has_edge("Node1", "Node2"));
        assert(stream_graph.get_edge_data("Node1", "Node2") == 50);
        assert(stream_graph.has_edge("Node2", "Node3"));
        assert(stream_graph.get_edge_data("Node2", "Node3") == 100);
    }

    cout << "All graph tests passed successfully!\n";
    return 0;
}
