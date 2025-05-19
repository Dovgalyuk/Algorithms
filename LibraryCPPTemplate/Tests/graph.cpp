#include "graph.h"

#include <iostream>
#include <cassert>

void testGraph() {
    Graph<int, std::string> graph(3);
    assert(graph.vertexCount() == 3);
    
    size_t v3 = graph.addVertex();
    assert(v3 == 3);
    assert(graph.vertexCount() == 4);
    
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    assert(graph.hasEdge(0, 1));
    assert(graph.hasEdge(1, 2));
    assert(graph.hasEdge(2, 3));
    assert(!graph.hasEdge(0, 2));
    
    graph.setVertexData(0, "A");
    graph.setVertexData(1, "B");
    graph.setVertexData(2, "C");
    graph.setVertexData(3, "D");
    assert(graph.getVertexData(0) == "A");
    assert(graph.getVertexData(3) == "D");
    
    graph.setEdgeData(0, 1, 5);
    graph.setEdgeData(1, 2, 3);
    assert(graph.getEdgeData(0, 1) == 5);
    assert(graph.getEdgeData(1, 2) == 3);
    
    size_t neighbors[] = {1};
    size_t i = 0;
    for (auto it = graph.beginNeighbors(0); it != graph.endNeighbors(0); ++it) {
        assert(*it == neighbors[i++]);
    }
    
    graph.removeEdge(0, 1);
    assert(!graph.hasEdge(0, 1));
    
    graph.removeVertex(1);
    assert(graph.vertexCount() == 3);
    assert(!graph.hasEdge(1, 2)); 
    
    std::cout << "All graph tests passed!" << std::endl;
}

int main() {
    testGraph();
    return 0;
}
