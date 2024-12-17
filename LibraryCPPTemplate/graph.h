#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <vector>
#include <stdexcept>

template <typename ValueType, typename EdgeType>
class Graph {
public:
    struct Edge {
        size_t to;
        EdgeType label;
    };

    Graph(size_t vertexCount);
    void addVertex(const ValueType& label);
    void addEdge(size_t from, size_t to, const EdgeType& label);
    void removeVertex(size_t vertex);
    void removeEdge(size_t from, size_t to);
    bool hasEdge(size_t from, size_t to) const;
    void setEdgeLabel(size_t from, size_t to, const EdgeType& label);
    EdgeType getEdgeLabel(size_t from, size_t to) const;
    void setVertexLabel(size_t vertex, const ValueType& label);
    ValueType getVertexLabel(size_t vertex) const;
    std::vector<ValueType> getAllVertexLabels() const;

    class NeighborIterator {
    public:
        NeighborIterator(std::nullptr_t) : current_(nullptr) {}
        NeighborIterator(typename List<Edge>::Item* item) : current_(item) {}
        NeighborIterator(const typename List<Edge>::Item* item) : current_(const_cast<typename List<Edge>::Item*>(item)) {}
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
            if (!current_) throw std::out_of_range("Итератор находится вне зоны действия");
            return {current_->data().to, current_->data().label};
        }
    private:
        typename List<Edge>::Item* current_;
    };

    NeighborIterator neighborsBegin(size_t vertex) const;
    NeighborIterator neighborsEnd(size_t vertex) const;

private:
    std::vector<ValueType> vertices_;
    std::vector<List<Edge>> adjacencyList_;
};

template <typename ValueType, typename EdgeType>
Graph<ValueType, EdgeType>::Graph(size_t vertexCount) : vertices_(vertexCount), adjacencyList_(vertexCount) {}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::addVertex(const ValueType& label) {
    vertices_.push_back(label);
    adjacencyList_.emplace_back();
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::addEdge(size_t from, size_t to, const EdgeType& label) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    adjacencyList_[from].insert({to, label});
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::removeVertex(size_t vertex) {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    for (size_t i = 0; i < adjacencyList_.size(); ++i) {
        auto item = adjacencyList_[i].first();
        while (item) {
            auto next = item->next();
            if (item->data().to == vertex) {
                adjacencyList_[i].erase_next(item->prev());
            } else if (item->data().to > vertex) {
                item->data().to--;
            }
            item = next;
        }
    }
    vertices_.erase(vertices_.begin() + vertex);
    adjacencyList_.erase(adjacencyList_.begin() + vertex);
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::removeEdge(size_t from, size_t to) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().to == to) {
            adjacencyList_[from].erase_next(item->prev());
            return;
        }
        item = item->next();
    }
}

template <typename ValueType, typename EdgeType>
bool Graph<ValueType, EdgeType>::hasEdge(size_t from, size_t to) const {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().to == to) {
            return true;
        }
        item = item->next();
    }
    return false;
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::setEdgeLabel(size_t from, size_t to, const EdgeType& label) {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().to == to) {
            item->data().label = label;
            return;
        }
        item = item->next();
    }
    throw std::runtime_error("Ребро не найдено");
}

template <typename ValueType, typename EdgeType>
EdgeType Graph<ValueType, EdgeType>::getEdgeLabel(size_t from, size_t to) const {
    if (from >= vertices_.size() || to >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    auto item = adjacencyList_[from].first();
    while (item) {
        if (item->data().to == to) {
            return item->data().label;
        }
        item = item->next();
    }
    throw std::runtime_error("Ребро не найдено");
}

template <typename ValueType, typename EdgeType>
void Graph<ValueType, EdgeType>::setVertexLabel(size_t vertex, const ValueType& label) {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    vertices_[vertex] = label;
}

template <typename ValueType, typename EdgeType>
ValueType Graph<ValueType, EdgeType>::getVertexLabel(size_t vertex) const {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
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
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    return NeighborIterator(adjacencyList_[vertex].first());
}

template <typename ValueType, typename EdgeType>
typename Graph<ValueType, EdgeType>::NeighborIterator Graph<ValueType, EdgeType>::neighborsEnd(size_t vertex) const {
    if (vertex >= vertices_.size()) {
        throw std::out_of_range("Индекс вершины вне диапазона");
    }
    return NeighborIterator(nullptr);
}

#endif
