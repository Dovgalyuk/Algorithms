#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <vector>

template<typename Data> class Graph 
{
    public:

        struct Edge;

        struct Vertex 
        {
            Data data;
            List<Edge*> edges = List<Edge*>();
      
            Vertex(Data VertexData): data(VertexData) {}

            ~Vertex() 
            {
                auto Del = edges.first();

                while(Del != nullptr) 
                {
                    delete Del->data();
                    Del = Del->next();
                }
            }

            void SetData(Data data_) 
            {
                data = data_;
            }

            Data GetData() 
            {
                return data;
            }

            void AddEdge(Vertex* toVertex) 
            {
                edges.insert(new Edge(toVertex));
            }

            Edge* GetEdge(Vertex* toVertex) 
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

            void RemoveEdge(Vertex* toVertex) 
            {
                for (auto i = edges->first(); i; i = i->next()) 
                {
                    if (i->data()->getToVertex() == toVertex) 
                    {
                        delete i->data();
                        edges->erase(i);
                        break;
                    }
                }
            }
        };

        struct Edge 
        {
            Vertex* toVertex;
            int weight = 0;

            Edge(Vertex* toVertex): toVertex(toVertex) {}

            Vertex* GetToVertex() 
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
            typename List<Edge*>::Item * edgeElem;

            EdgeIterator(Vertex* head) 
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
                VertexVec[i] = new Vertex(data);
            }
        }

        ~Graph() 
        {
            for (int i = 0; i < VertexVec.size(); i++)
            {
                delete VertexVec[i];
            }
        }

        size_t SizeVertexVec()
        {
            return VertexVec.size();
        }
        
        bool AvailabilityLink(Vertex* fromVertex, Vertex* toVertex)                 
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

        Vertex* AddVertex(Vertex* data) 
        {
            auto* vertex = new Vertex(data);
            VertexVec.push_back(vertex);

            return vertex;
        }

        Vertex* GetVertex(size_t index) 
        {
            return VertexVec[index];
        }

        void RemoveVertex(size_t index) 
        {
            if (index < VertexVec.size())
            {
                for (int i = 0; i < VertexVec.size(); i++)
                {
                    VertexVec[i]->removeEdge(VertexVec[index]);
                }

                delete VertexVec[index];
                for (int i = index + 1; i < VertexVec.size(); i++)
                {
                    VertexVec[i-1] = VertexVec[i];
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
        
        void AddEdge(Vertex* fromVertex, Vertex* toVertex, int weightEdge) 
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

        Edge* GetEdge (Vertex* fromVertex, Vertex* toVertex) 
        {
            return fromVertex->GetEdge(toVertex);
        }

        int GetWeightEdge(Vertex* fromVertex, Vertex* toVertex) 
        {
            return fromVertex->GetEdge(toVertex)->GetWeight();
        }

        void RemoveEdge(Vertex* fromVertex, Vertex* toVertex) 
        {
            fromVertex->RemoveEdge(toVertex);
        }

        size_t GetIndexVertex(Vertex* vertex) 
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
        std::vector<Vertex*> VertexVec;
};
#endif
