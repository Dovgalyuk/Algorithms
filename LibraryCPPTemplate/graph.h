#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <optional>
#include "list.h"

template<typename VertexLabelType, typename EdgeLabelType>
class Graph {
private:
    struct Edge {
        size_t to;
        std::optional<EdgeLabelType> label;
    };

    std::vector<std::optional<VertexLabelType>> vertexLabels;
    std::vector<List<Edge>> adjacencyLists;

public:
    explicit Graph(size_t vertexCount) {
        vertexLabels.resize(vertexCount);
        adjacencyLists.resize(vertexCount);
    }

    void AddVertex() {
        vertexLabels.push_back(std::nullopt);
        adjacencyLists.emplace_back();
    }

    void RemoveVertex(size_t index) {
        if (index >= vertexLabels.size()) return;

        while (!adjacencyLists[index].empty()) {
            adjacencyLists[index].erase(0); 
        }
 
        for (auto& list : adjacencyLists) {
            for (size_t i = 0; i < list.size(); ++i) {
                if (list.get(i)->data().to == index) {
                    list.erase(i);
                    --i;
                }
            }
        }
    
        vertexLabels.erase(vertexLabels.begin() + index);
        adjacencyLists.erase(adjacencyLists.begin() + index);
    
        for (auto& list : adjacencyLists) {
            for (size_t i = 0; i < list.size(); ++i) {
                if (list.get(i)->data().to > index) {
                    list.get(i)->data().to--;
                }
            }
        }
    }

    void AddEdge(size_t from, size_t to, std::optional<EdgeLabelType> label = std::nullopt) {
        if (from >= adjacencyLists.size() || to >= adjacencyLists.size()) return;

        if (HasEdge(from, to)) return; 

        Edge edge{to, label};
        adjacencyLists[from].push_back(edge);
    }

    void RemoveEdge(size_t from, size_t to) {
        if (from >= adjacencyLists.size()) return;

        auto& list = adjacencyLists[from];
        for (size_t i = 0; i < list.size(); ++i) {
            if (list.get(i)->data().to == to) { 
                list.erase(i);
                break;
            }
        }
    }

    bool HasEdge(size_t from, size_t to) const {
        if (from >= adjacencyLists.size()) return false;

        const auto& list = adjacencyLists[from];
        for (size_t i = 0; i < list.size(); ++i) {
            if (list.get(i)->data().to == to) 
                return true;
        }
        return false;
    }

    void SetVertexLabel(size_t index, const VertexLabelType& label) {
        if (index >= vertexLabels.size()) return;
        vertexLabels[index] = label;
    }

    std::optional<VertexLabelType> GetVertexLabel(size_t index) const {
        if (index >= vertexLabels.size()) return std::nullopt;
        return vertexLabels[index];
    }

    void SetEdgeLabel(size_t from, size_t to, const EdgeLabelType& label) {
        if (from >= adjacencyLists.size()) return;

        auto& list = adjacencyLists[from];
        for (size_t i = 0; i < list.size(); ++i) {
            auto& edge = list.get(i)->data(); 
            if (edge.to == to) {
                edge.label = label; 
                break;
            }
        }
    }

    std::optional<EdgeLabelType> GetEdgeLabel(size_t from, size_t to) const {
        if (from >= adjacencyLists.size()) return std::nullopt;

        const auto& list = adjacencyLists[from];
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& edge = list.get(i)->data(); 
            if (edge.to == to) {
                return edge.label; 
            }
        }
        return std::nullopt;
    }

    size_t VertexCount() const {
        return vertexLabels.size();
    }

    // Возвращает список соседей для заданной вершины
    std::vector<size_t> GetNeighbors(size_t vertex) const {
        std::vector<size_t> neighbors;
        if (vertex >= adjacencyLists.size()) return neighbors;

        const auto& list = adjacencyLists[vertex];
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& edge = list.get(i)->data(); 
            neighbors.push_back(edge.to);          
        }
        return neighbors;
    }
};

#endif 
