#include "graph.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void check(bool condition, const char* message)
{
    if (!condition)
        throw std::runtime_error(message);
}

int main()
{
    Graph<int, std::string> graph(2);
    check(graph.vertexNames().get(1) == "1", "Initial names");

    graph.addVertex("C", "third");
    graph.addEdge("0", "1", 0);
    graph.addEdge("0", "C", 10);
    graph.addEdge("1", "C", 3);
    check(graph.hasEdge("0", "1") && !graph.hasEdge("1", "0"), "Directed edge");
    check(graph.edgeLabel("0", "1") == 0, "Zero label");

    std::string neighbors;
    for (const auto& name : graph.neighbors("0"))
        neighbors += name;
    check(neighbors == "1C", "Outgoing neighbors");

    graph.setVertexLabel("0", "first");
    graph.setEdgeLabel("0", "C", 7);
    graph.removeVertex("1");
    check(graph.vertexNames().get(1) == "C", "Vertex removal");
    const auto labels = graph.vertexLabels();
    check(labels.size() == 2 && labels.get(0) == "first" && labels.get(1) == "third",
          "Vertex labels in order");
    check(graph.vertexLabel("C") == "third", "Single vertex label");
    check(graph.edgeLabel("0", "C") == 7, "Edge preserved during vertex removal");
    graph.removeEdge("0", "C");
    check(!graph.hasEdge("0", "C"), "Edge removal");
    auto range = graph.neighbors("0");
    check(!(range.begin() != range.end()), "Empty neighbor range");

    std::istringstream valid("2 1 A red B blue A B -5");
    check(static_cast<bool>(valid >> graph), "Read graph");
    check(graph.edgeLabel("A", "B") == -5, "Read weight");
    for (const char* input : {"2 0 A red A blue", "1 1 X red X Y 5", "1 1 X red X X", "-1 0"})
    {
        std::istringstream invalid(input);
        check(!(invalid >> graph), "Reject invalid graph");
        check(graph.edgeLabel("A", "B") == -5, "Preserve graph on input error");
    }

    Graph<std::string, bool> second;
    second.addVertex("X", true);
    second.addEdge("X", "X", "loop");
    check(second.edgeLabel("X", "X") == "loop" && second.vertexLabels().get(0),
          "Independent label types");
    std::cout << "Graph tests passed\n";
}
