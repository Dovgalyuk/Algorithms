#pragma once
#include "IGraph.h"
#include "LibraryCPPTemplate/vector.h"
#include <queue>
#include <unordered_map>
#include <algorithm>

template<class VertexType, class EdgeType>
class BFSShortestPaths {
public:
    struct PathInfo {
        Vector<std::size_t> vertices;
        EdgeType totalCost;
    };

    static Vector<PathInfo> findAllShortestPaths(
        const IGraph<VertexType, EdgeType>& graph,
        const std::string& startName,
        const std::string& endName) {

        std::size_t start = findVertexIndex(graph, startName);
        std::size_t end = findVertexIndex(graph, endName);

        if (start >= graph.vertexCount() || end >= graph.vertexCount()) {
            return {};
        }

        Vector<PathInfo> result;
        std::queue<Vector<std::size_t>> pathsQueue;
        std::unordered_map<std::size_t, std::size_t> minDistances;

        Vector<std::size_t> startPath = { start };
        pathsQueue.push(startPath);
        minDistances[start] = 0;

        std::size_t shortestLength = std::numeric_limits<std::size_t>::max();

        while (!pathsQueue.empty()) {
            auto currentPath = pathsQueue.front();
            pathsQueue.pop();

            std::size_t currentVertex = currentPath.back();
            std::size_t currentLength = currentPath.size() - 1;

            if (currentLength > shortestLength) {
                continue;
            }

            if (currentVertex == end) {
                if (currentLength < shortestLength) {
                    shortestLength = currentLength;
                    result.clear();
                }

                EdgeType totalCost = 0;
                for (std::size_t i = 0; i < currentPath.size() - 1; ++i) {
                    totalCost += graph.getEdge(currentPath[i], currentPath[i + 1]);
                }

                result.push_back({ currentPath, totalCost });
                continue;
            }

            auto iterator = graph.createNeighborIterator(currentVertex);
            while (iterator->hasNext()) {
                auto [neighborIdx, neighborName, edgeWeight] = iterator->next();

                if (std::find(currentPath.begin(), currentPath.end(), neighborIdx) != currentPath.end()) {
                    continue;
                }

                auto it = minDistances.find(neighborIdx);
                if (it == minDistances.end() || it->second >= currentLength + 1) {
                    minDistances[neighborIdx] = currentLength + 1;

                    Vector<std::size_t> newPath = currentPath;
                    newPath.push_back(neighborIdx);
                    pathsQueue.push(newPath);
                }
            }
        }

        return result;
    }

private:
    static std::size_t findVertexIndex(const IGraph<VertexType, EdgeType>& graph,
        const std::string& name) {
        const auto& vertices = graph.getAllVertices();
        for (std::size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == name) {
                return i;
            }
        }
        return std::numeric_limits<std::size_t>::max();
    }
};