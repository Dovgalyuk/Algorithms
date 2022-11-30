#include "KruskalsAlgorithm.hpp"
#include <iostream>

int main() {
    int vertex_amount = 0;
    int edges_amount = 0;
    std::cout << "Enter vertex amount: ";  std::cin >> vertex_amount;

    // Исходный граф
    Graph<int> *graph = new Graph<int>(vertex_amount, 0);
    // Установка вершинам метки = порядку вершины
    for(int i = 0; i < vertex_amount; i++) {
        graph->getVertex(i)->setVertexData(i);
    }

    std::cout << "Enter edges amount: ";  std::cin >> edges_amount;
    int start = 0;
    int end = 0;
    int weight;
    for(int i = 0; i < edges_amount; i++) {
        std::cout << "#" << i+1 << " Edge - [start]: "; std::cin >> start;
        std::cout << "#" << i+1 << " Edge - [end]: "; std::cin >> end;
        std::cout << "#" << i+1 << " Edge - [weight]: "; std::cin >> weight;
        graph->addEdge(start, end, weight);
        std::cout << std::endl;
    }

    KruskalsAlgorithm algorithm(graph);
    algorithm.run();
    algorithm.printResult();

    delete graph;
}