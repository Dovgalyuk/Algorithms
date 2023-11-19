#include <iostream>
#include "graph.h"

typedef Graph<int> MyGraph;

int main() {
    // Тестирование конструктора
    std::cout << "Testing constructor..." << std::endl;
    MyGraph graph(5);
    if (graph.vertexCount() != 5) 
    {
        std::cout << "Constructor test failed: wrong vertex count." << std::endl;
        return 1;
    }

    // Тестирование добавления вершин
    std::cout << "Testing addVertex..." << std::endl;
    graph.addVertex();
    if (graph.vertexCount() != 6) 
    {
        std::cout << "Add vertex test failed." << std::endl;
        return 1;
    }

    // Тестирование добавления нескольких рёбер
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

    // Тестирование удаления нескольких рёбер
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

    // Тестирование пометок для вершин
    std::cout << "Testing vertex data..." << std::endl;
    graph.setVertexData(0, 123);
    if (graph.getVertexData(0) != 123) 
    {
        std::cout << "Vertex data test failed." << std::endl;
        return 1;
    }

    // Тестирование пометок для рёбер
    std::cout << "Testing edge data..." << std::endl;
    graph.addEdge(0, 1, 10);
    //std::cout << "Adding edge data..." << std::endl;
    graph.setEdgeData(0, 1, 20);
    //std::cout << "Setting edge data..." << std::endl;
    if (graph.getEdgeData(0, 1) != 20) 
    {
        std::cout << "Edge data test failed." << std::endl;
        return 1;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
