#include <vector>
#include <stdexcept>
#include <map>
#include "vector.h"
using namespace std;
template <typename T>
class Graph {
private:
    Vector* vertices;
    Vector* adjMatrix;
    int numVertices;

public:
    Graph(int numVertices) : numVertices(numVertices) {
        vertices = vector_create(NULL);
        adjMatrix = vector_create(NULL);
        vector_resize(vertices, numVertices);
        vector_resize(adjMatrix, numVertices * numVertices);
    }

    void addEdge(long unsigned int src, long unsigned int dest, void* weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vector_set(adjMatrix, src * numVertices + dest, weight);
    }


    void setEdgeMark(long unsigned int src, long unsigned int dest, void* weight) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vector_set(adjMatrix, src * numVertices + dest, weight);
    }

    void addVertex(T data) {
        vector_resize(vertices, numVertices + 1);
        vector_set(vertices, numVertices, data);
        numVertices++;
        vector_resize(adjMatrix, numVertices * numVertices);
    }


    void removeEdge(long unsigned int src, long unsigned int dest) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vector_set(adjMatrix, src * numVertices + dest, (void*)0);
        vector_set(adjMatrix, dest * numVertices + src, (void*)0);
    }

    bool EdgeExists(long unsigned int src, long unsigned int dest) const {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vector_get(adjMatrix, src * numVertices + dest) != 0;
    }

    int getEdgeWeight(long unsigned int src, long unsigned int dest) {
        if (src >= numVertices || dest >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vector_get(adjMatrix, src * numVertices + dest);
    }

    void setVertexMark(long unsigned int vertex, T data) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vector_set(vertices, vertex, data);
    }

    T getVertexMark(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vector_get(vertices, vertex);
    }

    void removeVertex(long unsigned int vertex) {
        if (vertex >= numVertices) {
            throw std::out_of_range("Vertex does not exist");
        }
        vector_set(vertices, vertex, NULL);
        for (int i = vertex * numVertices; i < (vertex + 1) * numVertices; i++) {
            vector_set(adjMatrix, i, 0);
        }
        for (int i = vertex; i < numVertices - 1; i++) {
            vector_set(vertices, i, vector_get(vertices, i + 1));
        }
        numVertices--;
        vector_resize(adjMatrix, numVertices * numVertices);
    }

    const Vector* getAdjMatrix() const {
        return adjMatrix;
    }

    const Vector* getVertices() const {
        return vertices;
    }
};