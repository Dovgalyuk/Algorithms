#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include "graph.h"

using TestGraph = Graph<std::string, int>;
using NeighborIt = TestGraph::NeighborIterator;
using Pair = std::pair<std::size_t, int>;
using Labels = Vector<std::string>;

static void test_empty()
{
    TestGraph g;
    assert(g.vertex_count() == 0);
}

static void test_count_ctor()
{
    TestGraph g(4);
    assert(g.vertex_count() == 4);
}

static void test_grid_ctor()
{
    TestGraph g(2, 3);
    assert(g.vertex_count() == 6);

    assert(g.has_edge(0, 1));
    assert(g.has_edge(1, 2));
    assert(!g.has_edge(0, 2));
    assert(g.has_edge(3, 4));
    assert(g.has_edge(4, 5));
    assert(g.has_edge(0, 3));
    assert(g.has_edge(1, 4));
    assert(g.has_edge(2, 5));
    assert(!g.has_edge(0, 4));

    assert(!g.has_edge(0, 5));
    assert(!g.has_edge(2, 3));
}

static void test_vertices()
{
    TestGraph g;
    std::size_t a = g.add_vertex("alpha");
    std::size_t b = g.add_vertex("beta");
    assert(a == 0 && b == 1);
    assert(g.vertex_count() == 2);
    assert(g.vertex_label(0) == "alpha");
    assert(g.vertex_label(1) == "beta");
    g.resize(5);
    assert(g.vertex_count() == 5);
    assert(g.vertex_label(0) == "alpha");
}

static void test_edges()
{
    TestGraph g(3);
    g.add_edge(0, 1, 100);
    g.add_edge(1, 2, 200);
    g.add_edge(0, 2, 300);
    assert(g.has_edge(0, 1));
    assert(g.has_edge(1, 2));
    assert(!g.has_edge(1, 0));
    assert(g.edge_label(0, 1) == 100);
    assert(g.edge_label(1, 2) == 200);
    g.set_edge_label(0, 1, 150);
    assert(g.edge_label(0, 1) == 150);
    g.remove_edge(0, 1);
    assert(!g.has_edge(0, 1));
}

static void test_remove_vertex()
{
    TestGraph g(4);
    g.set_vertex_label(0, "w");
    g.set_vertex_label(1, "x");
    g.set_vertex_label(2, "y");
    g.set_vertex_label(3, "z");
    g.add_edge(0, 1, 10);
    g.add_edge(1, 2, 20);
    g.add_edge(2, 3, 30);
    g.remove_vertex(1);
    assert(g.vertex_count() == 3);
    assert(g.vertex_label(0) == "w");
    assert(g.vertex_label(1) == "y");
    assert(g.vertex_label(2) == "z");
    assert(!g.has_edge(0, 1));
    assert(g.has_edge(1, 2));
    assert(g.edge_label(1, 2) == 30);
}

static void test_neighbors()
{
    TestGraph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(0, 2, 2);
    g.add_edge(0, 3, 3);
    bool f1 = false, f2 = false, f3 = false;
    int count = 0;
    for (NeighborIt it = g.begin(0); it != g.end(0); ++it)
    {
        Pair p = *it;
        ++count;
        if (p.first == 1 && p.second == 1) f1 = true;
        if (p.first == 2 && p.second == 2) f2 = true;
        if (p.first == 3 && p.second == 3) f3 = true;
    }
    assert(count == 3);
    assert(f1 && f2 && f3);
}

static void test_labels_vector()
{
    TestGraph g(3);
    g.set_vertex_label(0, "one");
    g.set_vertex_label(1, "two");
    g.set_vertex_label(2, "three");
    Labels labels = g.vertex_labels();
    assert(labels.size() == 3);
    assert(labels.get(0) == "one");
    assert(labels.get(1) == "two");
    assert(labels.get(2) == "three");
}

static void test_read()
{
    std::istringstream input(
        "3\n"
        "north south east\n"
        "2\n"
        "north south 11\n"
        "south east 22\n");
    TestGraph g;
    assert(g.read(input));
    assert(g.vertex_count() == 3);
    assert(g.vertex_label(0) == "north");
    assert(g.vertex_label(1) == "south");
    assert(g.vertex_label(2) == "east");
    assert(g.edge_label(0, 1) == 11);
    assert(g.edge_label(1, 2) == 22);
}

static void test_read_invalid()
{
    std::istringstream bad("2\nA B\n1\nA C 5\n");
    TestGraph g;
    assert(!g.read(bad));
}

int main()
{
    test_empty();
    test_count_ctor();
    test_grid_ctor();
    test_vertices();
    test_edges();
    test_remove_vertex();
    test_neighbors();
    test_labels_vector();
    test_read();
    test_read_invalid();
    std::cout << "All graph tests passed\n";
    return 0;
}