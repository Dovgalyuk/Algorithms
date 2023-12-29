#include <stdexcept>
#include "vector.h" 

using namespace std;
template <typename T2>
class AdjacentVertexIterator {
private:
    Vector<T2>* adjMatrix;
    long unsigned int numVertices;
    long unsigned int currentVertex;
    const Vector<T2>* getAdjMatrix() const {
        return &adjMatrix;
    }
public:
    AdjacentVertexIterator(const Vector<T2>* adjMatrix, long unsigned int startVertex, long unsigned int numVertices)
        : adjMatrix(adjMatrix), numVertices(numVertices), currentVertex(startVertex) {}

    bool hasNext() {
        for (long unsigned int i = currentVertex; i < numVertices; i++) {
            if (adjMatrix->get(currentVertex * numVertices + i) != 0) {
                return true;
            }
        }
        return false;
    }

    long unsigned int next() {
        for (long unsigned int i = currentVertex; i < numVertices; i++) {
            if (adjMatrix->get(currentVertex * numVertices + i) != 0) {
                currentVertex = i;
                return i;
            }
        }
        return numVertices;
    }
};

template <typename T, typename T2>
class Graph {
private:
    Vector<T> vertices;
    Vector<T2> adjMatrix;
    long unsigned int numVertices;
    const Vector<T>* getVertices() const {
        return &vertices;
    }

    const Vector<T2>* getAdjMatrix() const {
        return &adjMatrix;
    }
public:

    Graph(int numVertices) : numVertices(numVertices) {
        vertices.resize(numVertices);
        adjMatrix.resize(numVertices * numVertices);
    }

    void addEdge(long unsigned int src, long unsigned int dest, int weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix.set(src * numVertices + dest, weight);
    }

    void setEdgeMark(long unsigned int src, long unsigned int dest, int weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix.set(src * numVertices + dest, weight);
    }

    void addVertex(T data) {
        vertices.resize(numVertices + 1);
        vertices.set(numVertices, data);
        numVertices++;
        adjMatrix.resize(numVertices * numVertices);
    }

    void removeEdge(long unsigned int src, long unsigned int dest) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix.set(src * numVertices + dest, 0);
        adjMatrix.set(dest * numVertices + src, 0);
    }

    bool EdgeExists(long unsigned int src, long unsigned int dest) const {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix.get(src * numVertices + dest) != 0;
    }

    T2 getEdgeWeight(long unsigned int src, long unsigned int dest)const {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix.get(src * numVertices + dest);
    }

    void setVertexMark(long unsigned int vertex, T data) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vertices.set(vertex, data);
    }

    T getVertexMark(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vertices.get(vertex);
    }

    void removeVertex(long unsigned int vertex) {

        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }


        for (long unsigned int i = vertex; i < numVertices - 1; i++) {
            for (long unsigned int j = 0; j < numVertices; j++) {
                adjMatrix.set(i * numVertices + j, adjMatrix.get((i + 1) * numVertices + j));
            }
        }for (long unsigned int i = 0; i < numVertices; i++) {
            for (long unsigned int j = vertex; j < numVertices - 1; j++) {
                adjMatrix.set(i * numVertices + j, adjMatrix.get(i * numVertices + j + 1));
            }
        }


        numVertices--;


        adjMatrix.resize(numVertices * numVertices);

        for (long unsigned int i = vertex; i < numVertices; i++)
            vertices.set(i, vertices.get(i + 1));


        vertices.resize(numVertices);
    }


    AdjacentVertexIterator getAdjacentVertices(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return AdjacentVertexIterator(getAdjMatrix(), vertex, numVertices);
    }
};