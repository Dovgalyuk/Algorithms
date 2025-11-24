#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <vector>
#include <list.h>

template <typename V, typename E> class Graph
{
public:
    struct Edge
    {
        size_t to;

        Edge(size_t to): to(to) {}

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
        edges.push_back(std::make_pair(std::make_pair(from, to), E()));
    }

    void setEdgeTag(size_t from, size_t to, E tag)
    {
        if(from >= vertexs.size() || to >= vertexs.size()) 
        {
            return;
        }

        if(!hasEdge(from, to))
        {
            return;
        }

        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first.first == from && edges[i].first.second == to)
            {
                edges[i].second = tag;
                break;
            }
        }
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

        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first.first == from && edges[i].first.second == to)
            {
                return edges[i].second;
            }
        }

        return E();
    }

    bool hasEdge(size_t from, size_t to)
    {   
        for(size_t i = 0; i < edges.size(); i++)
        {
            if(edges[i].first.first == from && edges[i].first.second == to)
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

        for(size_t i = 0; i < edges.size(); i++) 
        {
            if(edges[i].first.first == from && edges[i].first.second == to)
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
                removeEdge(i, vertex);  
                removeEdge(vertex, i);
            }
        }

        vertexs.erase(vertexs.begin() + vertex);
        adjacency_list.erase(adjacency_list.begin() + vertex);
    }

private:
    std::vector<V> vertexs;
    std::vector<std::pair<std::pair<size_t, size_t>, E>> edges;
    std::vector<List<Edge>> adjacency_list;
};

#endif