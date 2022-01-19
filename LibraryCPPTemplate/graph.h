#include <iostream>
#include "array.h"
 
template <typename Data> class _Graph {
public:
    struct Vertex;
    struct Edge;
 
    typedef Array<Vertex*> Vertices;
    typedef Array<Edge*> Edges;
 
    struct Vertex {
    public:
        Vertex() {
            data = 0;
        }
 
        Data getData() {
            return data;
        }
 
        void setData(Data newData) {
            data = newData;
        }
 
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
 
    _Graph(int _vertexCount) {
        vertexCount = _vertexCount;
        vertices = new Vertices(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            vertices->set(i, new Vertex());
        }

        edges = new Edges(vertexCount*vertexCount);
        for (int i = 0; i < vertexCount * vertexCount; i++) {
            edges->set(i, nullptr);
        }
    }
 
    ~_Graph() {
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
 
    void setEdgeToVertex(size_t from, size_t to_vert, Data weight) {
        edges->set(from + to_vert * vertexCount, new Edge(weight));
    }
 
    void removeVertex(size_t index) {
        vertices->delete_index(index);
        vertexCount--;
        for (size_t i = 0; i < vertexCount; i++) {
            getVertex(i)->removeEdge(index);
        }
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
 
    bool checkEdge(size_t from, size_t to_vert) {
        auto result = edges->get(from + to_vert * vertexCount);
        if (result == nullptr) return false;
 
        return result->exist;
    }
 
    int getWeight(size_t from, size_t to_vert) {
        auto result = edges->get(from + to_vert * vertexCount);
        if (result == nullptr) return -1;
 
        return result->weight;
    }
 
    void showGraph() {
        std::cout << "   Edges: ";
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << "Vertex " << i << ": ";
            for (int j = 0; j < vertexCount; j++) {
                if (!checkEdge(i, j)) {
                    std::cout<< 0 << " ";
                    continue;
                }
                std::cout << edges->get(i + j * vertexCount)->weight << " ";
            }
            std::cout<< std::endl;
        }
    }
 
    struct EdgesIterator {
 
    public:
        EdgesIterator(_Graph<Data>* _graph, int itIndex) {
            this->itIndex = itIndex;
            current = itIndex;
            graph = _graph;
        }
 
        bool operator ++() {
            for (size_t i = current + 1; i < graph->vertexCount; i++) {
                if (!graph->checkEdge(itIndex, i)) continue;
                current = i;
                return true;
            }
            return false;
        }
 
        Vertex* operator*() {
            auto result = graph->getVertex(itIndex);
            return result;
        }
 
        Vertex* getIt() {
            return graph->getVertex(itIndex);
        }
 
        Vertex* getCurrent() {
            return graph->getVertex(current);
        }
 
        auto getWeight() {
            return graph->getWeight(itIndex, current);
        }
 
    private:
        int itIndex;
        int current;
 
        _Graph<Data>* graph;
    };
 
private:
    Edges* edges;
 
    size_t vertexCount;
    Vertices* vertices;
};