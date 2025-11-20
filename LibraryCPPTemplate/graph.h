#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <vector>
#include <list.h>

template <typename V, typename E> class Graph
{
public:
    struct Edge
    {
        size_t from, to;

        Edge(size_t from, size_t to): from(from), to(to) {}

        bool operator==(Edge& other)
        {
            return from == other.from && to == other.to;
        }
    };

    struct Iterator
    {
        List<int>::Item* current;

        Iterator(List<int>::Item* start) : current(start) {}

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
            return current->data();
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
        adjacency_list.push_back(List<int>());
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

    void addEdge(Edge& edge)
    {
        if(edge.from >= vertexs.size() || edge.to >= vertexs.size()) 
        {
            return;
        }
        
        adjacency_list[edge.from].insert(edge.to);
        edges.push_back(std::make_pair(edge, E()));
    }

    void setEdgeTag(Edge& edge, E tag)
    {
        if(edge.from >= vertexs.size() || edge.to >= vertexs.size()) 
        {
            return;
        }

        if(!hasEdge(edge))
        {
            return;
        }

        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first == edge)
            {
                edges[i].second = tag;
                break;
            }
        }
    }

    E getEdgeTag(Edge& edge)
    {
        if(edge.from >= vertexs.size() || edge.to >= vertexs.size()) 
        {
            return E();
        }

        if(!hasEdge(edge))
        {
            return E();
        }

        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first == edge)
            {
                return edges[i].second;
            }
        }

        return E();
    }

    bool hasEdge(Edge& edge)
    {   
        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first == edge)
            {
                return true;
            }
        }

        return false;
    }

    std::vector<V> getVertexTags()
    {
        return vertexs;
    }

    void removeEdge(Edge& edge)
    {
        if(!hasEdge(edge))
        {
            return;
        }

        List<int>::Item* current = adjacency_list[edge.from].first();
        List<int>::Item* prev = nullptr;

        while(current != nullptr) 
        {
            if((size_t)current->data() == edge.to) 
            {
                if(prev == nullptr) 
                {
                    adjacency_list[edge.from].erase_first();
                } 
                else 
                {
                    adjacency_list[edge.from].erase_next(prev);
                }

                break;
            }

            prev = current;
            current = current->next();
        }

        for(size_t i = 0; i < edges.size(); i++) 
        {
            if(edges[i].first == edge) 
            {
                edges.erase(edges.begin() + i);
                break;
            }
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
                Edge edge1(i, vertex);
                Edge edge2(vertex, i);
                removeEdge(edge1);  
                removeEdge(edge2);
            }
        }

        vertexs.erase(vertexs.begin() + vertex);
        adjacency_list.erase(adjacency_list.begin() + vertex);
    }

private:
    std::vector<V> vertexs;
    std::vector<std::pair<Edge, E>>edges;
    std::vector<List<int>> adjacency_list;
};

#endif