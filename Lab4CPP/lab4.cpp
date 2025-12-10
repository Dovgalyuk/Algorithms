#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "graph.h"

bool findShortestPaths(const std::string& inputFile, const std::string& startVertex, const std::string& endVertex) {
    std::cout << "DEBUG: Opening file: " << inputFile << std::endl;

    std::string paths_to_try[] = {
        inputFile,
        "./" + inputFile,
        "../" + inputFile
    };

    std::ifstream file;
    std::string used_path;

    for (const auto& path : paths_to_try) {
        file.open(path);
        if (file.is_open()) {
            used_path = path;
            std::cout << "DEBUG: Successfully opened: " << path << std::endl;
            break;
        }
        else {
            std::cout << "DEBUG: Failed to open: " << path << std::endl;
        }
    }

    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open file '" << inputFile << "' from any location" << std::endl;
        std::cerr << "Current directory: ";
        system("pwd");
        return false;
    }

    size_t vertexCount;
    file >> vertexCount;

    if (file.fail()) {
        std::cerr << "ERROR: Failed to read vertex count from file" << std::endl;
        return false;
    }

    std::cout << "Reading " << vertexCount << " vertices..." << std::endl;

    Graph<std::string, int> graph;
    std::vector<std::string> vertexNames;

    for (size_t i = 0; i < vertexCount; ++i) {
        std::string name;
        if (!(file >> name)) {
            std::cerr << "ERROR: Failed to read vertex name #" << i << std::endl;
            return false;
        }
        graph.addVertex(name);
        vertexNames.push_back(name);
        std::cout << "  Vertex " << i << ": " << name << std::endl;
    }

    size_t edgeCount;
    file >> edgeCount;

    if (file.fail()) {
        std::cerr << "ERROR: Failed to read edge count from file" << std::endl;
        return false;
    }

    std::cout << "Reading " << edgeCount << " edges..." << std::endl;

    for (size_t i = 0; i < edgeCount; ++i) {
        std::string from, to;
        int weight;

        if (!(file >> from >> to >> weight)) {
            std::cerr << "ERROR: Failed to read edge #" << i << std::endl;
            return false;
        }

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
            if (graph.addEdge(fromIndex, toIndex, weight)) {
                std::cout << "  Edge " << from << " -> " << to << " (" << weight << ")" << std::endl;
            }
            else {
                std::cout << "  WARNING: Edge " << from << " -> " << to << " already exists or failed to add" << std::endl;
            }
        }
        else {
            std::cerr << "  ERROR: Vertex not found for edge " << from << " -> " << to << std::endl;
            if (!foundFrom) std::cerr << "    Vertex '" << from << "' not found in vertex list" << std::endl;
            if (!foundTo) std::cerr << "    Vertex '" << to << "' not found in vertex list" << std::endl;
        }
    }
    file.close();

    std::cout << "\nLooking for start vertex '" << startVertex << "' and end vertex '" << endVertex << "'..." << std::endl;

    size_t startIndex = 0, endIndex = 0;
    bool foundStart = false, foundEnd = false;

    for (size_t i = 0; i < vertexCount; ++i) {
        if (graph.getVertexLabel(i) == startVertex) {
            startIndex = i;
            foundStart = true;
            std::cout << "  Start vertex '" << startVertex << "' found at index " << i << std::endl;
        }
        if (graph.getVertexLabel(i) == endVertex) {
            endIndex = i;
            foundEnd = true;
            std::cout << "  End vertex '" << endVertex << "' found at index " << i << std::endl;
        }
    }

    if (!foundStart || !foundEnd) {
        std::cerr << "ERROR: Start or end vertex not found!" << std::endl;
        if (!foundStart) std::cerr << "  Start vertex '" << startVertex << "' not found" << std::endl;
        if (!foundEnd) std::cerr << "  End vertex '" << endVertex << "' not found" << std::endl;
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

        std::cout << "Input file: " << inputFile << std::endl;
        std::cout << "Start vertex: " << startVertex << std::endl;
        std::cout << "End vertex: " << endVertex << std::endl;
        std::cout << std::endl;

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