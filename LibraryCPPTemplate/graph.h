#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <istream>
#include <stdexcept>

#include "list.h"
#include "vector.h"

using namespace std;

template <typename EdgeLabel, typename VertexLabel> class Graph
{
private:
    struct Edge
    {
        size_t to;
        EdgeLabel label;
    };

    typedef List<Edge> EdgeList;
    typedef typename EdgeList::Item EdgeItem;

    struct Vertex
    {
        VertexLabel label;
        EdgeList edges;
    };

    Vector<Vertex> vertices;

    void check_vertex(size_t vertex) const
    {
        if (vertex >= size())
            throw out_of_range("Graph vertex");
    }

    EdgeItem *find_edge(size_t from, size_t to)
    {
        check_vertex(from);
        check_vertex(to);
        for (EdgeItem *item = vertices[from].edges.first(); item != nullptr; item = item->next())
            if (item->data().to == to)
                return item;
        return nullptr;
    }

    const EdgeItem *find_edge(size_t from, size_t to) const
    {
        check_vertex(from);
        check_vertex(to);
        for (const EdgeItem *item = vertices[from].edges.first(); item != nullptr; item = item->next())
            if (item->data().to == to)
                return item;
        return nullptr;
    }

public:
    struct Iterator
    {
        const EdgeItem *item;

        bool valid() const
        {
            return item != nullptr;
        }

        void next()
        {
            if (item != nullptr)
                item = item->next();
        }

        size_t vertex() const
        {
            if (!valid())
                throw out_of_range("Graph iterator");
            return item->data().to;
        }

        const EdgeLabel &label() const
        {
            if (!valid())
                throw out_of_range("Graph iterator");
            return item->data().label;
        }
    };

    explicit Graph(size_t count = 0)
    {
        vertices.resize(count);
    }

    size_t size() const
    {
        return vertices.size();
    }

    size_t add_vertex(VertexLabel label = VertexLabel())
    {
        size_t index = size();
        vertices.resize(index + 1);
        vertices[index].label = label;
        return index;
    }

    void remove_vertex(size_t vertex)
    {
        check_vertex(vertex);
        for (size_t from = 0; from < size(); ++from)
        {
            EdgeList &edges = vertices[from].edges;
            EdgeItem *previous = nullptr;
            EdgeItem *item = edges.first();
            while (item != nullptr)
            {
                if (item->data().to == vertex)
                    item = edges.erase_next(previous);
                else
                {
                    if (item->data().to > vertex)
                        --item->data().to;
                    previous = item;
                    item = item->next();
                }
            }
        }

        for (size_t i = vertex + 1; i < size(); ++i)
            vertices[i - 1] = vertices[i];
        vertices.resize(size() - 1);
    }

    bool add_edge(size_t from, size_t to, const EdgeLabel &label = EdgeLabel())
    {
        if (find_edge(from, to) != nullptr)
            return false;
        vertices[from].edges.insert_after(vertices[from].edges.last(), Edge{to, label});
        return true;
    }

    bool remove_edge(size_t from, size_t to)
    {
        check_vertex(from);
        check_vertex(to);
        EdgeList &edges = vertices[from].edges;
        EdgeItem *previous = nullptr;
        for (EdgeItem *item = edges.first(); item != nullptr; item = item->next())
        {
            if (item->data().to == to)
            {
                edges.erase_next(previous);
                return true;
            }
            previous = item;
        }
        return false;
    }

    bool has_edge(size_t from, size_t to) const
    {
        return find_edge(from, to) != nullptr;
    }

    const EdgeLabel &get_edge(size_t from, size_t to) const
    {
        const EdgeItem *item = find_edge(from, to);
        if (item == nullptr)
            throw out_of_range("Graph edge");
        return item->data().label;
    }

    void set_edge(size_t from, size_t to, const EdgeLabel &label)
    {
        EdgeItem *item = find_edge(from, to);
        if (item == nullptr)
            throw out_of_range("Graph edge");
        item->data().label = label;
    }

    const VertexLabel &get_vertex(size_t vertex) const
    {
        check_vertex(vertex);
        return vertices[vertex].label;
    }

    void set_vertex(size_t vertex, const VertexLabel &label)
    {
        check_vertex(vertex);
        vertices[vertex].label = label;
    }

    Vector<VertexLabel> get_vertices() const
    {
        Vector<VertexLabel> labels;
        labels.resize(size());
        for (size_t i = 0; i < size(); ++i)
            labels[i] = vertices[i].label;
        return labels;
    }

    size_t find_vertex(const VertexLabel &label) const
    {
        for (size_t i = 0; i < size(); ++i)
            if (vertices[i].label == label)
                return i;
        return size();
    }

    Iterator neighbors(size_t vertex) const
    {
        check_vertex(vertex);
        return Iterator{vertices[vertex].edges.first()};
    }

    void read(istream &input)
    {
        int count, edges;
        if (!(input >> count >> edges) || count < 0 || edges < 0)
            throw invalid_argument("Invalid graph size");

        Graph result;
        for (int i = 0; i < count; ++i)
        {
            VertexLabel label;
            if (!(input >> label) || result.find_vertex(label) != result.size())
                throw invalid_argument("Invalid vertex name");
            result.add_vertex(label);
        }

        for (int i = 0; i < edges; ++i)
        {
            VertexLabel from, to;
            EdgeLabel label;
            if (!(input >> from >> to >> label))
                throw invalid_argument("Invalid edge");
            size_t first = result.find_vertex(from);
            size_t second = result.find_vertex(to);
            if (first == result.size() || second == result.size() || !result.add_edge(first, second, label))
                throw invalid_argument("Invalid edge endpoints or duplicate edge");
        }
        *this = result;
    }
};

#endif
