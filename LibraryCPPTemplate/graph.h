#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <climits>

template<typename Data>
class Graph {
private:
    std::unordered_map<size_t, std::unordered_map<size_t, Data>> edges;

public:
    void addEdge(size_t start_vertex, size_t end_vertex, Data edge_data) {
        edges[start_vertex][end_vertex] = edge_data;
    }

    bool isEdgeExist(size_t start_vertex, size_t end_vertex) const {
        return edges.find(start_vertex) != edges.end() && edges.at(start_vertex).find(end_vertex) != edges.at(start_vertex).end();
    }

    Data getEdgeData(size_t start_vertex, size_t end_vertex) const {
        return edges.at(start_vertex).at(end_vertex);
    }

    const std::unordered_map<size_t, Data>& getEdges(size_t vertex) const {
        return edges.at(vertex);
    }

    size_t getVertexAmount() const {
        return edges.size();
    }

    void printGraph() const {
        for (const auto& pair : edges) {
            size_t vertex = pair.first;
            std::cout << "Vertex " << vertex << " has edges: ";
            for (const auto& edge : pair.second) {
                std::cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            std::cout << "\n";
        }
    }
};

#endif 
