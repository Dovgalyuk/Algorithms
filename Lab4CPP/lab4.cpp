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

    size_t vertexCount;
    file >> vertexCount;

    Graph<std::string, int> graph;
    std::vector<std::string> vertexNames;

    for (size_t i = 0; i < vertexCount; ++i) {
        std::string name;
        file >> name;
        graph.addVertex(name);
        vertexNames.push_back(name);
    }

    size_t edgeCount;
    file >> edgeCount;

    for (size_t i = 0; i < edgeCount; ++i) {
        std::string from, to;
        int weight;
        file >> from >> to >> weight;

        size_t fromIndex = 0, toIndex = 0;
        bool foundFrom = false, foundTo = false;

        for (size_t j = 0; j < vertexCount; ++j) {
            if (vertexNames[j] == from) {
                fromIndex = j;
                foundFrom = true;
            }
            if (vertexNames[j] == to) {
                toIndex = j;
                foundTo = true;
            }
        }

        if (foundFrom && foundTo) {
            graph.addEdge(fromIndex, toIndex, weight);
        }
        else {
            std::cerr << "WARNING: Vertex not found for edge " << from << " -> " << to << std::endl;
        }
    }
    file.close();

    size_t startIndex = 0, endIndex = 0;
    bool foundStart = false, foundEnd = false;

    for (size_t i = 0; i < vertexCount; ++i) {
        if (graph.getVertexLabel(i) == startVertex) {
            startIndex = i;
            foundStart = true;
        }
        if (graph.getVertexLabel(i) == endVertex) {
            endIndex = i;
            foundEnd = true;
        }
    }

    if (!foundStart || !foundEnd) {
        std::cerr << "Start or end vertex not found!" << std::endl;
        return false;
    }

    auto paths = graph.findAllShortestPaths(startIndex, endIndex);

    std::cout << "\n=== Shortest Paths from " << startVertex << " to " << endVertex << " ===" << std::endl;

    if (paths.size() == 0) {
        std::cout << "No path found!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < paths.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        const auto& path = paths[i];
        for (size_t j = 0; j < path.size(); ++j) {
            std::cout << graph.getVertexLabel(path[j]);
            if (j < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " (Length: " << path.size() - 1 << ")" << std::endl;
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