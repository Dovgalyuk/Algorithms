#ifndef DIRECTED_GRAPH_TEMPLATE_H
#define DIRECTED_GRAPH_TEMPLATE_H

#include "list.h"

template <typename VertexData, typename EdgeData> class DirectedGraph {
public:
    struct Vertex;

    struct Edge {
        Vertex* to;
        EdgeData data;
        Edge(Vertex* to, EdgeData data): to(to), data(data) {}
    };

    struct Vertex {
        VertexData data;
        List<Edge*> neighbors;
        Vertex(VertexData data): data(data), neighbors(List<Edge*>()) {}
        ~Vertex() {
            while (!neighbors.empty()) {
                auto* item = neighbors.first();
                delete item->data();
                neighbors.erase(item);
            }
        }

        void removeEdge(Vertex* to) {
            EdgeItem* first = neighbors.first();
            EdgeItem* item = first;
            while (item && (item->next() != first)) {
                if (item->data() && item->data()->to == to) {
                    delete item->data();
                    neighbors.erase(item);
                    return;
                }
                item = item->next();
            }
        }
    };

    typedef typename List<Vertex*>::Item VertexItem;
    typedef typename List<Edge*>::Item EdgeItem;
    struct NearVertexIterator {
        EdgeItem* firstNeighbor = nullptr;
        EdgeItem* neighbor = nullptr;

        NearVertexIterator(Vertex* vertex) {
            firstNeighbor = vertex->neighbors.first();
            neighbor = firstNeighbor;
        }

        Edge* operator *() {
            return neighbor ? neighbor->data() : nullptr;
        }

        NearVertexIterator operator ++(int i) {
            if (neighbor->next() != firstNeighbor) {
                neighbor = neighbor->next();
            } else {
                neighbor = nullptr;
            }
            return *this;
        }
    };

    DirectedGraph(size_t vertexAmount, VertexData defaultValue): vertices(List<Vertex*>()), vertexAmount(vertexAmount) {
        for (int i = 0; i < vertexAmount; ++i) {
            vertices.insert(new Vertex(defaultValue));
        }
    }

    ~DirectedGraph() {
    }

    Vertex* addVertex(VertexData data) {
        auto* vertex = new Vertex(data);
        vertices.insert(vertex);
        vertexAmount++;
        return vertex;
    }

    Edge* addEdge(Vertex* fromVertex, Vertex* toVertex, EdgeData data) {
        Edge* edge;
        EdgeItem* item = findEdgeItem(fromVertex, toVertex);
        if (item) {
            edge = item->data();
            edge->data = data;
        } else {
            edge = new Edge(toVertex, data);
            fromVertex->neighbors.insert(edge);
        }
        return edge;
    }

    Vertex* getVertex(size_t index) {
        VertexItem* item = vertices.first();
        int i = 0;
        while (item && i++ != index) {
            item = item->next();
        }
        return item ? item->data() : nullptr;
    }

    Edge* getEdge(Vertex* fromVertex, Vertex* toVertex) {
        EdgeItem* item = findEdgeItem(fromVertex, toVertex);
        return item ? item->data() : nullptr;
    }

    void removeVertex(Vertex* vertex) {
        VertexItem* item = findVertexItem(vertex);
        if (item) {
            VertexItem* ver = vertices.first();
            int i = 0;
            while (ver && i++ < vertexAmount) {
                if (ver->data() != vertex) {
                    removeEdge(ver->data(), vertex);
                }
                ver = ver->next();
            }
            delete vertex;
            vertices.erase(item);
            vertexAmount--;
        }
    }

    void removeEdge(Vertex* fromVertex, Vertex* toVertex) {
        fromVertex->removeEdge(toVertex);
    }

    bool containsEdgeBetweenVertices(Vertex* fromVertex, Vertex* toVertex) {
        return findEdgeItem(fromVertex, toVertex);
    }

    NearVertexIterator getNearVertexIterator(Vertex* vertex) {
        return NearVertexIterator(vertex);
    }
protected:
    List<Vertex*> vertices;
    size_t vertexAmount = 0;

    VertexItem* findVertexItem(Vertex* vertex) {
        VertexItem* item = vertices.first();
        int i = 0;
        while (item && i++ < vertexAmount) {
            if (item->data() && item->data() == vertex) {
                return item;
            }
            item = item->next();
        }
        return nullptr;
    }

    EdgeItem* findEdgeItem(Vertex* fromVertex, Vertex* toVertex) {
        EdgeItem* first = fromVertex->neighbors.first();
        EdgeItem* item = first;
        while (item && (item->next() != first)) {
            if (item->data() && item->data()->to == toVertex) {
                return item;
            }
            item = item->next();
        }
        return nullptr;
    }

};
#endif