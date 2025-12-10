#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "LibraryCPPTemplate/IGraph.h"
#include "LibraryCPPTemplate/AdjacencyMatrixGraph.h"
#include "LibraryCPPTemplate/BFSShortestPaths.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <start_vertex> <end_vertex>\n";
        return 1;
    }

    try {
        std::ifstream input(argv[1]);
        if (!input) {
            throw std::runtime_error("Cannot open input file: " + std::string(argv[1]));
        }

        auto graph = std::make_shared<AdjacencyMatrixGraph<std::string, double>>();

        std::size_t vertexCount;
        if (!(input >> vertexCount)) {
            throw std::runtime_error("Failed to read vertex count");
        }

        graph->initialize(vertexCount);

        for (std::size_t i = 0; i < vertexCount; ++i) {
            std::string name;
            if (!(input >> name)) {
                throw std::runtime_error("Failed to read vertex name " + std::to_string(i));
            }
            graph->setVertex(i, name);
        }

        std::size_t edgeCount;
        if (!(input >> edgeCount)) {
            throw std::runtime_error("Failed to read edge count");
        }

        for (std::size_t i = 0; i < edgeCount; ++i) {
            std::size_t from, to;
            double weight;
            if (!(input >> from >> to >> weight)) {
                throw std::runtime_error("Failed to read edge " + std::to_string(i));
            }
            graph->addEdge(from, to, weight);
        }

        std::string startName = argv[2];
        std::string endName = argv[3];

        auto paths = BFSShortestPaths<std::string, double>::findAllShortestPaths(
            *graph, startName, endName);

        if (paths.empty()) {
            std::cout << "No paths found from " << startName << " to " << endName << "\n";
        }
        else {
            std::cout << "Found " << paths.size() << " shortest path(s):\n";
            for (const auto& pathInfo : paths) {
                std::cout << "Cost: " << pathInfo.totalCost << ", Path: ";
                for (std::size_t i = 0; i < pathInfo.vertices.size(); ++i) {
                    std::cout << graph->getVertex(pathInfo.vertices[i]);
                    if (i != pathInfo.vertices.size() - 1) {
                        std::cout << " -> ";
                    }
                }
                std::cout << "\n";
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}