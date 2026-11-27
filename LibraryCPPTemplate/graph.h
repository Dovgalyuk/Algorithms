#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "list.h"

template <typename VertexData, typename EdgeData>
class Graph
{
public:
    struct Edge
    {
        std::string to;
        EdgeData data{};
    };

    struct Vertex
    {
        VertexData data{};
        List<Edge> edges;
    };

    class NeighborIterator
    {
    public:
        NeighborIterator(typename List<Edge>::Item *current = nullptr)
            : current_(current)
        {
        }

        bool has_next() const
        {
            return current_ != nullptr;
        }

        void next()
        {
            if (current_)
                current_ = current_->next();
        }

        NeighborIterator &operator++()
        {
            next();
            return *this;
        }

        bool operator==(const NeighborIterator &other) const
        {
            return current_ == other.current_;
        }

        bool operator!=(const NeighborIterator &other) const
        {
            return current_ != other.current_;
        }

        const std::string &to() const
        {
            return current_->data().to;
        }

        EdgeData &data()
        {
            return current_->data().data;
        }

        const EdgeData &data() const
        {
            return current_->data().data;
        }

    private:
        typename List<Edge>::Item *current_ = nullptr;
    };

    Graph() = default;

    explicit Graph(size_t vertex_count)
    {
        resize(vertex_count);
    }

    Graph(size_t rows, size_t cols, bool connect_grid_edges = false, EdgeData default_edge_data = EdgeData())
    {
        resize_grid(rows, cols, connect_grid_edges, default_edge_data);
    }

    void clear()
    {
        vertices.clear();
    }

    size_t vertex_count() const
    {
        return vertices.size();
    }

    bool has_vertex(const std::string &name) const
    {
        return vertices.find(name) != vertices.end();
    }

    bool add_vertex(const std::string &name, const VertexData &data = VertexData())
    {
        if (has_vertex(name))
            return false;
        vertices[name].data = data;
        return true;
    }

    void resize(size_t vertex_count)
    {
        clear();
        for (size_t i = 0; i < vertex_count; ++i)
            add_vertex(std::to_string(i));
    }

    void resize_grid(size_t rows, size_t cols, bool connect = false, EdgeData d = EdgeData())
    {
        clear();
        for (size_t r = 0; r < rows; ++r)
            for (size_t c = 0; c < cols; ++c)
                add_vertex(grid_name(r, c));

        if (connect)
        {
            for (size_t r = 0; r < rows; ++r)
            {
                for (size_t c = 0; c < cols; ++c)
                {
                    std::string from = grid_name(r, c);
                    if (r + 1 < rows) add_edge(from, grid_name(r + 1, c), d);
                    if (r > 0) add_edge(from, grid_name(r - 1, c), d);
                    if (c + 1 < cols) add_edge(from, grid_name(r, c + 1), d);
                    if (c > 0) add_edge(from, grid_name(r, c - 1), d);
                }
            }
        }
    }

    bool remove_vertex(const std::string &name)
    {
        if (vertices.find(name) == vertices.end())
            return false;

        for (auto &pair : vertices)
        {
            if (pair.first != name)
                remove_edge(pair.first, name);
        }

        vertices.erase(name);
        return true;
    }

    bool add_edge(const std::string &from, const std::string &to, const EdgeData &data = EdgeData())
    {
        if (!has_vertex(from) || !has_vertex(to))
            return false;

        for (auto item = vertices[from].edges.first(); item; item = item->next())
        {
            if (item->data().to == to)
            {
                item->data().data = data;
                return true;
            }
        }

        vertices[from].edges.insert(Edge{to, data});
        return true;
    }

    bool remove_edge(const std::string &from, const std::string &to)
    {
        auto it = vertices.find(from);
        if (it == vertices.end() || !has_vertex(to))
            return false;

        for (auto item = it->second.edges.first(); item; item = item->next())
        {
            if (item->data().to == to)
            {
                it->second.edges.erase(item);
                return true;
            }
        }
        return false;
    }

    bool has_edge(const std::string &from, const std::string &to) const
    {
        auto it = vertices.find(from);
        if (it == vertices.end() || !has_vertex(to))
            return false;

        for (auto item = it->second.edges.first(); item; item = item->next())
        {
            if (item->data().to == to)
                return true;
        }
        return false;
    }

    void set_edge_data(const std::string &from, const std::string &to, const EdgeData &data)
    {
        get_edge_data(from, to) = data;
    }

    EdgeData &get_edge_data(const std::string &from, const std::string &to)
    {
        auto it = vertices.find(from);
        if (it == vertices.end() || !has_vertex(to))
            throw std::runtime_error("Vertex not found");

        for (auto item = it->second.edges.first(); item; item = item->next())
        {
            if (item->data().to == to)
                return item->data().data;
        }
        throw std::runtime_error("Edge not found");
    }

    const EdgeData &get_edge_data(const std::string &from, const std::string &to) const
    {
        auto it = vertices.find(from);
        if (it == vertices.end() || !has_vertex(to))
            throw std::runtime_error("Vertex not found");

        for (auto item = it->second.edges.first(); item; item = item->next())
        {
            if (item->data().to == to)
                return item->data().data;
        }
        throw std::runtime_error("Edge not found");
    }

    void set_vertex_data(const std::string &name, const VertexData &data)
    {
        get_vertex_data(name) = data;
    }

    VertexData &get_vertex_data(const std::string &name)
    {
        auto it = vertices.find(name);
        if (it == vertices.end())
            throw std::runtime_error("Vertex not found");
        return it->second.data;
    }

    const VertexData &get_vertex_data(const std::string &name) const
    {
        auto it = vertices.find(name);
        if (it == vertices.end())
            throw std::runtime_error("Vertex not found");
        return it->second.data;
    }

    std::vector<VertexData> get_all_vertex_data() const
    {
        std::vector<VertexData> result;
        result.reserve(vertices.size());
        for (const auto &pair : vertices)
            result.push_back(pair.second.data);
        return result;
    }

    std::vector<std::string> get_vertex_names() const
    {
        std::vector<std::string> result;
        result.reserve(vertices.size());
        for (const auto &pair : vertices)
            result.push_back(pair.first);
        return result;
    }

    NeighborIterator get_neighbors(const std::string &name)
    {
        auto it = vertices.find(name);
        if (it == vertices.end())
            return NeighborIterator(nullptr);
        return NeighborIterator(it->second.edges.first());
    }

    NeighborIterator get_neighbors(const std::string &name) const
    {
        auto it = vertices.find(name);
        if (it == vertices.end())
            return NeighborIterator(nullptr);
        return NeighborIterator(const_cast<List<Edge>&>(it->second.edges).first());
    }

    void read(std::istream &in)
    {
        clear();
        size_t v_count = 0;
        if (!(in >> v_count))
            return;

        for (size_t i = 0; i < v_count; ++i)
        {
            std::string name;
            in >> name;
            add_vertex(name);
        }

        size_t e_count = 0;
        if (!(in >> e_count))
            return;

        for (size_t i = 0; i < e_count; ++i)
        {
            std::string from, to;
            EdgeData d;
            in >> from >> to >> d;
            add_edge(from, to, d);
        }
    }

private:
    std::unordered_map<std::string, Vertex> vertices;

    static std::string grid_name(size_t r, size_t c)
    {
        return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
    }
};

#endif
