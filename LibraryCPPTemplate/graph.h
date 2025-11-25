#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"
#include "list.h"

template <typename V, typename E> class Graph
{
public:
    struct Edge
    {
        size_t to;
        E tag;

        Edge(size_t to): to(to), tag(E()) {}

        bool operator==(Edge& other)
        {
            return to == other.to;
        }
    };

    struct Iterator
    {
        typename List<Edge>::Item* current;

        Iterator(typename List<Edge>::Item* start) : current(start) {}

        Iterator& operator++() 
        {
            if (current != nullptr) 
            {
                current = current->next();
            }

            return *this;
        }
    
        int operator*()
        {
            return current->data().to;
        }
    
        bool operator==(Iterator& other) 
        {
            return current == other.current;
        }
    
        bool operator!=(Iterator& other)
        {
            return current != other.current;
        }
    };

    Iterator begin(size_t vertex) 
    {
        return Iterator(adjacency_list[vertex].first());
    }

    Iterator end(size_t vertex) 
    {
        return Iterator(nullptr);
    }

    Graph(size_t size): vertexs(size), adjacency_list(size)
    {
        for(size_t i = 0; i < size; i++){
            vertexs[i] = V();
        }
    }

    void addVertex()
    {
        vertexs.push_back(V());
        adjacency_list.push_back(List<Edge>());
    }

    void setVertexTag(size_t index, V& tag)
    {
        if(index >= vertexs.size())
        {
            return;
        }

        vertexs[index] = tag;
    }

    V getVertexTag(size_t index)
    {
        if(index >= vertexs.size())
        {
            return V();
        }

        return vertexs[index];
    }

    void addEdge(size_t from, size_t to)
    {
        if(from >= vertexs.size() || to >= vertexs.size()) 
        {
            return;
        }
        
        Edge edge(to);
        adjacency_list[from].insert(edge);
    }

    void setEdgeTag(size_t from, size_t to, E tag)
    {
        if(from >= vertexs.size() || to >= vertexs.size()) 
        {
            return;
        }

        removeEdge(from, to);
    
        Edge new_edge(to);
        new_edge.tag = tag;
        adjacency_list[from].insert(new_edge);
    }

    E getEdgeTag(size_t from, size_t to)
    {
        if(from >= vertexs.size() || to >= vertexs.size()) 
        {
            return E();
        }

        if(!hasEdge(from, to))
        {
            return E();
        }

        typename List<Edge>::Item* current = adjacency_list[from].first();
        while(current != nullptr) 
        {
            if(current->data().to == to)
            {
                return current->data().tag;
            }

            current = current->next();
        }

        return E();
    }

    bool hasEdge(size_t from, size_t to)
    {   
        typename List<Edge>::Item* current = adjacency_list[from].first();
        while(current != nullptr) 
        {
            if(current->data().to == to)
            {
                return true;
            }

            current = current->next();
        }

        return false;
    }

    Vector<V> getVertexTags()
    {
        return vertexs;
    }

    void removeEdge(size_t from, size_t to)
    {
        if(!hasEdge(from, to))
        {
            return;
        }

        typename List<Edge>::Item* current = adjacency_list[from].first();
        typename List<Edge>::Item* prev = nullptr;

        while(current != nullptr) 
        {
            if(current->data().to == to) 
            {
                if(prev == nullptr) 
                {
                    adjacency_list[from].erase_first();
                } 
                else 
                {
                    adjacency_list[from].erase_next(prev);
                }

                break;
            }

            prev = current;
            current = current->next();
        }
    }

    void removeVertex(size_t vertex)
    {
        if(vertex >= vertexs.size())
        {
            return;
        }

        for(size_t i = 0; i < vertexs.size(); i++) 
        {
            if(i != vertex) 
            {
                removeEdge(i, vertex);  
                removeEdge(vertex, i);
            }
        }

        vertexs.erase(vertex);
        adjacency_list.erase(vertex);
    }

private:
    Vector<V> vertexs;
    Vector<List<Edge>> adjacency_list;
};

#endif