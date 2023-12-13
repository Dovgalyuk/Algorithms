#include <iostream>
#include "graph.h"

typedef Graph<size_t> MyGraph;

int main() {
    std::cout << "Testing constructor..." << std::endl;
    MyGraph graph(5);
    if (graph.vertexCount() != 5)
    {
        std::cout << "Constructor test failed: wrong vertex count." << std::endl;
        return 1;
    }

    std::cout << "Testing addVertex..." << std::endl;
    graph.addVertex();
    if (graph.vertexCount() != 6)
    {
        std::cout << "Add vertex test failed." << std::endl;
        return 1;
    }

    std::cout << "Testing addEdge with multiple edges..." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        graph.addEdge(i, (i + 1) % graph.vertexCount(), 10 * i);
        if (!graph.hasEdge(i, (i + 1) % graph.vertexCount()))
        {
            std::cout << "Add edge test failed for edge " << i << " to " << (i + 1) % graph.vertexCount() << std::endl;
            return 1;
        }
    }

    std::cout << "Testing removeEdge with multiple edges..." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        graph.removeEdge(i, (i + 1) % graph.vertexCount());
        if (graph.hasEdge(i, (i + 1) % graph.vertexCount()))
        {
            std::cout << "Remove edge test failed for edge " << i << " to " << (i + 1) % graph.vertexCount() << std::endl;
            return 1;
        }
    }

    std::cout << "Testing vertex data..." << std::endl;
    graph.setVertexLabel(0, 123);
    if (graph.getVertexLabel(0) != 123)
    {
        std::cout << "Vertex data test failed." << std::endl;
        return 1;
    }

    std::cout << "Testing edge data..." << std::endl;
    graph.addEdge(0, 1, 10);
    graph.setEdgeLabel(0, 1, 20);
    if (graph.getEdgeLabel(0, 1) != 20)
    {
        std::cout << "Edge data test failed." << std::endl;
        return 1;
    }

    std::cout << "Testing add multiple edges to a single vertex..." << std::endl;
    for (int i = 1; i < graph.vertexCount(); i++)
    {
        graph.addEdge(0, i, 10 * i);
    }
    for (int i = 1; i < graph.vertexCount(); i++)
    {
        if (!graph.hasEdge(0, i))
        {
            std::cout << "Multiple edges test failed for edge from 0 to " << i << std::endl;
            return 1;
        }
    }


    std::cout << "Testing removeVertex with non-empty edge set..." << std::endl;
    int removeVertexIndex = 2;
    graph.removeVertex(removeVertexIndex);
    if (graph.vertexCount() != 5)
    {
        std::cout << "Remove vertex test failed: incorrect vertex count." << std::endl;
        return 1;
    }
    for (int i = 0; i < graph.vertexCount(); i++)
    {
        if (graph.hasEdge(i, removeVertexIndex))
        {
            std::cout << "Remove vertex test failed: found edge to removed vertex." << std::endl;
            return 1;
        }
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
