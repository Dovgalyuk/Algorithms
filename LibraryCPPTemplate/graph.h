#pragma once
#include <vector>
#include <string>
#include "list.h"
#include <iostream>


template<typename Data> class Graph
{
public:
    struct Vertex;
    struct Edge;

    Graph(size_t number, Data data = 0) {

        vertices.resize(number);
        for (size_t i = 0; i < number; i++) {
            vertices[i] = new Vertex(data);
        }
    }

    ~Graph() {
        for (size_t i = 0; i < vertices.size(); i++) {
            delete vertices[i];
        }
    }

    struct Vertex
    {
    public:
        List<Edge*>* edges = new List<Edge*>;

        Vertex(Data data) {
            this->data = data;
        }

        ~Vertex() {
            auto del = edges->first();
            while (del != nullptr) {
                delete del->data();
                del = del->next();
            }
            delete edges;
        }

        Data getData() {
            return data;
        }

        void setData(Data newData) {
            data = newData;
        }

        void addEdge(Vertex* to) {
            edges->insert(new Edge(to));
        }

        void removeEdge(Vertex* to) {
            for (auto item = edges->first(); item; item = item->next()) {
                if (item->data()->getDest() == to) {
                    delete item->data();
                    edges->erase(item);
                    break;
                }
            }
        }

        Edge* getEdge(Vertex* to) {
            for (auto item = edges->first(); item; item = item->next()) {
                if (item->data()->getDest() == to) {
                    return item->data();
                }
            }
            return nullptr;
        }
    private:
        Data data;
    };
    
    struct Edge
    {
    public:
        Edge(Vertex* dest) {
            this->dest = dest;
        }

        Vertex* getDest() {
            return dest;
        }

        int getWeight() {
            return weight;
        }

        void setWeight(int newWeight) {
            weight = newWeight;
        }
    private:
        Vertex* dest;
        int weight = NULL;
    };

    struct EdgesIterator {

        typename List<Edge*>::Item* currItem;
        EdgesIterator(Vertex* begin) {
            currItem = begin->edges->first();
        }

        void operator ++() {
            if (currItem != nullptr)
                currItem = currItem->next();
        }


        Edge* operator *() {
            if (currItem != nullptr) {
                return currItem->data();
            }
            else {
                return nullptr;
            }
        }

    };

    size_t addVertex() {
        vertices.push_back(new Vertex(0));
        return vertices.size() - 1;
    }

    Vertex* getVertex(size_t index) {
        return vertices[index];
    }
    void removeVertex(size_t index) {
        if (index < vertices.size()) {
            for (size_t i = 0; i < vertices.size(); i++) {
                vertices[i]->removeEdge(vertices[index]);
            }

            delete vertices[index];
            for (size_t i = index + 1; i < vertices.size(); i++) {
                vertices[i - 1] = vertices[i];
            }
            vertices.pop_back();
        }
    }
    bool isEdgeExists(size_t fromIndex , size_t toIndex) {
        Vertex* from = getVertex(fromIndex);
        Vertex* to = getVertex(toIndex);
        for (auto item = from->edges->first(); item; item = item->next()) {
            if (item->data()->getDest() == to) {
                return true;
            }
        }
        return false;
    }

    size_t size() {
        return vertices.size();
    }
   
    size_t getIndexOf(Vertex* vertex) {
        for (size_t i = 0; i < vertices.size(); i++)
        {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }
    void addEdgeFromTo(int firstVertex, int secondVertex) {
        getVertex(firstVertex)->addEdge(getVertex(secondVertex));
    }

    void addWeightToEdge(int firstVertex, int secondVertex, int Weight) {
        if (isEdgeExists(firstVertex, secondVertex))
           getVertex(firstVertex)->getEdge(getVertex(secondVertex))->setWeight(Weight);
    }

    void removeEdgeFromTo(int firstVertex, int secondVertex) {
        getVertex(firstVertex)->removeEdge(getVertex(secondVertex));
    }
private:
    std::vector<Vertex*> vertices;
};