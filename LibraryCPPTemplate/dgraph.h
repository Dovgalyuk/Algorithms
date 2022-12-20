#ifndef DGRAPH_TEMPLATE_H
#define DGRAPH_TEMPLATE_H

#include <vector>
#include "vector.h"

template <typename Data> class DGraph 
{
public:
    struct Vertex
    {
        Data data;
        Vertex(Data data) : data(data) {}
    };

    struct Edge
    {
        Vertex* vertex;
        int weight;
        Edge(Vertex* vertex, int weight) : vertex(vertex), weight(weight) {}
    };

    struct VertexIterator
    {
        DGraph* graph = nullptr;
        size_t index_next_item = 0;

        VertexIterator(DGraph* graph) : graph(graph) {}

        Vertex* operator *()
        {
            return index_next_item < graph->vertices->size() ? graph->get_vertex(index_next_item) : nullptr;
        }

        void operator ++(int i)
        {
            index_next_item++;
        }
    };

    struct NearVertexIterator
    {
        DGraph* graph = nullptr;
        size_t root_vertex = 0;
        int last_index = -1;

        NearVertexIterator(DGraph* graph, size_t root_vertex) : graph(graph), root_vertex(root_vertex) { last_index = find_next_vertex(); }

        int find_next_vertex()
        {
            for (int i = last_index + 1; i < graph->get_vertex_amount(); ++i)
            {
                if (graph->contains_edge_between_vertices(root_vertex, i))
                {
                    return i;
                }
            }
            return -1;
        }

        Vertex* operator *()
        {
            return last_index != -1 ? graph->get_vertex(last_index) : nullptr;
        }

        void operator ++(int i)
        {
            last_index = find_next_vertex();
        }
    };

    Vector<Vertex*>* vertices;

    DGraph(size_t vertex_amount, Data default_value) : matrix(new Vector<Edge>)
    {
        vertices = new Vector<Vertex*>;
        vertices->resize(vertex_amount);
        for (int i = 0; i < vertex_amount; ++i)
        {
            vertices->set(i, new Vertex(default_value));
        }
        matrix->resize(vertex_amount * vertex_amount);
        fill_matrix_with_null();
    }

    ~DGraph()
    {
        delete matrix;
        delete vertices;
    }

    size_t add_vertex(Data data)
    {
        return add_vertex(new Vertex(data));
    }

    size_t add_vertex(Vertex* vertex)
    {
        size_t index = vertices->size();
        vertices->resize(index + 1);
        vertices->set(index, vertex);
        add_vertex_to_matrix(index);
        return index;
    }

    void add_edge(size_t first_vertex_index, size_t second_vertex_index, int weight)
    {
        Edge edge = Edge(get_vertex(second_vertex_index), weight);
        add_edge_to_matrix(first_vertex_index, second_vertex_index, edge);
    }

    void remove_vertex(size_t index)
    {
        if (index >= vertices->size()) return;
        int size = vertices->size();
        for (int i = 0; i < size - 1; ++i) {
            vertices->set(i, vertices->get(i + (i >= index)));
        }
        vertices->resize(size - 1);
        remove_vertex_from_matrix(index, size);
    }

    void remove_edge(size_t first_vertex_index, size_t second_vertex_index)
    {
        remove_edge_from_matrix(first_vertex_index, second_vertex_index);
    }

    Vertex* get_vertex(size_t index)
    {
        return vertices->get(index);
    }

    Data get_vertex_data(size_t index)
    {
        return vertices->get(index)->data;
    }

    size_t get_vertex_amount()
    {
        return vertices->size();
    }

    Edge get_edge(size_t first_vertex_index, size_t second_vertex_index)
    {
        return get_edge_from_matrix(first_vertex_index, second_vertex_index);
    }

    int get_edge_weight(size_t first_vertex_index, size_t second_vertex_index)
    {
        int weight = get_edge(first_vertex_index, second_vertex_index).weight;
        return weight;
    }

    void set_vertex(size_t index, Data data)
    {
        set_vertex(index, new Vertex(data));
    }

    void set_vertex(size_t index, Vertex* vertex)
    {
        if (index >= vertices->size()) return;
        vertices->set(index, vertex);
    }

    void set_vertex_data(size_t index, Data data)
    {
        vertices->get(index)->data = data;
    }

    void set_edge_weight(size_t first_vertex_index, size_t second_vertex_index, int weight)
    {
        Edge edge = get_edge(first_vertex_index, second_vertex_index);
        edge.weight = weight;
    }

    bool contains_edge_between_vertices(size_t first_vertex_index, size_t second_vertex_index)
    {
        Edge* edge = new Edge(get_edge_from_matrix(first_vertex_index, second_vertex_index));
        return edge != nullptr;
    }

    VertexIterator get_vertex_iterator()
    {
        return VertexIterator(this);
    }

    NearVertexIterator get_near_vertex_iterator(size_t root_index)
    {
        return NearVertexIterator(this, root_index);
    }
protected:
    Vector<Edge>* matrix;

    void fill_matrix_with_null()
    {
        for (int i = 0; i < matrix->size(); ++i)
        {
            Edge edge;
            matrix->set(i, edge);
        }
    }

    void remove_vertex_from_matrix(size_t removed_vertex_index, int amount_vertex_in_matrix)
    {
        int vertex_amount = get_vertex_amount();
        Vector<Edge>* new_matrix = new Vector<Edge>;
        new_matrix->resize(vertex_amount * vertex_amount);
        for (int i = 0; i < vertex_amount; ++i)
        {
            for (int j = 0; j < vertex_amount; ++j)
            {
                Edge edge = matrix->get(((i + (i >= removed_vertex_index)) * amount_vertex_in_matrix) + (j + (j >= removed_vertex_index)));
                new_matrix->set((i * vertex_amount) + j, edge);
            }
        }
        delete matrix;
        matrix = new_matrix;
    }

    void add_vertex_to_matrix(int amount_vertex_in_matrix)
    {
        int vertex_amount = get_vertex_amount();
        Vector<Edge>* new_matrix = new Vector<Edge>;
        new_matrix->resize(vertex_amount * vertex_amount);
        for (int i = 0; i < amount_vertex_in_matrix; ++i)
        {
            for (int j = 0; j < amount_vertex_in_matrix; ++j)
            {
                new_matrix->set((i * vertex_amount) + j, matrix->get(i * amount_vertex_in_matrix + j));
            }
        }
        delete matrix;
        matrix = new_matrix;
    }

    size_t get_edge_index_in_matrix(size_t first_vertex_index, size_t second_vertex_index)
    {
        return first_vertex_index * get_vertex_amount() + second_vertex_index;
    }

    void add_edge_to_matrix(size_t first_vertex_index, size_t second_vertex_index, Edge edge)
    {
        matrix->set(get_edge_index_in_matrix(first_vertex_index, second_vertex_index), edge);
    }

    void remove_edge_from_matrix(size_t first_vertex_index, size_t second_vertex_index)
    {
        matrix->set(get_edge_index_in_matrix(first_vertex_index, second_vertex_index), nullptr);
    }

    Edge get_edge_from_matrix(size_t first_vertex_index, size_t second_vertex_index)
    {
        return matrix->get(get_edge_index_in_matrix(first_vertex_index, second_vertex_index));
    }
};
#endif
