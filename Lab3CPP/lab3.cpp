#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "queue.h"

struct Graph {
    int vertexCount;
    int startVertex;
    int endVertex;
    std::vector<std::vector<int>> adjacencyList;
};

Graph readGraph(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream inputFile;
    if (argc > 1) {
        inputFile.open(argv[1]);
        if (!inputFile) throw std::runtime_error("Ошибка: не удается открыть файл " + std::string(argv[1]));
        input = &inputFile;
    }

    Graph graph;
    if (!(*input >> graph.vertexCount >> graph.startVertex >> graph.endVertex))
        throw std::runtime_error("Ошибка: неверный заголовок");

    graph.adjacencyList.assign(graph.vertexCount + 1, {});

    int from;
    int to;
    while (*input >> from >> to) {
        if (from >= 1 && from <= graph.vertexCount && to >= 1 && to <= graph.vertexCount) {
            graph.adjacencyList[from].push_back(to);
            graph.adjacencyList[to].push_back(from);
        }
    }
    return graph;
}

int main(int argc, char* argv[]) {
    try {
        Graph graph = readGraph(argc, argv);
        std::vector<int> distances(graph.vertexCount + 1, -1);

        Queue *queue = queue_create();
        distances[graph.startVertex] = 0;
        queue_insert(queue, graph.startVertex);

        while (!queue_empty(queue)) {
            int curr = queue_get(queue);
            queue_remove(queue);

            for (int neighbor : graph.adjacencyList[curr]) {
                if (distances[neighbor] == -1) {
                    distances[neighbor] = distances[curr] + 1;
                    queue_insert(queue, neighbor);
                }
            }
        }

        if (distances[graph.endVertex] != -1)
            std::cout << distances[graph.endVertex] << "\n";
        else
            std::cout << "IMPOSSIBLE\n";

        queue_delete(queue);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
