#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <vector>

template<typename Data> class Graph
{
public:

    Data data;

    struct Edge;

    List<Edge*> edges;

    struct Edge
    {
        Graph* toVertex;
        int weight = 0;

        Edge(Graph* toVertex) : toVertex(toVertex) {}

        Graph* GetToVertex()
        {
            return toVertex;
        }

        void SetWeight(int weight_)
        {
            weight = weight_;
        }

        int GetWeight()
        {
            return weight;
        }
    };

    struct EdgeIterator
    {
        typename List<Edge*>::Item* edgeElem;

        EdgeIterator(Graph* head)
        {
            edgeElem = head->edges.first();
        }

        void operator ++()
        {
            if (edgeElem != nullptr)
            {
                edgeElem = edgeElem->next();
            }
        }

        Edge* operator *()
        {
            if (edgeElem != nullptr)
            {
                return edgeElem->data();
            }
            else
            {
                return nullptr;
            }
        }
    };

    Graph(size_t VertexNumber, Data data)
    {
        VertexVec.resize(VertexNumber);
        for (size_t i = 0; i < VertexNumber; i++)
        {
            VertexVec[i] = new Graph(data);
        }
    }

    Graph(Data VertexData) : data(VertexData) {}

    ~Graph()
    {
        for (int i = 0; i < VertexVec.size(); i++)
        {
            delete VertexVec[i];
        }

        auto Del = edges.first();

        while (Del != nullptr)
        {
            delete Del->data();
            Del = Del->next();
        }
    }

    size_t SizeVertexVec()
    {
        return VertexVec.size();
    }

    bool AvailabilityLink(Graph* fromVertex, Graph* toVertex)
    {
        for (auto i = fromVertex->edges.first(); i != nullptr; i = i->next())
        {
            if (i->data()->GetToVertex() == toVertex)
            {
                return true;
            }
        }
        return false;
    }

    Graph* AddVertex(Graph* data)
    {
        auto* vertex = new Graph(data);
        VertexVec.push_back(vertex);

        return vertex;
    }

    Graph* GetVertex(size_t index)
    {
        return VertexVec[index];
    }

    void RemoveVertex(size_t index)
    {
        if (index < VertexVec.size())
        {
            for (int i = 0; i < VertexVec.size(); i++)
            {
                VertexVec[i]->RemoveEdge(VertexVec[index]);
            }

            delete VertexVec[index];
            for (int i = index + 1; i < VertexVec.size(); i++)
            {
                VertexVec[i - 1] = VertexVec[i];
            }
            VertexVec.pop_back();
        }
    }

    void SetVertexData(size_t index, Data data)
    {
        VertexVec[index]->SetData(data);
    }

    Data GetVertexData(size_t index)
    {
        return VertexVec[index]->GetData();
    }
   
    void AddEdge(Graph* fromVertex, Graph* toVertex, int weightEdge)
    {

        if (AvailabilityLink(fromVertex, toVertex))
        {
            fromVertex->GetEdge(toVertex)->SetWeight(weightEdge);
        }
        else
        {
            fromVertex->AddEdge(toVertex);
            fromVertex->GetEdge(toVertex)->SetWeight(weightEdge);
        }
    }

    Edge* GetEdge(Graph* fromVertex, Graph* toVertex)
    {
        return fromVertex->GetEdge(toVertex);
    }

    int GetWeightEdge(Graph* fromVertex, Graph* toVertex)
    {
        return fromVertex->GetEdge(toVertex)->GetWeight();
    }

    void RemoveEdge(Graph* fromVertex, Graph* toVertex)
    {
        fromVertex->RemoveEdge(toVertex);
    }

    size_t GetIndexVertex(Graph* vertex)
    {
        for (size_t i = 0; i < VertexVec.size(); i++)
        {
            if (VertexVec[i] == vertex)
            {
                return i;
            }
        }

        return -1;
    }

private:
    std::vector<Graph*> VertexVec;

    void SetData(Data data_)
    {
        data = data_;
    }

    Data GetData()
    {
        return data;
    }

    void AddEdge(Graph* toVertex)
    {
        edges.insert(new Edge(toVertex));
    }

    Edge* GetEdge(Graph* toVertex)
    {
        for (auto i = edges.first(); i; i = i->next())
        {
            if (i->data()->GetToVertex() == toVertex)
            {
                return i->data();
            }
        }
        return nullptr;
    }

    void RemoveEdge(Graph* toVertex)
    {
        for (auto i = edges.first(); i; i = i->next())
        {
            if (i->data()->GetToVertex() == toVertex)
            {
                delete i->data();
                edges.erase(i);
                break;
            }
        }
    }
};
#endif
