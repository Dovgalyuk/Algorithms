#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"


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

    for (int i = 0; i < vertexCount; ++i) {
        std::string name;
        file >> name;
        graph.addVertex(name);
        vertexNames.push_back(name);
    }

    int edgeCount;
    file >> edgeCount;

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

        std::cout << "Graph Library - Shortest Path Finder" << std::endl;
        std::cout << "Usage: lab4 input.txt start_vertex end_vertex" << std::endl;
        std::cout << "Example: lab4 input.txt A E" << std::endl;
        return 0;
    }
    else if (argc == 4) {
        std::string inputFile = argv[1];
        std::string startVertex = argv[2];
        std::string endVertex = argv[3];
        if (!findShortestPaths(inputFile, startVertex, endVertex)) {
            return 1;
        }
    }
    else {
        std::cout << "Invalid arguments!" << std::endl;
        std::cout << "Usage: lab4 input.txt start_vertex end_vertex" << std::endl;
        return 1;
    }
    return 0;
}