#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "list.h"
#include "vector.h"
#include <cstddef>
#include <istream>
#include <string>
template <typename EdgeLabel, typename VertexLabel>
class Graph
{
    struct Edge
    {
        std::string to;
        EdgeLabel label;
        Edge(const std::string &to, const EdgeLabel &value) : to(to), label(value) {}
    };

    struct Vertex
    {
        std::string name;
        VertexLabel label;
        List<Edge> edges;
        Vertex(const std::string &vertexName, const VertexLabel &value) : name(vertexName), label(value) {}
    };

    using VertexItem = typename List<Vertex>::Item;
    using EdgeItem = typename List<Edge>::Item;
    List<Vertex> vertices_;

    VertexItem *find_vertex(const std::string &name)
    {
        for (VertexItem *item = vertices_.first(); item; item = item->next())
            if (item->data().name == name)
                return item;
        return nullptr;
    }

    const VertexItem *find_vertex(const std::string &name) const
    {
        for (const VertexItem *item = vertices_.first(); item; item = item->next())
            if (item->data().name == name)
                return item;
        return nullptr;
    }

    static EdgeItem *find_edge(VertexItem *vertex, const std::string &to)
    {
        if (!vertex)
            return nullptr;
        for (EdgeItem *item = vertex->data().edges.first(); item; item = item->next())
            if (item->data().to == to)
                return item;
        return nullptr;
    }

    static const EdgeItem *find_edge(const VertexItem *vertex, const std::string &to)
    {
        if (!vertex)
            return nullptr;
        for (const EdgeItem *item = vertex->data().edges.first(); item; item = item->next())
            if (item->data().to == to)
                return item;
        return nullptr;
    }

    void remove_to_edges(const std::string &name)
    {
        for (VertexItem *vertex = vertices_.first(); vertex; vertex = vertex->next())
        {
            List<Edge> &edges = vertex->data().edges;
            EdgeItem *prev = nullptr;
            EdgeItem *current = edges.first();
            while (current)
            {
                if (current->data().to == name)
                {
                    if (prev)
                        current = edges.erase_next(prev);
                    else
                        current = edges.erase_first();
                }
                else
                {
                    prev = current;
                    current = current->next();
                }
            }
        }
    }

public:
    class NeighborIterator
    {
        friend class Graph;
        const EdgeItem *current_;

        explicit NeighborIterator(const EdgeItem *item) : current_(item) {}

    public:
        NeighborIterator() : current_(nullptr) {}
        bool hasNext() const { return current_ != nullptr; }
        std::string next()
        {
            if (!current_) return std::string();
            std::string name = current_->data().to;
            current_ = current_->next();
            return name;
        }
    };

    Graph() = default;
    explicit Graph(std::size_t count) { resize(count); }
    Graph(std::size_t rows, std::size_t columns) { resize_grid(rows, columns); }

    std::size_t size() const
    {
        std::size_t count = 0;
        for (const VertexItem *item = vertices_.first(); item; item = item->next()){
            ++count;
        }
        return count;
    }

    bool has_vertex(const std::string &name) const { return find_vertex(name) != nullptr; }

    bool add_vertex(const std::string &name, const VertexLabel &label = VertexLabel())
    {
        if (has_vertex(name))
            return false;
        vertices_.insert_after(vertices_.last(), Vertex(name, label));
        return true;
    }

    bool remove_vertex(const std::string &name)
    {
        VertexItem *target = find_vertex(name);
        if (!target)
            return false;
        remove_to_edges(name);

        VertexItem *prev = nullptr;
        for (VertexItem *item = vertices_.first(); item; item = item->next())
        {
            if (item == target)
            {
                if (prev) vertices_.erase_next(prev);
                else
                    vertices_.erase_first();
                return true;
            }
            prev = item;
        }
        return false;
    }
    void resize(std::size_t count)
    {
        while (size() > count){
            remove_vertex(vertices_.first()->data().name);
        }
        std::size_t index = 0;
        while (size() < count) {
            const std::string name = "vertex_" + std::to_string(index++);
            if (!has_vertex(name)) add_vertex(name);
        }
    }
    void resize_grid(std::size_t rows, std::size_t columns)
    {
        while (vertices_.first()) {
            vertices_.erase_first();
        }
        for (std::size_t row = 0; row < rows; ++row) {
            for (std::size_t column = 0; column < columns; ++column) {
                add_vertex(std::to_string(row) + "_" + std::to_string(column));
        }
        }
    }

    bool add_edge(const std::string &from, const std::string &to, const EdgeLabel &label = EdgeLabel())
    {
        VertexItem *source = find_vertex(from);
        if (!source || !has_vertex(to) || find_edge(source, to)) return false;
        source->data().edges.insert_after(source->data().edges.last(), Edge(to, label));
        return true;
    }

    bool remove_edge(const std::string &from, const std::string &to)
    {
        VertexItem *source = find_vertex(from);
        EdgeItem *prev = nullptr;
        if (!source)
            return false;
        for (EdgeItem *edge = source->data().edges.first(); edge; edge = edge->next())
        {
            if (edge->data().to == to) {
                if (prev) source->data().edges.erase_next(prev);
                else
                    source->data().edges.erase_first();
                return true;
            }
            prev = edge;
        }
        return false;
    }

    bool has_edge(const std::string &from, const std::string &to) const
    {
        return find_edge(find_vertex(from), to) != nullptr;
    }

    bool set_vertex_label(const std::string &name, const VertexLabel &label)
    {
        VertexItem *vertex = find_vertex(name);
        if (!vertex) return false;
        vertex->data().label = label;
        return true;
    }

    bool get_vertex_label(const std::string &name, VertexLabel &label) const
    {
        const VertexItem *vertex = find_vertex(name);
        if (!vertex) return false;
        label = vertex->data().label;
        return true;
    }

    bool set_edge_label(const std::string &from, const std::string &to, const EdgeLabel &label)
    {
        EdgeItem *edge = find_edge(find_vertex(from), to);
        if (!edge) return false;
        edge->data().label = label;
        return true;
    }

    bool get_edge_label(const std::string &from, const std::string &to, EdgeLabel &label) const
    {
        const EdgeItem *edge = find_edge(find_vertex(from), to);
        if (!edge) return false;
        label = edge->data().label;
        return true;
    }

    Vector<VertexLabel> vertex_labels() const
    {
        Vector<VertexLabel> labels;
        labels.resize(size());
        std::size_t index = 0;
        for (const VertexItem *item = vertices_.first(); item; item = item->next()){
            labels.set(index++, item->data().label);
        }
        return labels;
    }

    NeighborIterator neighbors_begin(const std::string &name) const
    {
        const VertexItem *vertex = find_vertex(name);
        if (!vertex) return NeighborIterator();
        return NeighborIterator(vertex->data().edges.first());
    }
    bool read(std::istream &input)
    {
        std::size_t vertex_count, edge_count;
        if (!(input >> vertex_count >> edge_count)) return false;

        Graph parsed;
        for (std::size_t i = 0; i < vertex_count; i++)
        {
            std::string name;
            VertexLabel label{};
            if (!(input >> name >> label) || !parsed.add_vertex(name, label)) return false;
        }
        for (std::size_t i = 0; i < edge_count; i++)
        {
            std::string from, to;
            EdgeLabel label{};
            if (!(input >> from >> to >> label) || !parsed.add_edge(from, to, label)) return false;
        }
        *this = parsed;
        return true;
    }
};

#endif