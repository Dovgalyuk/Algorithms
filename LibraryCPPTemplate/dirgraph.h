#ifndef DIRGRAPH_TEMPLATE_H
#define DIRGRAPH_TEMPLATE_H

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
    std::vector<std::vector<Edge>> edges;

    void checkVertex(size_t v) const {
        if (v >= vertexMarks.size())
            throw std::out_of_range("Invalid vertex id");
    }

public:
    typedef size_t VertexId;

    // Constructor. Creates graph with specified number of vertices
    DirGraph(size_t vertexCount = 0) {
        vertexMarks.resize(vertexCount);
        edges.resize(vertexCount);
    }

    // Add new vertex to the graph
    VertexId addVertex(const vertex& mark = vertex()) {
        VertexId id = vertexMarks.size();
        vertexMarks.push_back(mark);
        edges.push_back(std::vector<Edge>());
        return id;
    }

    // Remove vertex from the graph
    void removeVertex(VertexId v) {
        checkVertex(v);

        vertexMarks.erase(vertexMarks.begin() + v);
        edges.erase(edges.begin() + v);

        for (size_t i = 0; i < edges.size(); ++i) {
            auto& neighbors = edges[i];
            for (auto it = neighbors.begin(); it != neighbors.end(); ) {
                if (it->to == v) {
                    it = neighbors.erase(it);
                }
                else {
                    if (it->to > v) {
                        it->to--;
                    }
                    ++it;
                }
            }
        }
    }

    // Add edge between two vertices
    bool addEdge(VertexId from, VertexId to, const edge& mark = edge()) {
        checkVertex(from);
        checkVertex(to);

        for (const auto& e : edges[from]) {
            if (e.to == to) {
                return false;
            }
        }

        edges[from].push_back(Edge(to, mark));
        return true;
    }

    // Remove edge between two vertices
    void removeEdge(VertexId from, VertexId to) {
        checkVertex(from);
        checkVertex(to);

        auto& neighbors = edges[from];
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (it->to == to) {
                neighbors.erase(it);
                return;
            }
        }
    }

    // Check if edge exists between two vertices
    bool edgeExists(VertexId from, VertexId to) const {
        checkVertex(from);
        checkVertex(to);

        for (const auto& e : edges[from]) {
            if (e.to == to) {
                return true;
            }
        }
        return false;
    }

    // Set label for edge
    void setEdgeMark(VertexId from, VertexId to, const edge& mark) {
        checkVertex(from);
        checkVertex(to);

        for (auto& e : edges[from]) {
            if (e.to == to) {
                e.label = mark;
                return;
            }
        }
        throw std::out_of_range("Edge does not exist");
    }

    // Get label of edge
    edge getEdgeMark(VertexId from, VertexId to) const {
        checkVertex(from);
        checkVertex(to);

        for (const auto& e : edges[from]) {
            if (e.to == to) {
                return e.label;
            }
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
        typename std::vector<Edge>::const_iterator current;
        typename std::vector<Edge>::const_iterator end;

    public:
        NeighborIterator(typename std::vector<Edge>::const_iterator begin,
            typename std::vector<Edge>::const_iterator end)
            : current(begin), end(end) {
        }

        bool operator!=(const NeighborIterator& other) const {
            return current != other.current;
        }

        NeighborIterator& operator++() {
            ++current;
            return *this;
        }

        VertexId operator*() const {
            return current->to;
        }
    };

    // Get iterator to first neighbor
    NeighborIterator neighborsBegin(VertexId v) const {
        checkVertex(v);
        return NeighborIterator(edges[v].begin(), edges[v].end());
    }

    // Get iterator to end of neighbors
    NeighborIterator neighborsEnd(VertexId v) const {
        checkVertex(v);
        return NeighborIterator(edges[v].end(), edges[v].end());
    }
};

#endif