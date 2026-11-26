#include <iostream>
#include <sstream>
#include "graph.h"

using namespace std;

#define CHECK(cond)                                                               \
    do                                                                            \
    {                                                                             \
        if (!(cond))                                                              \
        {                                                                         \
            cerr << "Check failed: " << #cond << " at line " << __LINE__ << "\n"; \
            return 1;                                                             \
        }                                                                         \
    } while (0)

int main()
{
    Graph<string, int> graph;

    CHECK(graph.add_vertex("A", "DataA"));
    CHECK(graph.add_vertex("B", "DataB"));
    CHECK(graph.add_vertex("C", "DataC"));
    CHECK(!graph.add_vertex("A"));
    CHECK(graph.vertex_count() == 3);

    CHECK(graph.get_vertex_data("A") == "DataA");
    graph.set_vertex_data("A", "UpdatedA");
    CHECK(graph.get_vertex_data("A") == "UpdatedA");

    CHECK(graph.add_edge("A", "B", 10));
    CHECK(graph.add_edge("A", "C", 20));
    CHECK(graph.add_edge("B", "C", 30));
    CHECK(graph.has_edge("A", "B"));
    CHECK(graph.has_edge("A", "C"));
    CHECK(graph.has_edge("B", "C"));
    CHECK(!graph.has_edge("C", "A"));

    CHECK(graph.get_edge_data("A", "B") == 10);
    graph.set_edge_data("A", "B", 15);
    CHECK(graph.get_edge_data("A", "B") == 15);

    {
        int neighbor_count = 0;
        int sum_weights = 0;
        for (auto it = graph.get_neighbors("A"); it.has_next(); ++it)
        {
            neighbor_count++;
            sum_weights += it.data();
            CHECK(it.to() == "B" || it.to() == "C");
        }
        CHECK(neighbor_count == 2);
        CHECK(sum_weights == 15 + 20);
    }

    {
        auto all_data = graph.get_all_vertex_data();
        CHECK(all_data.size() == 3);
    }

    CHECK(graph.remove_edge("A", "B"));
    CHECK(!graph.has_edge("A", "B"));
    CHECK(!graph.remove_edge("A", "B"));

    CHECK(graph.add_edge("C", "B", 40));
    CHECK(graph.has_edge("C", "B"));
    CHECK(graph.remove_vertex("B"));
    CHECK(!graph.has_vertex("B"));
    CHECK(graph.vertex_count() == 2);
    CHECK(!graph.has_edge("C", "B"));

    {
        Graph<int, int> count_graph(4);
        CHECK(count_graph.vertex_count() == 4);
        CHECK(count_graph.has_vertex("0"));
        CHECK(count_graph.has_vertex("3"));
    }

    {
        Graph<int, int> grid_graph(2, 3, true, 1);
        CHECK(grid_graph.vertex_count() == 6);
        CHECK(grid_graph.has_vertex("(0,0)"));
        CHECK(grid_graph.has_vertex("(1,2)"));
        CHECK(grid_graph.has_edge("(0,0)", "(0,1)"));
        CHECK(grid_graph.has_edge("(0,0)", "(1,0)"));
        CHECK(!grid_graph.has_edge("(0,0)", "(1,2)"));
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

        CHECK(stream_graph.vertex_count() == 3);
        CHECK(stream_graph.has_vertex("Node1"));
        CHECK(stream_graph.has_vertex("Node2"));
        CHECK(stream_graph.has_vertex("Node3"));
        CHECK(stream_graph.has_edge("Node1", "Node2"));
        CHECK(stream_graph.get_edge_data("Node1", "Node2") == 50);
        CHECK(stream_graph.has_edge("Node2", "Node3"));
        CHECK(stream_graph.get_edge_data("Node2", "Node3") == 100);
    }

    cout << "All graph tests passed successfully!\n";
    return 0;
}
