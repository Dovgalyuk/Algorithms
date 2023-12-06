#include <stdexcept>
#include "vector.h" 

using namespace std;

template <typename T>
class Graph {
private:
    Vector<T>* vertices;
    Vector<int>* adjMatrix;
    long unsigned int numVertices;

public:
    Graph(int numVertices) : numVertices(numVertices) {
        vertices = new Vector<T>;
        adjMatrix = new Vector<int>;
        vertices->resize(numVertices);
        adjMatrix->resize(numVertices * numVertices);
    }

    void addEdge(long unsigned int src, long unsigned int dest, int weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix->set(src * numVertices + dest, weight);
    }

    void setEdgeMark(long unsigned int src, long unsigned int dest, int weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix->set(src * numVertices + dest, weight);
    }

    void addVertex(T data) {
        vertices->resize(numVertices + 1);
        vertices->set(numVertices, data);
        numVertices++;
        adjMatrix->resize(numVertices * numVertices);
    }

    void removeEdge(long unsigned int src, long unsigned int dest) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix->set(src * numVertices + dest, 0);
        adjMatrix->set(dest * numVertices + src, 0);
    }

    bool EdgeExists(long unsigned int src, long unsigned int dest) const {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix->get(src * numVertices + dest) != 0;
    }

    int getEdgeWeight(long unsigned int src, long unsigned int dest) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix->get(src * numVertices + dest);
    }

    void setVertexMark(long unsigned int vertex, T data) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vertices->set(vertex, data);
    }

    int getVertexMark(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vertices->get(vertex);
    }

    void removeVertex(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vertices->set(vertex, NULL);
        for (long unsigned int i = vertex * numVertices; i < (vertex + 1) * numVertices; i++) {
            adjMatrix->set(i, 0);
        }
        for (long unsigned int i = vertex; i < numVertices - 1; i++) {
            vertices->set(i, vertices->get(i + 1));
        }
        numVertices--;
        adjMatrix->resize(numVertices * numVertices);
    }

    const Vector<T>* getVertices() const {
        return vertices;
    }

    const Vector<int>* getAdjMatrix() const {
        return adjMatrix;
    }
};