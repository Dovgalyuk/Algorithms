#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <iostream>
#include "list.h"
#include <vector>

template<typename Data, typename Weight>
class Graph{
public:
    class Edge;
    class Vertex{
    public:
        Vertex(Data data){
            this->data = data;
        }

        ~Vertex(){
            auto itemDel = edges.first();

            while(itemDel != nullptr) {
                delete itemDel->data();
                itemDel = itemDel->getNext();
            }
        }

        Data getData() {
            return data;
        }

        void addEdge(Vertex* v) {
            edges.insert(new Edge(v));
        }

        Edge* getEdge(Vertex* v) {
            for (auto item = edges.first(); item != nullptr; item = item->getNext()) {
                if (item->getData()->getToV() == v) {
                    return item->getData();
                }
            }

            return nullptr;
        }

        void removeEdge(Vertex* toVertex) {
            for (auto item = edges.first(); item != nullptr; item = item->getNext()) {
                if (item->data()->getToV() == toVertex) {
                    delete item->data();
                    edges.erase(item);
                    break;
                }
            }
        }

    List<Edge*> edges = List<Edge*>();
    Data data;
    public:
        void setData(Data data) {
            this->data = data;
        }

        std::vector<Edge*> getEdges(){
            std::vector<Edge*> edge;
            auto list = edges;
            int size = edges.getSize();
            for(auto item = list.first(); item != nullptr; item = item->getNext()){
                edge.push_back(item->getData());
            }
            return edge;
        }
    };
    class Edge{
        Vertex* v;
        Weight weight;
    public:
        void setWeight(int weight) {
            this->weight = weight;
        }

        Edge(Vertex* v) {
            this->v = v;
        }

        Vertex* getToV() {
            return v;
        }

        int getWeight() {
            return weight;
        }
    };

    ~Graph() {
        for (int i = 0; i < vertices.size(); i++) {
            delete vertices[i];
        }
    }

    bool checkEdge(Vertex* fromVertex, Vertex* toVertex) {
        for (int i = 0; i < fromVertex->getEdges().size(); i++) {
            if (fromVertex->getEdges().at(i)->getToV() == toVertex) {
                return true;
            }
        }

        return false;
    }
public:
    Vertex* addVertex(Data data) {
        auto vertex = new Vertex(data);
        vertices.push_back(vertex);
        return vertex;
    }

    void removeVertex(size_t index) {
        if (index < vertices.size()) {
            for (int i = 0; i < vertices.size(); i++) {
                vertices[i]->removeEdge(vertices[index]);
            }

            delete vertices[index];
            for (int i = index + 1; i < vertices.size(); i++) {
                vertices[i - 1] = vertices[i];
            }
            vertices.pop_back();
        }
    }

    void setDataVertex(size_t index, Data data) {
        if (index >= vertices.size()) return;

        vertices[index]->setData(data);
    }

    Data getDataVertex(size_t index) {
        return vertices[index]->getData();
    }

    Edge* getEdge (Vertex* u, Vertex* v) {
        return u->getEdge(v);
    }

    int getWeightEdge(Vertex* u, Vertex* v) {
        return getEdge(u, v)->getWeight();
    }

    void removeEdge(Vertex* u, Vertex* v) {
        u->removeEdge(v);
    }

    size_t getIndexVertex(Vertex* v) {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices[i] == v) {
                return i;
            }
        }

        return -1;
    }


    Graph(size_t numberVertex, Data data) {
        vertices.resize(numberVertex);
        for (size_t i = 0; i < numberVertex; i++) {
            vertices[i] = new Vertex(data);
        }
    }

    size_t sizeVertices() {
        return vertices.size();
    }

    Vertex* getVertex(size_t index) {
        return vertices[index];
    }

    void addEdge(Vertex* u, Vertex* v, int weightEdge) {
        if (!checkEdge(u, v)) {
            u->addEdge(v);
        }
        u->getEdge(v)->setWeight(weightEdge);
    }

private:
    std::vector<Vertex*> vertices;

};

#endif //ALGORITHMS_GRAPH_H
