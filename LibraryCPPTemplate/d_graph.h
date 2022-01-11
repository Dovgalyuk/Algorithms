#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "array.h"

template <typename Data> class d_graph
{
public:
    struct Vertex;
    struct Edge;

    typedef Array<Vertex*> Vertices;
    typedef Array<Edge*> Edges;

    struct Vertex
    {
    public:
        Vertex(size_t vertexCount) {
            edges = new Edges(vertexCount);
            for (int i = 0; i < vertexCount; i++)
                edges->set(i, new Edge());
            data = 0;
        }

        ~Vertex() {
            for (size_t i = 0; i < edges->size(); i++)
                delete edges->get(i);
            delete edges;
        }

        Data getData() {
            return data;
        }

        void setData(Data newData) {
            data = newData;
        }

        void setEdge(size_t index, Data cost) {
            edges->set(index, new Edge(cost));
        }

        void addEdge() {
            edges->push_back(new Edge());
        }
        void removeEdge(size_t index) {
            edges->delete_index(index);
        }

        size_t size() {
            return edges->size();
        }

        void show_egdes() {
          for (int i = 0; i < edges->size(); i++)
              std::cout << edges->get(i)->weight << " ";
        }

        bool check_exist(size_t index) {
            return edges->get(index)->exist;
        }


        auto getWeight(size_t index) {
                return edges->get(index)->weight;  
        }


        Edges* edges;
        Data data;
    };

    struct Edge {
    public:
        Edge() {
            weight = 0;
            exist = false;
        }
        Edge(Data weight) {
            this->weight = weight;
            exist = true;
        }

        Data getData() {
            return weight;
        }

        Data weight;
        bool exist;
    };

   


    d_graph(int vertexCount) {
        this->vertexCount = vertexCount;
        vertices = new Vertices(vertexCount);
        for (int i = 0; i < vertexCount; i++)
            vertices->set(i, new Vertex(vertexCount));
    }

    ~d_graph() {
        for (int i = 0; i < vertexCount; i++)
            delete vertices->get(i);
        delete vertices;
    }


     size_t getVertexIndex(Vertex* vertex) {
         for (size_t i = 0; i < vertexCount; i++) {
             if (vertex == getVertex(i)) {
                 return i;
             }
         }
         return 0;
     }

     Vertex* getVertex(size_t index) {
             return vertices->get(index);
  
     }

    void setEdgetoVertex(size_t from, size_t to, Data weight) {
        getVertex(from)->setEdge(to, weight);
    }

    void setEdgeVertices(Vertex* from, size_t to, Data weight) {
        from->setEdge(to, weight);
    }

    void removeVertex(size_t index) {
        vertices->delete_index(index);
        vertexCount--;
        for (size_t i = 0; i < vertexCount; i++) {
            getVertex(i)->removeEdge(index);
        }
    }

    void setVertex(size_t index, Data data) {
        if (index >= vertexCount) return;

        if (vertices->get(index) != nullptr) {
            delete vertices->get(index);
        }

        vertices->set(index, new Vertex(vertexCount, data));
    }

    void setVertex(Vertex* vertex, size_t index) {
        if (index >= vertexCount) {
            addVertex();
        }
        vertices->set(index, vertex);
    }



    void addVertex() {
        vertices->push_back(new Vertex(vertexCount));
        vertexCount++;
        for (size_t i = 0; i < vertexCount; i++) {
            getVertex(i)->addEdge();
        }
    }


    Data GetDataVertex(size_t vertex) {
       return getVertex(vertex)->getData();
    }

    void SetDataVertex(size_t vertex, Data data) {
        getVertex(vertex)->setData(data);
    }



    bool checkEdge(size_t from, size_t to) {
        if (getVertex(from)->check_exist(to))
            return true;
            
        else
        return false;
    }

    bool checkEdge(Vertex* from, size_t to) {
        if (from->check_exist(to))
            return true;

        else
            return false;
    }


    void show() {
        std::cout << "----Edges:";
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << "Vertex " << i << ": ";
                getVertex(i)->show_egdes();
          std::cout<< std::endl;
        }
    }

    struct EdgesIterator {

    public:
        EdgesIterator(d_graph<Data>& graph, Vertex* it) {
            this->it = it;
            current = it;
            vertices = graph.vertices;
            current_pos = 0;
        }

        bool operator ++() {
            for (size_t i = current_pos+1; i < it->edges->size(); i++) {
                if (it->check_exist(i)){
                    current = vertices->get(i);
                    current_pos = i;
                    return true;
                }
            }
            return false;
        }

        Vertex* operator*() {
            if (it != nullptr) {
                return it;
            }
            else {
                return nullptr;
            }
        }

        Vertex* getIt() {
            return it;
        }
        Vertex* getCurrent() {
            return current;
        }
       

        auto getWeight() {
            return it->getWeight(current_pos);
        }
        size_t current_pos;

    private:
        Vertex* it;
        Vertex* current;
        Vertices* vertices;

    };

private:
    size_t vertexCount;
    Vertices* vertices;
};