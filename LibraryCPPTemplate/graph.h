#ifndef ALGORITHMS_DIRECTEDGRAPH_H
#define ALGORITHMS_DIRECTEDGRAPH_H

#include <iostream>
#include <vector>
#include "array.h"
#include <climits>

template<typename Data>
class Graph {
public:
    struct Vertex {
        Data data;

        Vertex() {
            this->data = 0;
        }

        Vertex(Data data) {
            this->data = data;
        }
    };

    struct Edge {
        size_t cost;

        Edge() {
            cost = 0;
        }

        Edge(size_t cost) {
            this->cost = cost;
        }
    };

    class NeighbourIterator {
    public:
        NeighbourIterator &next() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                if (!graph.isLinked(ownerIndex, i)) continue;
                current = i;
                break;
            }
            return *this;
        }

        NeighbourIterator &prev() {
            for (int i = current - 1; i < graph.vertexCount; i--) {
                if (!graph.isLinked(ownerIndex, i)) continue;
                current = i;
                break;
            }
            return *this;
        }

        bool hasNext() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                if (!graph.isLinked(ownerIndex, i)) continue;
                return true;
            }
            return false;
        }

        NeighbourIterator(Graph<Data> &_graph, int index) : graph(_graph) {
            this->ownerIndex = index;
            this->current = -1;
        }

        NeighbourIterator(Graph<Data> &_graph, int index, int current) : graph(_graph) {
            this->ownerIndex = index;
            this->current = current;
        }

        Vertex *operator*() {
            return graph.vertices->get(current);
        }

        NeighbourIterator &operator++() {
            return next();
        }

        NeighbourIterator &operator--() {
            return prev();
        }

        NeighbourIterator operator++(int) {
            next();
            Iterator it(graph, ownerIndex, current);
            return it;
        }

        NeighbourIterator operator--(int) {
            prev();
            Iterator it(graph, ownerIndex, current);
            return it;
        }

        int getCurrentIndex() {
            return current;
        }

    private:
        Graph<Data> &graph;
        int ownerIndex = -1;
        int current = -1;
    };

    ///

    class Iterator {
    public:
        Iterator &next() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                if (graph.vertices->get(i) == nullptr) continue;
                current = i;
                break;
            }
            return *this;
        }

        Iterator &prev() {
            for (int i = current - 1; i < graph.vertexCount; i--) {
                if (graph.vertices->get(i) == nullptr) continue;
                current = i;
                break;
            }
            return *this;
        }

        bool hasNext() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                if (graph.vertices->get(i) == nullptr) continue;
                return true;
            }
            return false;
        }

        Iterator(Graph<Data> &_graph) : graph(_graph) {
            current = -1;
        }

        Iterator(Graph<Data> &_graph, int current) : graph(_graph) {
            this->current = current;
        }

        Vertex *operator*() {
            return graph.vertices->get(current);
        }

        Iterator &operator++() {
            return next();
        }

        Iterator operator++(int) {
            next();
            Iterator it(graph, current);
            return it;
        }

        Iterator &operator--() {
            return prev();
        }

        Iterator operator--(int) {
            prev();
            Iterator it(graph, current);
            return it;
        }

        int getCurrentIndex() {
            return current;
        }

    private:
        Graph<Data> &graph;
        int current;
    };

    Iterator getIterator() {
        return Iterator(*this);
    }

    NeighbourIterator getNeighbourIterator(size_t index) {
        return NeighbourIterator(*this, index);
    }

    typedef Array<Edge *> MatrixArray;
    typedef Array<Vertex *> VertexArray;

    Graph(size_t vertexCount) {
        this->vertexCount = vertexCount;
        matrix = new MatrixArray(vertexCount * vertexCount);
        for (int i = 0; i < vertexCount * vertexCount; i++)
            matrix->set(i, nullptr);
        vertices = new VertexArray(vertexCount);
        for (int i = 0; i < vertexCount; i++)
            vertices->set(i, nullptr);
    }

    ~Graph() {
        for (int i = 0; i < vertexCount * vertexCount; i++)
            delete matrix->get(i);
        delete matrix;
        for (int i = 0; i < vertexCount; i++)
            delete vertices->get(i);
        delete vertices;
    }

//
    void addVertex(Data data) {
        copyArray(vertexCount + 1);
        setVertex(vertexCount - 1, data);
    }

    void setVertex(size_t index, Data data) {
        if (index >= vertexCount) return;
        if (vertices->get(index) != nullptr) {
            delete vertices->get(index);
        }
        vertices->set(index, new Vertex(data));
    }

    void removeVertex(size_t index) {
        int newSize = vertexCount - 1;
        delete vertices->get(index);
        vertices->set(index, nullptr);
        for (size_t i = index; i < newSize; i++) {
            vertices->set(i, vertices->get(i + 1));
        }

        for (size_t i = 0; i < newSize; i++) {
            for (size_t j = index; j < newSize; j++) {
                if (i == j) continue;
                if(i < index && j >= index) {
                    matrix->set(getIndex(i, j), matrix->get(getIndex(i, j + 1)));
                }
                else if(i >= index && j < index) {
                    matrix->set(getIndex(i, j), matrix->get(getIndex(i + 1, j)));
                }
                else if(i >= index && j >= index) {
                    matrix->set(getIndex(i, j), matrix->get(getIndex(i + 1, j + 1)));
                }
                // matrix->set(getIndex(i, j), matrix->get(getIndex(i + 1, j + 1)));
            }
        }
        copyArray(newSize);
    }

    void setEdge(size_t firstIndex, size_t secondIndex, size_t cost) {
        if (matrix->get(getIndex(firstIndex, secondIndex)) != nullptr) {
            removeEdge(firstIndex, secondIndex);
        }
        matrix->set(getIndex(firstIndex, secondIndex), new Edge(cost));
    }

    void removeEdge(size_t firstIndex, size_t secondIndex) {
        delete matrix->get(getIndex(firstIndex, secondIndex));
        matrix->set(getIndex(firstIndex, secondIndex), nullptr);
    }

    bool isLinked(size_t firstIndex, size_t secondIndex) {
        return getEdgeCost(firstIndex, secondIndex) != 0;
    }

    bool containsVertex(size_t index) {
        return index < vertices->size() && vertices->get(index) != nullptr;
    }

    Vertex *getVertex(size_t index) {
        return vertices->get(index);
    }

    size_t getEdgeCost(size_t firstIndex, size_t secondIndex) {
        if (matrix->get(getIndex(firstIndex, secondIndex)) == nullptr) return 0;
        return matrix->get(getIndex(firstIndex, secondIndex))->cost;
    }

    int getVertexCount() {
        return vertexCount;
    }

    void displayMatrix() {
        std::cout << std::endl;
        std::cout << "  |";
        for (int i = 0; i < vertexCount; i++)
            std::cout << i;
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << " |";
            for (int j = 0; j < vertexCount; j++) {
                if (matrix->get(getIndex(i, j)) != nullptr &&
                    matrix->get(getIndex(i, j))->cost != 0)
                    std::cout << matrix->get(getIndex(i, j))->cost;
                else
                    std::cout << 0;
            }
            std::cout << std::endl;
        }
    }

private:
    void copyArray(size_t newSize) {
        bool increase = newSize > vertexCount;

        auto newArray = new VertexArray(newSize);
        for (int i = 0; i < newSize; i++) {
            if (increase && i >= vertices->size()) {
                newArray->set(i, nullptr);
                continue;
            }
            newArray->set(i, vertices->get(i));
            if (i < vertices->size()) vertices->set(i, nullptr);
        }
        delete vertices;
        vertices = newArray;

        size_t matrixSize = newSize * newSize;
        auto newMatrix = new MatrixArray(matrixSize);
        for (int y = 0; y < newSize; y++) {
            for (int x = 0; x < newSize; x++) {
                if (increase && (x >= vertexCount || y >= vertexCount)) {
                    newMatrix->set(x + y * newSize, nullptr);
                    continue;
                }
                newMatrix->set(x + y * newSize, matrix->get(x + y * vertexCount));
                if (!(x >= vertexCount || y >= vertexCount)) matrix->set(x + y * vertexCount, nullptr);
            }
        }
        delete matrix;
        matrix = newMatrix;
        vertexCount = newSize;
    }

    inline int getIndex(const int first, const int second) {
        return first + second * vertexCount;
    }

    MatrixArray *matrix;
    VertexArray *vertices;
    size_t vertexCount;
};


#endif 