#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h" 
#include "list.h"
#include <optional>
#include <iostream> 

template<typename VertexLabelType, typename EdgeLabelType>
class Graph {
private:
    struct Edge {
        size_t to;
        std::optional<EdgeLabelType> label;
    };

    Vector<std::optional<VertexLabelType>> vertexLabels; 
    Vector<List<Edge>> adjacencyLists; 

public:
    explicit Graph(size_t vertexCount) {
        vertexLabels.resize(vertexCount);
        adjacencyLists.resize(vertexCount);
    }

    void AddVertex() {
        vertexLabels.resize(vertexLabels.size() + 1);
        adjacencyLists.resize(adjacencyLists.size() + 1);
    }

    void RemoveVertex(size_t index) {
        if (index >= vertexLabels.size()) {
            std::cout << "Ошибка: индекс вершины выходит за пределы\n";
            return;
        }
   
        adjacencyLists.set(index, List<Edge>()); 
    
        for (size_t i = 0; i < adjacencyLists.size(); ++i) {
            auto& list = adjacencyLists.get(i);
            for (auto* item = list.head; item != nullptr; item = item->next()) {
                auto& edge = item->data();
                if (edge.to == index) {
                } else if (edge.to > index) {
                    edge.to--;
                }
            }
        }
  
        vertexLabels.set(index, std::nullopt);
        for (size_t i = index; i < vertexLabels.size() - 1; ++i) {
            vertexLabels.set(i, vertexLabels.get(i + 1));
            adjacencyLists.set(i, adjacencyLists.get(i + 1));
        }
        vertexLabels.resize(vertexLabels.size() - 1);
        adjacencyLists.resize(adjacencyLists.size() - 1);
    
        std::cout << "Вершина " << index << " удалена\n";
    }

    void AddEdge(size_t from, size_t to, std::optional<EdgeLabelType> label = std::nullopt) {
        if (from >= adjacencyLists.size() || to >= adjacencyLists.size()) {
            std::cout << "Ошибка: индекс вершины выходит за пределы\n";
            return;
        }

        if (HasEdge(from, to)) {
            std::cout << "Ребро " << from << " -> " << to << " уже существует\n";
            return;
        }

        Edge edge{to, label};
        adjacencyLists.get(from).push_back(edge);
        std::cout << "Ребро " << from << " -> " << to << " добавлено\n";
    }

    void RemoveEdge(size_t from, size_t to) {
        if (from >= adjacencyLists.size()) return;

        auto& list = adjacencyLists.get(from);
        for (size_t i = 0; i < list.size(); ++i) {
            auto& edge = list.get(i)->data(); 
            if (edge.to == to) {
                list.erase(i);
                std::cout << "Ребро " << from << " -> " << to << " удалено\n";
                return;
            }
        }
        std::cout << "Ребро " << from << " -> " << to << " не найдено для удаления\n";
    }

    bool HasEdge(size_t from, size_t to) const {
        if (from >= adjacencyLists.size()) {
            std::cout << "Ошибка: индекс вершины выходит за пределы\n";
            return false;
        }

        const auto& list = adjacencyLists.get(from);
        for (size_t i = 0; i < list.size(); ++i) {
            const auto& edge = list.get(i)->data(); 
            if (edge.to == to) {
                return true;
            }
        }
        return false;
    }

    void SetVertexLabel(size_t index, const VertexLabelType& label) {
        if (index >= vertexLabels.size()) return;
        vertexLabels.set(index, label);
    }

    std::optional<VertexLabelType> GetVertexLabel(size_t index) const {
        if (index >= vertexLabels.size()) return std::nullopt;
        return vertexLabels.get(index);
    }

    void SetEdgeLabel(size_t from, size_t to, const EdgeLabelType& label) {
        if (from >= adjacencyLists.size()) return;

        auto& list = adjacencyLists.get(from);
        for (size_t i = 0; i < list.size(); ++i) {
            auto& edge = list.get(i)->data(); 
            if (edge.to == to) {
                edge.label = label;
                std::cout << "Метка ребра " << from << " -> " << to << " обновлена\n";
                return;
            }
        }
        std::cout << "Ребро " << from << " -> " << to << " не найдено для обновления метки\n";
    }

    std::optional<EdgeLabelType> GetEdgeLabel(size_t from, size_t to) const {
        if (from >= adjacencyLists.size()) return std::nullopt;

        const auto& list = adjacencyLists.get(from);
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

    Vector<size_t> GetNeighbors(size_t vertex) const {
        Vector<size_t> neighbors;
        if (vertex >= adjacencyLists.size()) return neighbors;

        const auto& list = adjacencyLists.get(vertex);
        neighbors.resize(list.size());
        for (size_t i = 0; i < list.size(); ++i) {
            neighbors.set(i, list.get(i)->data().to); 
        }
        return neighbors;
    }

    const List<Edge>& GetAdjacencyList(size_t vertex) const {
        return adjacencyLists.get(vertex);
    }

public:
    class NeighborIterator {
    public:
        NeighborIterator(typename List<Edge>::Item* ptr) : ptr_(ptr) {}
        NeighborIterator& operator++() { if (ptr_) ptr_ = ptr_->next(); return *this; }
        bool operator!=(const NeighborIterator& other) const { return ptr_ != other.ptr_; }
        size_t operator*() const { return ptr_->data().to; }
    private:
        typename List<Edge>::Item* ptr_;
    };

    NeighborIterator neighbors_begin(size_t vertex) const {
        return NeighborIterator(adjacencyLists.get(vertex).head);
    }
    NeighborIterator neighbors_end(size_t) const {
        return NeighborIterator(nullptr);
    }
};

#endif
