#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <string>

class Graph {
public:
    struct Vertex {
        int id;
        std::string mark;  // Пометка для вершины
    };

    struct Edge {
        Vertex* from;
        Vertex* to;
        std::string mark;  // Пометка для ребра
    };

    // Итератор для перебора соседей заданной вершины
    class NeighborIterator {
    public:
        NeighborIterator(List<Edge*>::Item* current, Vertex* vertex) : _current(current), _vertex(vertex) {
            moveToNextValid();
        }

        bool hasNext() const {
            return _current != nullptr;
        }

        Vertex* next() {
            if (!hasNext()) return nullptr;
            Vertex* neighbor = (_current->data()->from == _vertex) ? _current->data()->to : _current->data()->from;
            _current = _current->next();
            moveToNextValid();
            return neighbor;
        }

    private:
        List<Edge*>::Item* _current;
        Vertex* _vertex;

        void moveToNextValid() {
            while (_current != nullptr && _current->data()->from != _vertex && _current->data()->to != _vertex) {
                _current = _current->next();
            }
        }
    };

    Graph() {}
    ~Graph() {
        auto v = vertices.first();
        while (v) {
            delete v->data();
            v = vertices.erase_next(v->prev());
        }

        auto e = edges.first();
        while (e) {
            delete e->data();
            e = edges.erase_next(e->prev());
        }
    }

    void addVertex(int vertexId) {
        Vertex* newVertex = new Vertex{vertexId, ""};
        vertices.insert(newVertex);
    }

    void addEdge(int fromId, int toId) {
        Vertex* fromVertex = findVertex(fromId);
        Vertex* toVertex = findVertex(toId);
        if (fromVertex && toVertex) {
            Edge* newEdge = new Edge{ fromVertex, toVertex, ""};
            edges.insert(newEdge);
        }
    }

    void removeVertex(int vertexId) {
        // Поиск элемента вершины для удаления
        auto vertexItem = findVertexItem(vertexId);
        if (!vertexItem) return;

        // Удаление всех рёбер, связанных с удаляемой вершиной
        auto edge = edges.first();
        while (edge) {
            auto nextEdge = edge->next();
            if (edge->data()->from == vertexItem->data() || edge->data()->to == vertexItem->data()) {
                delete edge->data();  // Удаление объекта ребра
                edges.erase_next(edge->prev());  // Удаление элемента списка рёбер
            }
            edge = nextEdge;
        }

        // Удаление самой вершины
        delete vertexItem->data();  // Удаление объекта вершины
        vertices.erase_next(vertexItem->prev());  // Удаление элемента списка вершин
    }

    void removeEdge(int fromId, int toId) {
        auto edge = findEdgeItem(fromId, toId);
        if (edge) {
            delete edge->data();
            edges.erase_next(edge->prev());
        }
    }

    bool edgeExists(int fromId, int toId) {
        return findEdgeItem(fromId, toId) != nullptr;
    }

    void setVertexMark(int vertexId, const std::string& mark) {
        auto vertex = findVertex(vertexId);
        if (vertex) {
            vertex->mark = mark;
        }
    }

    std::string getVertexMark(int vertexId) {
        auto vertex = findVertex(vertexId);
        if(vertex)
            return vertex->mark;
        return "";
    }

    void setEdgeMark(int fromId, int toId, const std::string& mark) {
        auto edge = findEdge(fromId, toId);
        if (edge) {
            edge->mark = mark;
        }
    }

    std::string getEdgeMark(int fromId, int toId) {
        auto edge = findEdge(fromId, toId);
        if(edge)
            return edge->mark;
        return "";
    }

    int vertexCount() const {
        return (int)vertices.size();
    }

    NeighborIterator getNeighbors(int vertexId) {
        Vertex* vertex = findVertex(vertexId);
        return NeighborIterator(edges.first(), vertex);
    }

private:
    List<Vertex*> vertices;
    List<Edge*> edges;

    Vertex* findVertex(int id) {
        for (auto item = vertices.first(); item != nullptr; item = item->next()) {
            if (item->data()->id == id) {
                return item->data();
            }
        }
        return nullptr;
    }

    typename List<Vertex*>::Item* findVertexItem(int id) {
        for (auto item = vertices.first(); item != nullptr; item = item->next()) {
            if (item->data()->id == id) {
                return item;
            }
        }
        return nullptr;
    }

    Edge* findEdge(int fromId, int toId) {
        Vertex* from = findVertex(fromId);
        Vertex* to = findVertex(toId);
        if (!from || !to) return nullptr;
        for (auto item = edges.first(); item != nullptr; item = item->next()) {
            if (item->data()->from == from && item->data()->to == to) {
                return item->data();
            }
        }
        return nullptr;
    }

    typename List<Edge*>::Item* findEdgeItem(int fromId, int toId) {
        Vertex* from = findVertex(fromId);
        Vertex* to = findVertex(toId);
        for (auto item = edges.first(); item != nullptr; item = item->next()) {
            if (item->data()->from == from && item->data()->to == to) {
                return item;
            }
        }
        return nullptr;
    }
};

#endif // GRAPH_H