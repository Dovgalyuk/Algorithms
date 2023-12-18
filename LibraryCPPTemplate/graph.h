#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "list.h"

template <typename VertexLabel, typename EdgeLabel> class Graph
{
public:
    struct Edge {
        int to;
        EdgeLabel weight;
        Edge() : to(-1), weight(EdgeLabel()) {}
        Edge(int to, EdgeLabel weight) : to(to), weight(weight) {}
    };
    Graph(int vertexCount) : vertexCount_(vertexCount) {
        vertexLabels_ = new VertexLabel[vertexCount_];
        adjacencyList_ = new List<Edge>[vertexCount_];
    }

    Graph(Graph& other) : vertexCount_(other.vertexCount_) {
        vertexLabels_ = new VertexLabel[vertexCount_];
        for (int i = 0; i < vertexCount_; i++) {
            vertexLabels_[i] = other.vertexLabels_[i];
            adjacencyList_[i] = other.adjacencyList_[i];
        }
    }

    Graph& operator=(Graph& other) {
        if (this != &other) {
            delete[] vertexLabels_;
            delete[] adjacencyList_;
            vertexCount_ = other.vertexCount_;
            vertexLabels_ = new VertexLabel[vertexCount_];
            adjacencyList_ = new List<Edge>[vertexCount_];
            for (int i = 0; i < vertexCount_; i++) {
                vertexLabels_[i] = other.vertexLabels_[i];
                adjacencyList_[i] = other.adjacencyList_[i];
            }
        }
        return *this;
    }

    ~Graph()
    {
        delete[] adjacencyList_;
        delete[] vertexData_;
    }

    List<Edge>& adjacencyList(int vertex) { return adjacencyList_[vertex]; }
    VertexLabel& vertexLabel(int vertex) { return vertexLabels_[vertex]; }

    void addVertex()
    {
        List<Edge>* newAdjacencyList = new List<Edge>[vertexCount_ + 1];
        for (int i = 0; i < vertexCount_; i++)
            newAdjacencyList[i] = adjacencyList_[i];
        delete[] adjacencyList_;
        adjacencyList_ = newAdjacencyList;
        vertexCount_++;
    }

    void addEdge(int from, int to, EdgeLabel weight)
    {
        if (from >= 0 && from < vertexCount_ && to >= 0 && to < vertexCount_)
            adjacencyList_[from].insert(Edge(to, weight));
    }

    void removeVertex(int vertex)
    {
        if (vertex < 0 || vertex >= vertexCount_)
            return;

        List<Edge>* newAdjacencyList = new List<Edge>[vertexCount_ - 1];

        for (int i = 0, j = 0; i < vertexCount_; i++)
        {
            if (i != vertex)
            {
                newAdjacencyList[j] = adjacencyList_[i];

                auto item = newAdjacencyList[j].first();
                typename List<Edge>::Item* prevItem = nullptr;
                while (item != nullptr)
                {
                    if (item->data().to == vertex)
                    {
                        if (prevItem == nullptr) { item = newAdjacencyList[j].erase_first(); }
                        else { item = newAdjacencyList[j].erase_next(prevItem); }
                    }
                    else
                    {
                        prevItem = item;
                        item = item->next();
                    }
                }
                j++;
            }
        }

        delete[] adjacencyList_;
        adjacencyList_ = newAdjacencyList;
        --vertexCount_;
    }

    void removeEdge(int from, int to) {
        if (from < 0 || from >= vertexCount_) return;
        typename List<Edge>::Item* prevItem = nullptr;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next()) {
            if (item->data().to == to)
            {
                if (prevItem == nullptr) { adjacencyList_[from].erase_first(); }
                else { adjacencyList_[from].erase_next(prevItem); }
                break;
            }
            prevItem = item;
        }
    }

    bool hasEdge(int from, int to)
    {
        if (from < 0 || from >= vertexCount_)
            return false;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next())
        {
            if (item->data().to == to)
                return true;
        }
        return false;
    }

    void setEdgeData(int from, int to, EdgeLabel data)
    {
        if (from < 0 || from >= vertexCount_)
            return;
        typename List<Edge>::Item* prev = nullptr;
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next())
        {
            if (item->data().to == to)
            {
                if (prev == nullptr)
                {
                    adjacencyList_[from].erase_first();
                    adjacencyList_[from].insert(Edge(to, data));
                }
                else
                {
                    adjacencyList_[from].erase_next(prev);
                    adjacencyList_[from].insert_after(prev, Edge(to, data));
                }
                break;
            }
            prev = item;
        }
    }

    Data getEdgeData(int from, int to)
    {
        if (from < 0 || from >= vertexCount_)
            return Data();
        for (auto item = adjacencyList_[from].first(); item != nullptr; item = item->next())
        {
            if (item->data().to == to)
            {
                return item->data().weight;
            }
        }
        return Data();
    }

    void setVertexData(int vertex, VertexLabel data) { if (vertex >= 0 && vertex < vertexCount_) { vertexData_[vertex] = data; } }

    Data getVertexData(int vertex)
    {
        if (vertex >= 0 && vertex < vertexCount_)
            return vertexData_[vertex];
        return Data();
    }

    int vertexCount() { return vertexCount_; }

    class NeighborIterator
    {
    public:
        NeighborIterator(Graph* graph, int vertex) : graph_(graph), vertex_(vertex), currentItem_(nullptr)
        {
            if (vertex >= 0 && vertex < graph->vertexCount_)
            {
                currentItem_ = graph->adjacencyList_[vertex].first();
            }
        }
        void next() { if (currentItem_ != nullptr) { currentItem_ = currentItem_->next(); } }
        bool hasNext() { return currentItem_ != nullptr; }
        Edge current()
        {
            if (currentItem_ != nullptr)
                return currentItem_->data();
            return Edge();
        }

    private:
        Graph* graph_;
        int vertex_;
        typename List<Edge>::Item* currentItem_;
    };

private:
    List<Edge>* adjacencyList_;
    int vertexCount_;
    VertexLabel* vertexData_;
};

#endif
