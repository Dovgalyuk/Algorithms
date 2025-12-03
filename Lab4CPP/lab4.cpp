#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graph.h"

// Тестовая функция, которая будет запускаться при запуске без аргументов
void testGraphLibrary() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph(5);

    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");
    graph.setVertexLabel(3, "D");
    graph.setVertexLabel(4, "E");

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 6);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    std::cout << "Has edge A->B: " << graph.hasEdge(0, 1) << std::endl;
    std::cout << "Has edge B->A: " << graph.hasEdge(1, 0) << std::endl;

    auto labels = graph.getAllVertexLabels();
    std::cout << "Vertex labels: ";
    for (const auto& label : labels) {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    std::cout << "Neighbors of A: ";
    auto neighbors = graph.getNeighbors(0);
    while (neighbors.hasNext()) {
        int neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
    }
    std::cout << std::endl;

    std::cout << "Edge A->B weight: " << graph.getEdgeLabel(0, 1) << std::endl;
    std::cout << "Edge C->D weight: " << graph.getEdgeLabel(2, 3) << std::endl;

    // Тестирование поиска путей
    auto paths = graph.findAllShortestPaths(0, 4);
    std::cout << "\nFound " << paths.size() << " shortest path(s) from A to E" << std::endl;

    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[i][j]);
            if (j < paths[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " (Length: " << paths[i].size() - 1 << ")" << std::endl;
    }
}

bool findShortestPaths(const std::string& inputFile, const std::string& startVertex, const std::string& endVertex) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << inputFile << std::endl;
        return false;
    }

    int vertexCount;
    file >> vertexCount;

    Graph<std::string, int> graph;
    std::vector<std::string> vertexNames;

    // Читаем названия вершин и добавляем их в граф
    for (int i = 0; i < vertexCount; ++i) {
        std::string name;
        file >> name;
        graph.addVertex(name);
        vertexNames.push_back(name);
    }

    int edgeCount;
    file >> edgeCount;

    // Читаем ребра
    for (int i = 0; i < edgeCount; ++i) {
        std::string from, to;
        int weight;
        file >> from >> to >> weight;

        int fromIndex = -1, toIndex = -1;
        for (int j = 0; j < vertexCount; ++j) {
            if (vertexNames[j] == from) fromIndex = j;
            if (vertexNames[j] == to) toIndex = j;
        }

        if (fromIndex != -1 && toIndex != -1) {
            graph.addEdge(fromIndex, toIndex, weight);
        }
    }
    file.close();

    // Находим индексы начальной и конечной вершин
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < vertexCount; ++i) {
        if (graph.getVertexLabel(i) == startVertex) startIndex = i;
        if (graph.getVertexLabel(i) == endVertex) endIndex = i;
    }

    if (startIndex == -1 || endIndex == -1) {
        std::cerr << "Start or end vertex not found!" << std::endl;
        return false;
    }

    auto paths = graph.findAllShortestPaths(startIndex, endIndex);

    std::cout << "\n=== Shortest Paths from " << startVertex << " to " << endVertex << " ===" << std::endl;

    if (paths.empty()) {
        std::cout << "No path found!" << std::endl;
        return false;
    }

    // Выводим все найденные пути
    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths[i].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[i][j]);
            if (j < paths[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " (Length: " << paths[i].size() - 1 << ")" << std::endl;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // Запуск в тестовом режиме без аргументов
        testGraphLibrary();
    }
    else if (argc == 4) {
        // Запуск с файлом и вершинами
        std::string inputFile = argv[1];
        std::string startVertex = argv[2];
        std::string endVertex = argv[3];
        findShortestPaths(inputFile, startVertex, endVertex);
    }
    else {
        // Неправильное количество аргументов
        std::cout << "Usage:" << std::endl;
        std::cout << "  Testing: lab4" << std::endl;
        std::cout << "  Find paths: lab4 input.txt start_vertex end_vertex" << std::endl;
    }
    return 0;
}