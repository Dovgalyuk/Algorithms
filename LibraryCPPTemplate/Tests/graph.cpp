#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "graph.h"

int main() {
    using MyGraph = Graph<std::string, int>;

    MyGraph* g = new MyGraph();

    size_t v0 = g->addVertex();
    size_t v1 = g->addVertex();
    size_t v2 = g->addVertex();

    g->setVertexLabel(v0, "A");
    g->setVertexLabel(v1, "B");
    g->setVertexLabel(v2, "C");

    if (g->getVertexLabel(v0) != "A") { std::cout << "Vertex label error\n"; return 1; }
    if (g->getVertexLabel(v1) != "B") { std::cout << "Vertex label error\n"; return 1; }

    g->addEdge(v0, v1, 10);
    g->addEdge(v1, v2, 20);
    g->addEdge(v2, v0, 30);

    if (!g->edgeExists(v0, v1)) { std::cout << "Edge should exist\n"; return 1; }
    if (!g->edgeExists(v2, v0)) { std::cout << "Edge should exist\n"; return 1; }

    if (g->getEdgeLabel(v0, v1) != 10) { std::cout << "Edge label error\n"; return 1; }
    if (g->getEdgeLabel(v2, v0) != 30) { std::cout << "Edge label error\n"; return 1; }

    g->removeEdge(v0, v1);
    if (g->edgeExists(v0, v1)) { std::cout << "Edge should be removed\n"; return 1; }

    std::vector<std::string> expected = {"C"};
    std::vector<std::string> found;

    std::cout << "Neighbors of vertex B: ";
    for (auto it = g->neighbors_begin(v1); it != g->neighbors_end(v1); ++it) {
        size_t neighbor = *it;

        if (!g->edgeExists(v1, neighbor)) {
            std::cout << "Iterator returned non-adjacent vertex!\n";
            return 1;
        }

        found.push_back(g->getVertexLabel(neighbor));

        int w = g->getEdgeLabel(v1, neighbor);
        std::cout << "  neighbor: " << g->getVertexLabel(neighbor)
                << " weight = " << w << "\n";
    }
    
    if (found.size() != expected.size()) {
        std::cout << "Invalid number of neighbors! Expected "
                << expected.size() << ", got " << found.size() << "\n";
        return 1;
    }

    std::sort(found.begin(), found.end());
    std::sort(expected.begin(), expected.end());
    if (found != expected) {
        std::cout << "Neighbors mismatch!\n";
        return 1;
    }

    g->removeVertex(v2);
    if (g->size() != 2) { std::cout << "Vertex removal failed\n"; return 1; }

    Vector<std::string> labels = g->getAllVertexLabels();
    std::cout << "All vertex labels: ";
    for (size_t i = 0; i < labels.size(); ++i)
        std::cout << labels.get(i) << " ";
    std::cout << std::endl;

    size_t v3 = g->addVertex();
    g->setVertexLabel(v3, "D");

    std::cout << "Vertex D added, label: " << g->getVertexLabel(v3) << "\n";

    delete g;
    return 0;
}