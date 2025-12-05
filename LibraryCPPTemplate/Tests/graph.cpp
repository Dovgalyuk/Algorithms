#include "graph.h"


#ifdef TEST_GRAPH_STANDALONE
int main() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph(3);

    graph.setVertexLabel(0, "X");
    graph.setVertexLabel(1, "Y");
    graph.setVertexLabel(2, "Z");

    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    std::cout << "Has edge X->Y: " << graph.hasEdge(0, 1) << std::endl;
    std::cout << "Edge weight X->Y: " << graph.getEdgeLabel(0, 1) << std::endl;

    std::cout << "Neighbors of X: ";
    auto neighbors = graph.getNeighbors(0);
    while (neighbors.hasNext()) {
        int neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
    }
    std::cout << std::endl;

    auto paths = graph.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths.size() << " shortest path(s) from X to Z" << std::endl;

    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[i][j]);
            if (j < paths[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "TestGraphCPPTemplate completed successfully!" << std::endl;
    return 0;
}
#endif