
#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <unordered_map>
#include <algorithm>
#include <climits>

template <typename VertexData, typename EdgeData>
class Graph {
public:
    struct Vertex;
    struct Edge {
        Vertex* from, * to;
        EdgeData data;
        Edge(Vertex* f, Vertex* t, EdgeData d) : from(f), to(t), data(d) {}
    };

    struct Vertex {
        VertexData data;
        List<Edge> edges;
        size_t id;  // Добавлен идентификатор для вершины

        Vertex(VertexData d, size_t id) : data(d), id(id) {}
    };

    Graph(size_t initialSize = 0) : nextVertexId(0) {
        for (size_t i = 0; i < initialSize; ++i) {
            addVertex(VertexData());
        }
    }

    ~Graph() {
        for (auto& vertexPair : vertices) {
            delete vertexPair.second;
        }
    }

    Vertex* addVertex(const VertexData& data) {
        size_t vertexId = nextVertexId++;
        Vertex* newVertex = new Vertex(data, vertexId);
        vertices[vertexId] = newVertex;
        return newVertex;
    }

    void removeVertex(Vertex* vertex) {
        if (!vertex) return;

        // Удаление всех рёбер, связанных с вершиной
        auto it = vertex->edges.first();
        while (it) {
            auto next = it->next();
            Edge* edge = &it->_data;
            if (edge->to != vertex) {
                // Удаление ребра из списка рёбер другой вершины
                removeEdgeFromVertex(edge->to, edge);
            }
            it = next;
        }

        // Удаление вершины из графа
        vertices.erase(std::find_if(vertices.begin(), vertices.end(),
            [&](const auto& pair) { return pair.second == vertex; }));
        delete vertex;
    }

    Edge* addEdge(Vertex* from, Vertex* to, const EdgeData& data) {
        Edge newEdge(from, to, data);
        from->edges.insert(newEdge);
        return &from->edges.first()->_data;
    }

    void removeEdge(Edge* edge) {
        if (!edge) return;
        removeEdgeFromVertex(edge->from, edge);
        if (edge->from != edge->to) {
            removeEdgeFromVertex(edge->to, edge);
        }
    }

    bool edgeExists(Vertex* from, Vertex* to) const {
        if (!from || !to) return false;

        auto it = from->edges.first();
        while (it) {
            if (it->_data.to == to) return true;
            it = it->next();
        }
        return false;
    }

    size_t vertexCount() const {
        return vertices.size();
    }

    void setVertexData(Vertex* vertex, const VertexData& data) {
        if (vertex) vertex->data = data;
    }

    VertexData getVertexData(Vertex* vertex) const {
        return vertex ? vertex->data : VertexData();
    }

    void setEdgeData(Edge* edge, const EdgeData& data) {
        if (edge) edge->data = data;
    }

    EdgeData getEdgeData(Edge* edge) const {
        return edge ? edge->data : EdgeData();
    }

    Vertex* getVertex(size_t vertexId) const {
        auto it = vertices.find(vertexId);
        if (it != vertices.end()) {
            return it->second;
        }
        return nullptr;
    }

    size_t getVertexId(const Vertex* vertex) const {
        if (vertex) {
            return vertex->id;
        }
        return SIZE_MAX; // Возвращаем максимально возможное значение, если вершина не найдена
    }


    class NeighborIterator {
    public:
        NeighborIterator(Vertex* vertex) : current(vertex ? vertex->edges.first() : nullptr) {}

        bool hasNext() const {
            return current != nullptr;
        }

        Vertex* next() {
            if (!hasNext()) {
                return nullptr;
            }
            Vertex* neighbor = current->_data.to;
            current = current->next();
            return neighbor;
        }

    private:
        typename List<Edge>::Item* current;
    };

private:
    std::unordered_map<size_t, Vertex*> vertices;
    size_t nextVertexId;

    void removeEdgeFromVertex(Vertex* vertex, Edge* edge) {
        if (!vertex || !edge) return;

        auto it = vertex->edges.first();
        while (it) {
            if (&it->_data == edge) {
                if (it == vertex->edges.first()) {
                    vertex->edges.erase_first();
                }
                else {
                    vertex->edges.erase_next(it->prev());
                }
                break;
            }
            it = it->next();
        }
    }
};

#endif // GRAPH_H
