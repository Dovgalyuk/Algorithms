#undef NDEBUG
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "graph.h"

using TestGraph = Graph<std::string, int>;
using NeighborIt = TestGraph::NeighborIterator;

static void test_empty()
{
    TestGraph g;
    assert(g.vertexCount() == 0);
}

static void test_count_ctor()
{
    TestGraph g(5);
    assert(g.vertexCount() == 5);
    for (std::size_t i = 0; i < 5; ++i)
        assert(g.getVertexLabel(i) == std::string("v") + std::to_string(i));
    assert(!g.hasEdge("v0", "v1"));
}

static void test_grid_ctor()
{
    TestGraph g(3, 2);
    assert(g.vertexCount() == 6);

    const char* present[][2] = {
        {"v0", "v1"}, {"v2", "v3"}, {"v4", "v5"},
        {"v0", "v2"}, {"v1", "v3"}, {"v2", "v4"}, {"v3", "v5"}
    };
    for (const auto& p : present)
        assert(g.hasEdge(p[0], p[1]));

    const char* absent[][2] = {
        {"v0", "v3"}, {"v1", "v2"}, {"v1", "v0"}, {"v5", "v4"}
    };
    for (const auto& p : absent)
        assert(!g.hasEdge(p[0], p[1]));
}

static void test_vertices()
{
    TestGraph g;
    g.addVertex("alpha");
    g.addVertex("beta");
    assert(g.vertexCount() == 2);
    assert(g.getVertexLabel(0) == "alpha");
    assert(g.getVertexLabel(1) == "beta");
    g.setVertexLabel("beta", "gamma");
    assert(g.getVertexLabel(1) == "gamma");

    bool thrown = false;
    try {
        g.addVertex("alpha");
    }
    catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);
    assert(g.vertexCount() == 2);
    g.resize(4);
    assert(g.vertexCount() == 4);
    assert(g.getVertexLabel(0) == "alpha");
    g.resize(1);
    assert(g.vertexCount() == 1);
    assert(g.getVertexLabel(0) == "alpha");
}

static void test_edges()
{
    TestGraph g(4);
    g.addEdge("v0", "v1", 10);
    g.addEdge("v1", "v2", 20);
    g.addEdge("v2", "v3", 30);
    g.addEdge("v3", "v0", 40);

    const char* present[][2] = {
        {"v0", "v1"}, {"v3", "v0"}
    };
    for (const auto& p : present)
        assert(g.hasEdge(p[0], p[1]));

    const char* absent[][2] = {
        {"v1", "v0"}, {"v0", "v2"}
    };
    for (const auto& p : absent)
        assert(!g.hasEdge(p[0], p[1]));

    assert(g.getEdgeLabel("v0", "v1") == 10);
    assert(g.getEdgeLabel("v3", "v0") == 40);

    g.addEdge("v0", "v1", 99);
    assert(g.getEdgeLabel("v0", "v1") == 99);

    g.setEdgeLabel("v0", "v1", 123);
    assert(g.getEdgeLabel("v0", "v1") == 123);

    g.removeEdge("v1", "v2");
    assert(!g.hasEdge("v1", "v2"));

    bool thrown = false;
    try {
        g.getEdgeLabel("v1", "v2");
    }
    catch (const std::runtime_error&) {
        thrown = true;
    }
    assert(thrown);
}

static void test_remove_vertex()
{
    TestGraph g(4);
    g.setVertexLabel("v0", "a");
    g.setVertexLabel("v1", "b");
    g.setVertexLabel("v2", "c");
    g.setVertexLabel("v3", "d");
    g.addEdge("a", "b", 1);
    g.addEdge("b", "c", 2);
    g.addEdge("c", "d", 3);
    g.addEdge("d", "a", 4);

    g.removeVertex("b");
    assert(g.vertexCount() == 3);
    const char* kept[][2] = {
        {"c", "d"}, {"d", "a"}
    };
    for (const auto& p : kept)
        assert(g.hasEdge(p[0], p[1]));

    assert(g.getEdgeLabel("c", "d") == 3);
    assert(g.getEdgeLabel("d", "a") == 4);

    bool thrown = false;
    try {
        g.removeVertex("unknown");
    }
    catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);
}

static void test_neighbors()
{
    TestGraph g(5);
    g.addEdge("v0", "v1", 11);
    g.addEdge("v0", "v3", 33);
    g.addEdge("v0", "v4", 44);

    std::vector<std::string> seen;
    for (NeighborIt it = g.neighborsBegin("v0"); it != g.neighborsEnd("v0"); ++it)
        seen.push_back(*it);
    assert(seen.size() == 3);

    for (const char* name : { "v1", "v3", "v4" })
        assert(std::find(seen.begin(), seen.end(), name) != seen.end());

    std::size_t none = 0;
    for (NeighborIt it = g.neighborsBegin("v2"); it != g.neighborsEnd("v2"); ++it)
        ++none;
    assert(none == 0);

    g.removeVertex("v3");
    std::size_t after = 0;
    for (NeighborIt it = g.neighborsBegin("v0"); it != g.neighborsEnd("v0"); ++it)
        ++after;
    assert(after == 2);
}

static void test_labels_vector()
{
    TestGraph g(3);
    g.setVertexLabel("v0", "red");
    g.setVertexLabel("v1", "green");
    g.setVertexLabel("v2", "blue");

    std::vector<std::string> labels = g.getAllVertexLabels();
    const char* expected[] = { "red", "green", "blue" };
    assert(labels.size() == 3);
    for (std::size_t i = 0; i < 3; ++i)
        assert(labels[i] == expected[i]);

    bool thrown = false;
    try {
        g.getVertexLabel(5);
    }
    catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown);
}

static void test_read()
{
    std::istringstream input(
        "4\n"
        "north south east west\n"
        "4\n"
        "north south 12\n"
        "south east 34\n"
        "east west 56\n"
        "west north 78\n");
    TestGraph g;
    g.readFromStream(input);

    assert(g.vertexCount() == 4);
    const char* names[] = { "north", "south", "east", "west" };
    for (std::size_t i = 0; i < 4; ++i)
        assert(g.getVertexLabel(i) == names[i]);

    struct E { const char* from; const char* to; int w; };
    const E edges[] = {
        {"north", "south", 12},
        {"south", "east", 34},
        {"east", "west", 56},
        {"west", "north", 78}
    };
    for (const auto& e : edges) {
        assert(g.hasEdge(e.from, e.to));
        assert(g.getEdgeLabel(e.from, e.to) == e.w);
    }
    assert(!g.hasEdge("north", "east"));

    TestGraph g2(3);
    g2.addEdge("v0", "v1", 1);
    std::istringstream input2("2\nx y\n1\nx y 9\n");
    g2.readFromStream(input2);
    assert(g2.vertexCount() == 2);
    assert(g2.getEdgeLabel("x", "y") == 9);
}

static void test_read_invalid()
{
    {
        std::istringstream input("not_a_number\n");
        TestGraph g;
        bool thrown = false;
        try {
            g.readFromStream(input);
        }
        catch (const std::runtime_error&) {
            thrown = true;
        }
        assert(thrown);
    }
    {
        std::istringstream input(
            "2\n"
            "a b\n"
            "1\n"
            "a unknown 5\n");
        TestGraph g;
        bool thrown = false;
        try {
            g.readFromStream(input);
        }
        catch (const std::invalid_argument&) {
            thrown = true;
        }
        assert(thrown);
    }
}

static void test_copy_and_assign()
{
    TestGraph g(3);
    g.addEdge("v0", "v1", 7);
    g.addEdge("v1", "v2", 8);
    TestGraph copy = g;
    assert(copy.vertexCount() == 3);
    assert(copy.getEdgeLabel("v0", "v1") == 7);
    copy.removeEdge("v0", "v1");
    assert(!copy.hasEdge("v0", "v1"));
    assert(g.hasEdge("v0", "v1"));
    TestGraph assigned;
    assigned = g;
    assert(assigned.vertexCount() == 3);
    assert(assigned.getEdgeLabel("v1", "v2") == 8);
}

int main()
{
    std::cout << "Running test_empty...\n"; test_empty();
    std::cout << "Running test_count_ctor...\n"; test_count_ctor();
    std::cout << "Running test_grid_ctor...\n"; test_grid_ctor();
    std::cout << "Running test_vertices...\n"; test_vertices();
    std::cout << "Running test_edges...\n"; test_edges();
    std::cout << "Running test_remove_vertex...\n"; test_remove_vertex();
    std::cout << "Running test_neighbors...\n"; test_neighbors();
    std::cout << "Running test_labels_vector...\n"; test_labels_vector();
    std::cout << "Running test_read...\n"; test_read();
    std::cout << "Running test_read_invalid...\n"; test_read_invalid();
    std::cout << "Running test_copy_and_assign...\n"; test_copy_and_assign();

    std::cout << "All graph tests passed\n";
    return 0;
}