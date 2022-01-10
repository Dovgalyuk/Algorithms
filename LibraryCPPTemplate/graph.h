#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "list.h"
#include <vector>

template<typename Data>
class Graph {
public:
    struct Edge;
    struct Vertex {
        Data data;
        List<Edge*> edges = List<Edge*>();

        Vertex(Data data) {
            this->data = data;
        }

        ~Vertex() {
            auto itemDel = edges.first();

            while(itemDel != nullptr) {
                delete itemDel->data();
                itemDel = itemDel->next();
            }
        }

        void setData(Data data) {
            this->data = data;
        }

        Data getData() {
            return data;
        }

        void addEdge(Vertex* toVertex) {
            edges.insert(new Edge(toVertex));
        }

        Edge* getEdge(Vertex* toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->next()) {
                if (item->data()->getToVertex() == toVertex) {
                    return item->data();
                }
            }

            return nullptr;
        }

        void removeEdge(Vertex* toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->next()) {
                if (item->data()->getToVertex() == toVertex) {
                    delete item->data();
                    edges.erase(item);
                    break;
                }
            }
        }

    };

    struct Edge {
        Vertex* toVertex;
        int weight;

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

        typename List<Edge*>::Item *edgeItem;

        EdgeIterator(Vertex* head) {
            edgeItem = head->edges.first();
        }

        void operator ++() {
            if (edgeItem != nullptr) {
                edgeItem = edgeItem->next();
            }
        }

        Edge* operator *() {
            if (edgeItem != nullptr) {
                return edgeItem->data();
            } else {
                return nullptr;
            }
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
            if (item->data()->getToVertex() == toVertex) {
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
        fromVertex->getEdge(toVertex)->setWeight(weightEdge);
    }

    Edge* getEdge (Vertex* fromVertex, Vertex* toVertex) {
        return fromVertex->getEdge(toVertex);
    }

    int getWeightEdge(Vertex* fromVertex, Vertex* toVertex) {
        return getEdge(fromVertex, toVertex)->getWeight();
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