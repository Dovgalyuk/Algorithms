#ifndef DIRGRAPH_WITH_LIST_H
#define DIRGRAPH_WITH_LIST_H

#include "list.h"
#include <vector>
#include <stdexcept>

template <class vertex, class edge>
class DirGraph {
private:
    struct Edge {
        size_t to;
        edge label;

        Edge(size_t t, const edge& l = edge()) : to(t), label(l) {}
    };

    std::vector<vertex> vertexMarks;
    std::vector<List<Edge>> adjacencyLists;

    void checkVertex(size_t v) const {
        if (v >= vertexMarks.size())
            throw std::out_of_range("Invalid vertex id");
    }

public:
    typedef size_t VertexId;

    // Constructor. Creates graph with specified number of vertices
    DirGraph(size_t vertexCount = 0) {
        vertexMarks.resize(vertexCount);
        adjacencyLists.resize(vertexCount);
    }

    // Add new vertex to the graph
    VertexId addVertex(const vertex& mark = vertex()) {
        VertexId id = vertexMarks.size();
        vertexMarks.push_back(mark);
        adjacencyLists.push_back(List<Edge>());
        return id;
    }

    // Remove vertex from the graph - упрощенная версия
    void removeVertex(VertexId v) {
        checkVertex(v);

        adjacencyLists[v] = List<Edge>(); 

        for (size_t i = 0; i < adjacencyLists.size(); ++i) {
            if (i == v) continue;

            List<Edge>& neighbors = adjacencyLists[i];
            typename List<Edge>::Item* current = neighbors.first();
            typename List<Edge>::Item* prevItem = nullptr;

            while (current != nullptr) {
                if (current->data().to == v) {

                    if (prevItem == nullptr) {
                        neighbors.erase_first();
                        current = neighbors.first();
                    }
                    else {
                        current = neighbors.erase_next(prevItem);
                    }
                }
                else if (current->data().to > v) {

                    Edge correctedEdge(current->data().to - 1, current->data().label);

                    if (prevItem == nullptr) {
                        neighbors.erase_first();
                        neighbors.insert(correctedEdge);
                        current = neighbors.first();
                    }
                    else {
                        typename List<Edge>::Item* nextItem = current->next();
                        neighbors.erase_next(prevItem);
                        neighbors.insert_after(prevItem, correctedEdge);
                        current = nextItem;
                    }
                }
                else {
                    prevItem = current;
                    current = current->next();
                }
            }
        }

        vertexMarks.erase(vertexMarks.begin() + v);
        adjacencyLists.erase(adjacencyLists.begin() + v);
    }

    // Add edge between two vertices
    bool addEdge(VertexId from, VertexId to, const edge& mark = edge()) {
        checkVertex(from);
        checkVertex(to);

        typename List<Edge>::Item* current = adjacencyLists[from].first();
        while (current != nullptr) {
            if (current->data().to == to) {
                return false; // edge already exists
            }
            current = current->next();
        }

        // Insert new edge
        adjacencyLists[from].insert(Edge(to, mark));
        return true;
    }

    // Remove edge between two vertices
    void removeEdge(VertexId from, VertexId to) {
        checkVertex(from);
        checkVertex(to);

        List<Edge>& neighbors = adjacencyLists[from];
        typename List<Edge>::Item* current = neighbors.first();
        typename List<Edge>::Item* prevItem = nullptr;

        while (current != nullptr) {
            if (current->data().to == to) {
                if (prevItem == nullptr) {
                    neighbors.erase_first();
                }
                else {
                    neighbors.erase_next(prevItem);
                }
                return;
            }
            prevItem = current;
            current = current->next();
        }
    }

    // Check if edge exists between two vertices
    bool edgeExists(VertexId from, VertexId to) const {
        checkVertex(from);
        checkVertex(to);

        const typename List<Edge>::Item* current = adjacencyLists[from].first();
        while (current != nullptr) {
            if (current->data().to == to) {
                return true;
            }
            current = current->next();
        }
        return false;
    }

    // Set label for edge
    void setEdgeMark(VertexId from, VertexId to, const edge& mark) {
        checkVertex(from);
        checkVertex(to);

        typename List<Edge>::Item* current = adjacencyLists[from].first();
        while (current != nullptr) {
            if (current->data().to == to) {
                // Remove and reinsert with new mark
                Edge newEdge(to, mark);
                removeEdge(from, to);
                adjacencyLists[from].insert(newEdge);
                return;
            }
            current = current->next();
        }
        throw std::out_of_range("Edge does not exist");
    }

    // Get label of edge
    edge getEdgeMark(VertexId from, VertexId to) const {
        checkVertex(from);
        checkVertex(to);

        const typename List<Edge>::Item* current = adjacencyLists[from].first();
        while (current != nullptr) {
            if (current->data().to == to) {
                return current->data().label;
            }
            current = current->next();
        }
        throw std::out_of_range("Edge does not exist");
    }

    // Set label for vertex
    void setVertexMark(VertexId v, const vertex& mark) {
        checkVertex(v);
        vertexMarks[v] = mark;
    }

    // Get label of vertex
    vertex getVertexMark(VertexId v) const {
        checkVertex(v);
        return vertexMarks[v];
    }

    // Get labels of all vertices
    std::vector<vertex> getAllVertexMarks() const {
        return vertexMarks;
    }

    // Get total number of vertices
    size_t getVertexCount() const {
        return vertexMarks.size();
    }

    // Iterator for neighbors of a vertex
    class NeighborIterator {
    private:
        const typename List<Edge>::Item* current;

    public:
        NeighborIterator(const typename List<Edge>::Item* start) : current(start) {}

        bool operator!=(const NeighborIterator& other) const {
            return current != other.current;
        }

        NeighborIterator& operator++() {
            if (current != nullptr)
                current = current->next();
            return *this;
        }

        VertexId operator*() const {
            return current->data().to;
        }
    };

    // Get iterator to first neighbor
    NeighborIterator neighborsBegin(VertexId v) const {
        checkVertex(v);
        return NeighborIterator(adjacencyLists[v].first());
    }

    // Get iterator to end of neighbors
    NeighborIterator neighborsEnd(VertexId v) const {
        checkVertex(v);
        return NeighborIterator(nullptr);
    }
};

#endif