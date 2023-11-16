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

    // Тестирование добавления ребра
    std::cout << "Testing addEdge..." << std::endl;
    graph.addEdge(0, 1, 10);
    if (!graph.hasEdge(0, 1)) 
    {
        std::cout << "Add edge test failed." << std::endl;
        return 1;
    }

    // Тестирование удаления ребра
    std::cout << "Testing removeEdge..." << std::endl;
    graph.removeEdge(0, 1);
    if (graph.hasEdge(0, 1)) 
    {
        std::cout << "Remove edge test failed." << std::endl;
        return 1;
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
