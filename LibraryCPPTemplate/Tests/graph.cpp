#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "graph.h"

using namespace std;

typedef Graph<int, string> TestGraph;
typedef Vector<string> StringVector;

void check(bool condition, const char *message)
{
    if (!condition)
        throw runtime_error(message);
}

void test_graph()
{
    TestGraph graph(3);
    graph.set_vertex(0, "source");
    graph.set_vertex(1, "middle");
    graph.set_vertex(2, "sink");
    check(graph.size() == 3 && graph.get_vertex(1) == "middle", "Vertex labels");
    graph.set_vertex(1, "A");
    check(graph.find_vertex("A") == 1 && graph.find_vertex("missing") == graph.size(), "Find vertex");

    check(graph.add_edge(0, 1, 5), "Add edge");
    check(!graph.add_edge(0, 1, 99) && graph.get_edge(0, 1) == 5, "Reject duplicate edge");
    check(!graph.has_edge(1, 0), "Directed edge");
    graph.add_edge(0, 2, 7);
    graph.add_edge(1, 2, 3);
    graph.add_edge(2, 0, 4);
    graph.add_edge(1, 1, 2);
    graph.set_edge(0, 1, 8);
    check(graph.get_edge(0, 1) == 8, "Change edge label");

    const TestGraph &constant = graph;
    auto edge = constant.neighbors(0);
    check(edge.valid() && edge.vertex() == 1 && edge.label() == 8, "First neighbor");
    edge.next();
    check(edge.valid() && edge.vertex() == 2 && edge.label() == 7, "Second neighbor");
    edge.next();
    check(!edge.valid(), "Iterator end");
    edge.next();
    check(!edge.valid(), "Advance empty iterator");

    StringVector labels = graph.get_vertices();
    check(labels.size() == 3 && labels[0] == "source" && labels[2] == "sink", "Labels vector");
    labels[0] = "changed";
    check(graph.get_vertex(0) == "source", "Labels independent copy");

    TestGraph copy(graph);
    copy.set_edge(0, 1, 1);
    copy.set_vertex(0, "other");
    copy.remove_edge(2, 0);
    check(graph.get_edge(0, 1) == 8 && graph.has_edge(2, 0), "Graph independent edges");
    check(graph.get_vertex(0) == "source", "Graph independent labels");
    copy = graph;
    copy = copy;
    check(copy.get_edge(0, 1) == 8, "Graph assignment");

    check(graph.remove_edge(0, 1) && !graph.remove_edge(0, 1), "Remove first edge");
    graph.add_edge(0, 1, 8);
    check(graph.remove_edge(0, 1) && !graph.has_edge(0, 1), "Remove last edge");
    check(graph.remove_edge(1, 1) && !graph.has_edge(1, 1), "Remove self loop");
    graph.remove_vertex(1);
    check(graph.size() == 2 && graph.get_vertex(1) == "sink", "Remove middle vertex");
    check(graph.get_edge(0, 1) == 7 && graph.get_edge(1, 0) == 4, "Renumber edges");
    edge = graph.neighbors(0);
    check(edge.valid() && edge.vertex() == 1, "Remaining neighbor");
    edge.next();
    check(!edge.valid(), "No removed incoming edges");
    graph.remove_vertex(0);
    check(graph.size() == 1 && !graph.neighbors(0).valid(), "Remove first vertex");
    graph.remove_vertex(0);
    check(graph.size() == 0, "Remove last vertex");
    check(graph.add_vertex("again") == 0 && graph.get_vertex(0) == "again", "Graph reuse");
    graph.add_edge(0, 0, 1);
    graph.remove_vertex(0);
    check(graph.size() == 0, "Remove vertex with self loop");

    bool rejected = false;
    try { graph.add_edge(0, 0, 1); }
    catch (const out_of_range &) { rejected = true; }
    check(rejected, "Invalid vertex rejected");
    rejected = false;
    try { copy.get_edge(2, 1); }
    catch (const out_of_range &) { rejected = true; }
    check(rejected, "Missing edge rejected");

    typedef Graph<string, int> OtherGraph;
    OtherGraph other(2);
    other.set_vertex(0, 10);
    other.set_vertex(1, 20);
    other.add_edge(0, 1, "road");
    check(other.get_vertex(1) == 20 && other.get_edge(0, 1) == "road", "Other label types");
}

void test_input()
{
    TestGraph graph;
    istringstream input("3 2 source A sink source A 8 A sink 5");
    graph.read(input);
    check(graph.size() == 3 && graph.get_edge(0, 1) == 8, "Read graph");
    check(graph.get_vertex(2) == "sink" && graph.get_edge(1, 2) == 5, "Read names");

    const char *invalid[] = {
        "-1 0", "2 -1", "2 0 A A", "2 1 A B A C 1", "2 1 A B A B",
        "2 2 A B A B 1 A B 2", "2 0 A", ""
    };
    for (const char *text : invalid)
    {
        bool rejected = false;
        istringstream bad(text);
        try { graph.read(bad); }
        catch (const invalid_argument &) { rejected = true; }
        check(rejected, "Invalid graph input rejected");
        check(graph.size() == 3 && graph.get_edge(0, 1) == 8, "Failed read preserves graph");
    }

    istringstream empty("0 0");
    graph.read(empty);
    check(graph.size() == 0, "Read empty graph");
}

int main()
{
    try
    {
        test_graph();
        test_input();
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }
    cout << "Graph tests passed\n";
    return 0;
}
