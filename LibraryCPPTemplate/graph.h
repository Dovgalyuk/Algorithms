#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "list.h"
#include <vector>

template<typename Data>
class Graph {
public:
    struct Edge;

    typedef List<Edge> Edges;

    struct Vertex {
        Data data;
        Edges edges = List<Edge>();

        Vertex(Data data) {
            this->data = data;
        }

        void setData(Data data) {
            this->data = data;
        }

        Data getData() {
            return data;
        }

        void addEdge(Vertex* toVertex) {
            edges.insert(Edge(toVertex));
        }

        bool hasEdge(Vertex *toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->next()) {
                if (item->data().getToVertex() == toVertex) {
                    return true;
                }
            }

            return false;
        }

        Edge& getEdge(Vertex* toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->next()) {
                if (item->data().getToVertex() == toVertex) {
                    return item->data();
                }
            }
            Edge nullEdge = Edge();
            return nullEdge;
        }

        void removeEdge(Vertex* toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->next()) {
                if (item->data().getToVertex() == toVertex) {
                    edges.erase(item);
                    break;
                }
            }
        }

    };

    struct Edge {
        Vertex* toVertex;
        int weight;

        Edge() {
            toVertex = nullptr;
        }

        Edge(Vertex* toVertex) {
            this->toVertex = toVertex;
        }

        Vertex* getToVertex() {
            return toVertex;
        }

        void setWeight(int weight) {
            this->weight = weight;
        }

        int getWeight() {
            return weight;
        }
    };

    struct EdgeIterator {

        typename Edges::Item *edgeItem;

        EdgeIterator(Vertex* head) {
            edgeItem = head->edges.first();
        }

        void operator ++() {
            if (edgeItem != nullptr) {
                edgeItem = edgeItem->next();
            }
        }

        Edge operator *() {
            return edgeItem->data();
        }

        bool hasNext() {
            return edgeItem != nullptr;
        }
    };

    Graph(size_t numberVertex, Data data) {
        vertexex.resize(numberVertex);
        for (size_t i = 0; i < numberVertex; i++) {
            vertexex[i] = new Vertex(data);
        }
    }

    ~Graph() {
        for (int i = 0; i < vertexex.size(); i++) {
            delete vertexex[i];
        }
    }

    size_t sizeVertexex() {
        return vertexex.size();
    }

    bool checkEdge(Vertex* fromVertex, Vertex* toVertex) {
        for (auto item = fromVertex->edges.first(); item != nullptr; item = item->next()) {
            if (item->data().getToVertex() == toVertex) {
                return true;
            }
        }

        return false;
    }

    Vertex* addVertex(Data data) {
        auto vertex = new Vertex(data);
        vertexex.push_back(vertex);

        return vertex;
    }

    Vertex* getVertex(size_t index) {
        return vertexex[index];
    }

    void removeVertex(size_t index) {
        if (index < vertexex.size()) {
            for (int i = 0; i < vertexex.size(); i++) {
                vertexex[i]->removeEdge(vertexex[index]);
            }

            delete vertexex[index];
            for (int i = index + 1; i < vertexex.size(); i++) {
                vertexex[i - 1] = vertexex[i];
            }
            vertexex.pop_back();
        }
    }

    void setDataVertex(size_t index, Data data) {
        if (index >= vertexex.size()) return;

        vertexex[index]->setData(data);
    }

    Data getDataVertex(size_t index) {
        return vertexex[index]->getData();
    }

    void addEdge(Vertex* fromVertex, Vertex* toVertex, int weightEdge) {
        if (!checkEdge(fromVertex, toVertex)) fromVertex->addEdge(toVertex);

        if (!fromVertex->hasEdge(toVertex)) return;

        fromVertex->getEdge(toVertex).setWeight(weightEdge);
    }

    void setWeightEdge(Vertex* fromVertex, Vertex* toVertex, int weight) {
        if (!fromVertex->hasEdge(toVertex)) return;

        fromVertex->getEdge(toVertex).weight = weight;
    }

    int getWeightEdge(Vertex* fromVertex, Vertex* toVertex) {
        if (!fromVertex->hasEdge(toVertex)) return -1;

        return fromVertex->getEdge(toVertex).weight;
    }

    void removeEdge(Vertex* fromVertex, Vertex* toVertex) {
        fromVertex->removeEdge(toVertex);
    }

    size_t getIndexVertex(Vertex* vertex) {
        for (size_t i = 0; i < vertexex.size(); i++) {
            if (vertexex[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

private:
    std::vector<Vertex*> vertexex;
};

#endif