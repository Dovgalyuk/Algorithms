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
    struct Vertex;

    struct Edge
    {
        std::size_t to_id;
        EdgeLabel label;
        Edge(std::size_t to_id, const EdgeLabel &value) : to_id(to_id), label(value) {}
    };

    struct Vertex
    {
        std::size_t id;
        std::string name;
        VertexLabel label;
        List<Edge> edges;
        Vertex(std::size_t vertex_id, const std::string &vertex_name, const VertexLabel &value) : id(vertex_id), name(vertex_name), label(value) {}
    };

    using EdgeList = List<Edge>;
    using VertexItem = typename List<Vertex>::Item;
    using EdgeItem = typename List<Edge>::Item;

    List<Vertex> vertices_;
    std::size_t next_vertex_id_ = 0;

    VertexItem *find_vertex(const std::string &name) {
        for (VertexItem *item = vertices_.first(); item; item = item->next()){
            if (item->data().name == name) return item;
        }
        return nullptr;
    }

    const VertexItem *find_vertex(const std::string &name) const
    {
        for (const VertexItem *item = vertices_.first(); item; item = item->next()){
            if (item->data().name == name) return item;
        }
        return nullptr;
    }

    const VertexItem *find_vertex_by_id(std::size_t id) const
    {
        for (const VertexItem *item = vertices_.first(); item; item = item->next()){
            if (item->data().id == id) return item;
        }
        return nullptr;
    }

    static EdgeItem *find_edge(VertexItem *vertex, std::size_t to_id)
    {
        if (!vertex) return nullptr;
        for (EdgeItem *item = vertex->data().edges.first(); item; item = item->next()){
            if (item->data().to_id == to_id) return item;
        }
        return nullptr;
    }

    static const EdgeItem *find_edge(const VertexItem *vertex, std::size_t to_id)
    {
        if (!vertex) return nullptr;
        for (const EdgeItem *item = vertex->data().edges.first(); item; item = item->next()){
            if (item->data().to_id == to_id) return item;
        }
        return nullptr;
    }

    void remove_to_edges(std::size_t id)
    {
        for (VertexItem *vertex = vertices_.first(); vertex; vertex = vertex->next())
        {
            EdgeList &edges = vertex->data().edges;
            EdgeItem *previous = nullptr;
            EdgeItem *current = edges.first();
            while (current) {
                if (current->data().to_id == id) {
                    current = edges.erase_next(previous);
                }
                else {
                    previous = current;
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
        const VertexItem *vertices_;

        NeighborIterator(const EdgeItem *edge, const VertexItem *vertices) : current_(edge), vertices_(vertices) {}

    public:
        NeighborIterator() : current_(nullptr), vertices_(nullptr) {}

        bool hasNext() const { return current_ != nullptr; }

        std::string next()
        {
            if (!current_) return std::string();

            const std::size_t to_id = current_->data().to_id;
            current_ = current_->next();
            for (const VertexItem *vertex = vertices_; vertex; vertex = vertex->next()){
                if (vertex->data().id == to_id) return vertex->data().name;
            }
            return std::string();
        }
    };

    Graph() = default;
    explicit Graph(std::size_t count) { resize(count); }
    Graph(std::size_t rows, std::size_t columns) { resize_grid(rows, columns); }

    std::size_t size() const
    {
        std::size_t count = 0;
        for (const VertexItem *item = vertices_.first(); item; item = item->next()){
            count++;
        }
        return count;
    }

    bool has_vertex(const std::string &name) const { return find_vertex(name) != nullptr; }

    bool add_vertex(const std::string &name, const VertexLabel &label = VertexLabel())
    {
        if (has_vertex(name)) return false;
        vertices_.insert_after(vertices_.last(), Vertex(next_vertex_id_++, name, label));
        return true;
    }

    bool remove_vertex(const std::string &name)
    {
        VertexItem *target = find_vertex(name);
        if (!target) return false;
        remove_to_edges(target->data().id);

        VertexItem *previous = nullptr;
        for (VertexItem *item = vertices_.first(); item; item = item->next())
        {
            if (item == target) {
                if (previous) vertices_.erase_next(previous);
                else
                    vertices_.erase_first();
                return true;
            }
            previous = item;
        }
        return false;
    }

    void resize(std::size_t count)
    {
        while (size() > count) {
            const std::string last_vertex = vertices_.last()->data().name;
            remove_vertex(last_vertex);
        }

        std::size_t index = 0;
        while (size() < count)
        {
            const std::string name = "vertex_" + std::to_string(index++);
            if (!has_vertex(name)) add_vertex(name);
        }
    }

    void resize_grid(std::size_t rows, std::size_t columns)
    {
        resize(0);
        for (std::size_t row = 0; row < rows; row++) {
            for (std::size_t column = 0; column < columns; column++){
                add_vertex(std::to_string(row) + "_" + std::to_string(column));
            }
        }
    }

    bool add_edge(const std::string &from, const std::string &to, const EdgeLabel &label = EdgeLabel())
    {
        VertexItem *source = find_vertex(from);
        const VertexItem *destination = find_vertex(to);
        if (!source || !destination || find_edge(source, destination->data().id))
            return false;
        source->data().edges.insert_after(source->data().edges.last(), Edge(destination->data().id, label));
        return true;
    }

    bool remove_edge(const std::string &from, const std::string &to)
    {
        if (!has_edge(from, to)) return false;

        VertexItem *source = find_vertex(from);
        const VertexItem *destination = find_vertex(to);
        EdgeItem *previous = nullptr;

        for (EdgeItem *edge = source->data().edges.first(); edge; edge = edge->next()) {
            if (edge->data().to_id == destination->data().id) {
                source->data().edges.erase_next(previous);
                return true;
            }
            previous = edge;
        }

        return false;
    }

    bool has_edge(const std::string &from, const std::string &to) const
    {
        const VertexItem *source = find_vertex(from);
        const VertexItem *destination = find_vertex(to);
        if (!source || !destination) return false;
        return find_edge(source, destination->data().id) != nullptr;
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
        const VertexItem *destination = find_vertex(to);
        if (!destination) return false;
        EdgeItem *edge = find_edge(find_vertex(from), destination->data().id);
        if (!edge) return false;
        edge->data().label = label;
        return true;
    }

    bool get_edge_label(const std::string &from, const std::string &to, EdgeLabel &label) const
    {
        const VertexItem *destination = find_vertex(to);
        if (!destination) return false;
        const EdgeItem *edge = find_edge(find_vertex(from), destination->data().id);
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
        return NeighborIterator(vertex->data().edges.first(), vertices_.first());
    }

    bool read(std::istream &input)
    {
        std::size_t vertex_count, edge_count;
        if (!(input >> vertex_count >> edge_count)) return false;

        Graph parsed;
        for (std::size_t i = 0; i < vertex_count; i++) {
            std::string name;
            VertexLabel label{};
            if (!(input >> name >> label) || !parsed.add_vertex(name, label))
                return false;
        }
        for (std::size_t i = 0; i < edge_count; i++) {
            std::string from, to;
            EdgeLabel label{};
            if (!(input >> from >> to >> label) || !parsed.add_edge(from, to, label))
                return false;
        }
        *this = parsed;
        return true;
    }
};

#endif

