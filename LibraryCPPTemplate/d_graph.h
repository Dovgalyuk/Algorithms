#pragma once
#include <vector>
#include <string>
#include "list.h"
#include <iostream>






template<typename Data> class D_Graph
{
    public:
    struct Vertex;
    struct Edge;

    D_Graph(size_t number, Data defaultValue) {
        maxVerticesNumber = number;
        vertices.resize(maxVerticesNumber);
        for (size_t i = 0; i < maxVerticesNumber; i++) {
            vertices[i] = new Vertex(defaultValue);
        }
    }
    D_Graph(const D_Graph& second) {
        maxVerticesNumber = second.maxVerticesNumber;
        vertices = second.vertices;
    }
    ~D_Graph() {
        for (int i = 0; i < vertices.size(); i++) {
            delete vertices[i];
        }
    }

    struct Vertex
    {
        public:
        Vertex(Data data) {
            this->data = data;
            label = 0;
        }
        ~Vertex() {
            auto mustBeDeleted = edges->first();
            while(mustBeDeleted != nullptr) {
                delete mustBeDeleted->data();
                mustBeDeleted = mustBeDeleted->next();
            }
            delete edges;
        }
        Data getData(){
            return data;
        }
        void setData(Data newData){
            data = newData;
        }


        void addEdgeTo(Vertex* to) {
            edges->insert(new Edge(to));
        }
        void removeEdgeTo(Vertex* to) {
            for (auto item = edges->first(); item; item = item->next()) {
                if (item->data()->getDest() == to) {
                    delete item->data();
                    edges->erase(item);
                    break;
                }
            }
        }
        Edge* getEdgeTo(Vertex* to) {
            for (auto item = edges->first(); item; item = item->next()) {
                if (item->data()->getDest() == to) {
                    return item->data();
                }
            }
            return nullptr;
        }
        int getLabel() {
            return label;
        }
        void setLabel(int newLabel) {
            label = newLabel;
        }
        List<Edge*> *edges = new List<Edge*>;
        private:
        Data data;
        int label;
    };

    struct Edge
    {
        public:
        Edge(Vertex* dest) {
            this->dest = dest;
        }
        int getWeight() {
            return weight;
        }
        void setWeight(int newWeight) {
            weight = newWeight;
        }
        Vertex* getDest() {
            return dest;
        }
        private:
        Vertex* dest;
        int weight;
    };
    
    struct EdgesIterator {
        
        typename List<Edge*>::Item *lastItem;
        EdgesIterator(Vertex* root) {    
            lastItem = root->edges->first();
        }

        void operator ++() {
            if (lastItem != nullptr)
                lastItem = lastItem->next();
        }

        
        Edge* operator*() {
            if (lastItem != nullptr) {
                return lastItem->data();
            }
            else {
                return nullptr;
            }
        }

        void refresh(Vertex* root) {
            lastItem = root->edges->first();
        }

    };

    size_t addVertex(Data data) {
        if (vertices.size() == maxVerticesNumber) {
            return -1;
        } 
        else {
            vertices.push_back(new Vertex(data));
            return vertices.size() - 1;
        }
    }
    size_t addVertex(Vertex* vertex) {
        if (vertices.size() == maxVerticesNumber) {
            return -1;
        }
        else {
            vertices.push_back(vertex);
            return vertices.size() - 1;
        }
    }
    void removeVertex(size_t index) {
        if (index < vertices.size()) {
            for (int i = 0; i < vertices.size(); i++) {
                vertices[i]->removeEdgeTo(vertices[index]);
            }

            delete vertices[index];
            for (int i = index+1; i < vertices.size(); i++) {
                vertices[i-1] = vertices[i];
            }
            vertices.pop_back();
        }
    }
    bool edgeExist(Vertex* from, Vertex* to) {
        for (auto item = from->edges->first(); item; item = item->next() ) {
            if (item->data()->getDest() == to) {
                return true;
            }
        }
        return false;
    }

    Vertex* getVertex(size_t index) {
        return vertices[index];
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

    private:
    int maxVerticesNumber;
    std::vector<Vertex*> vertices;



};