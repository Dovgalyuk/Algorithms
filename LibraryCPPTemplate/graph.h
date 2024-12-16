#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <vector>
#include <stdexcept>

template <typename ValueType, typename EdgeType>
class Graph {
public:
    // Конструктор для инициализации графа с заданным количеством вершин
    Graph(size_t vertexCount);

    // Добавить вершину
    void addVertex(const ValueType& label);

    // Добавить ребро между заданными вершинами
    void addEdge(size_t from, size_t to, const EdgeType& label);

    // Удалить вершину
    void removeVertex(size_t vertex);

    // Удалить ребро
    void removeEdge(size_t from, size_t to);

    // Проверить существует ли ребро между вершинами
    bool hasEdge(size_t from, size_t to) const;

    // Задать пометку для ребра
    void setEdgeLabel(size_t from, size_t to, const EdgeType& label);

    // Считать пометку для ребра
    EdgeType getEdgeLabel(size_t from, size_t to) const;

    // Задать пометку для вершины
    void setVertexLabel(size_t vertex, const ValueType& label);

    // Считать пометку для вершины
    ValueType getVertexLabel(size_t vertex) const;

    // Получить пометки всех вершин в виде вектора
    std::vector<ValueType> getAllVertexLabels() const;

    // Итератор для перебора всех соседей заданной вершины
    class NeighborIterator {
public:
    // Constructor for nullptr
    NeighborIterator(std::nullptr_t) : current_(nullptr) {}
    
    // Constructor for non-const pointer
    NeighborIterator(typename List<std::pair<size_t, EdgeType>>::Item* item) 
        : current_(item) {}
    
    // Constructor for const pointer
    NeighborIterator(const typename List<std::pair<size_t, EdgeType>>::Item* item) 
        : current_(const_cast<typename List<std::pair<size_t, EdgeType>>::Item*>(item)) {}

    NeighborIterator& operator++() {
        if (current_) current_ = current_->next();
        return *this;
    }

    bool operator!=(const NeighborIterator& other) const {
        return current_ != other.current_;
    }

    bool operator==(const NeighborIterator& other) const {
        return current_ == other.current_;
    }

    std::pair<size_t, EdgeType> operator*() const {
        if (!current_) throw std::out_of_range("Iterator out of range");
        return current_->data();
    }

private:
    typename List<std::pair<size_t, EdgeType>>::Item* current_;
};
    // Получить итератор для начала перебора соседей вершины
    NeighborIterator neighborsBegin(size_t vertex) const;

    // Получить итератор для конца перебора соседей вершины
    NeighborIterator neighborsEnd(size_t vertex) const;

private:
    std::vector<ValueType> vertices_;
    std::vector<List<std::pair<size_t, EdgeType>>> adjacencyList_;
};

// Реализация методов

template <typename ValueType, typename EdgeType>
Graph<ValueType, EdgeType>::Graph(size_t vertexCount)
    : vertices_(vertexCount), adjacencyList_(vertexCount) {}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::addVertex(const ValueType& label) {
    vertices_.push_back(label);
    adjacencyList_.emplace_back();
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::addEdge(size_t from, size_t to, const EdgeType& label) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    adjacencyList_[from].insert({to, label});
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::removeVertex(size_t vertex) {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }

    // Удаляем все рёбра, связанные с этой вершиной
    for (size_t i = 0; i < adjacencyList_.size(); ++i) {
        auto item = adjacencyList_[i].first();
        while (item) {
            auto next = item->next();
            if (item->data().first == vertex) {
                adjacencyList_[i].erase_next(item);
            }
            item = next;
        }
    }

    // Удаляем вершину и её список смежности
    vertices_.erase(vertices_.begin() + vertex);
    adjacencyList_.erase(adjacencyList_.begin() + vertex);
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::removeEdge(size_t from, size_t to) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().first == to) {
            adjacencyList_[from].erase_next(item->prev());
            return;
        }
        item = item->next();
    }
}

template <typename ValueType, typename EdgeType>
bool Graph<ValueType, EdgeType>::hasEdge(size_t from, size_t to) const {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().first == to) {
            return true;
        }
        item = item->next();
    }
    return false;
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::setEdgeLabel(size_t from, size_t to, const EdgeType& label) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().first == to) {
            item->data().second = label;
            return;
        }
        item = item->next();
    }
    throw std::runtime_error("Edge not found");
}

template <typename ValueType, typename EdgeType>
EdgeType Graph<ValueType, EdgeType>::getEdgeLabel(size_t from, size_t to) const {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().first == to) {
            return item->data().second;
        }
        item = item->next();
    }
    throw std::runtime_error("Edge not found");
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::setVertexLabel(size_t vertex, const ValueType& label) {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    vertices_[vertex] = label;
}

template <typename ValueType, typename EdgeType>
ValueType Graph<ValueType, EdgeType>::getVertexLabel(size_t vertex) const {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices_[vertex];
}

template <typename ValueType, typename EdgeType>
std::vector<ValueType> Graph<ValueType, EdgeType>::getAllVertexLabels() const {
    return vertices_;
}

template <typename ValueType, typename EdgeType>
typename Graph<ValueType, EdgeType>::NeighborIterator Graph<ValueType, EdgeType>::neighborsBegin(size_t vertex) const {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return NeighborIterator(adjacencyList_[vertex].first());
}

template <typename ValueType, typename EdgeType>
typename Graph<ValueType, EdgeType>::NeighborIterator Graph<ValueType, EdgeType>::neighborsEnd(size_t vertex) const {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return NeighborIterator(nullptr);
}

#endif // GRAPH_H
