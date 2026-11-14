#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include <string>
#include <utility>
#include <vector>
#include "list.h"
#include "vector.h"

// First template parameter is the edge mark (e.g. weight), second is vertex mark.
template <typename EdgeData, typename VertexData> class Graph
{
    struct Edge { size_t to; EdgeData mark; Edge(size_t v, EdgeData m) : to(v), mark(m) {} };
    struct Vertex { std::string name; VertexData mark; List<Edge> edges; Vertex(std::string n, VertexData m) : name(n), mark(m) {} };
public:
    class Iterator
    {
    public:
        Iterator() : graph(nullptr), item(nullptr) {}
        bool valid() const { return item != nullptr; }
        void next() { if (item) item = item->next(); }
        std::string vertex_name() const { return valid() ? graph->vertices[item->data().to].name : std::string(); }
        EdgeData edge_mark() const { return valid() ? item->data().mark : EdgeData(); }
    private:
        Iterator(const Graph *g, const typename List<Edge>::Item *i) : graph(g), item(i) {}
        const Graph *graph;
        const typename List<Edge>::Item *item;
        friend class Graph<EdgeData, VertexData>;
    };

    Graph() = default;
    explicit Graph(size_t count) { resize(count); }
    Graph(size_t rows, size_t columns)
    {
        for (size_t r = 0; r < rows; r++) for (size_t c = 0; c < columns; c++)
            add_vertex("(" + std::to_string(r) + "," + std::to_string(c) + ")", VertexData());
    }

    size_t size() const { return vertices.size(); }
    void resize(size_t count)
    {
        while (vertices.size() > count) remove_vertex(vertices.back().name);
        while (vertices.size() < count) add_vertex("v" + std::to_string(vertices.size()), VertexData());
    }
    bool add_vertex(const std::string &name, const VertexData &mark = VertexData())
    {
        if (vertex_index(name) != invalid()) return false;
        vertices.emplace_back(name, mark);
        return true;
    }
    bool remove_vertex(const std::string &name)
    {
        size_t id = vertex_index(name);
        if (id == invalid()) return false;
        vertices.erase(vertices.begin() + id);
        for (auto &v : vertices) {
            auto i = v.edges.first();
            while (i) {
                if (i->data().to == id) i = v.edges.erase_next(i->prev());
                else { if (i->data().to > id) { Edge e(i->data().to - 1, i->data().mark); i->data() = e; } i = i->next(); }
            }
        }
        return true;
    }
    bool add_edge(const std::string &from, const std::string &to, const EdgeData &mark)
    {
        size_t a = vertex_index(from), b = vertex_index(to);
        if (a == invalid() || b == invalid()) return false;
        for (auto i = vertices[a].edges.first(); i; i = i->next()) if (i->data().to == b) { i->data().mark = mark; return true; }
        vertices[a].edges.insert(Edge(b, mark));
        return true;
    }
    bool remove_edge(const std::string &from, const std::string &to)
    {
        size_t a = vertex_index(from), b = vertex_index(to);
        if (a == invalid() || b == invalid()) return false;
        for (auto i = vertices[a].edges.first(); i; i = i->next()) if (i->data().to == b) { vertices[a].edges.erase_next(i->prev()); return true; }
        return false;
    }
    bool has_edge(const std::string &from, const std::string &to) const
    {
        size_t a = vertex_index(from), b = vertex_index(to);
        if (a == invalid() || b == invalid()) return false;
        for (auto i = vertices[a].edges.first(); i; i = i->next()) if (i->data().to == b) return true;
        return false;
    }
    bool set_edge_mark(const std::string &from, const std::string &to, const EdgeData &mark)
    { return has_edge(from, to) && add_edge(from, to, mark); }
    EdgeData edge_mark(const std::string &from, const std::string &to) const
    {
        size_t a = vertex_index(from), b = vertex_index(to);
        if (a == invalid() || b == invalid()) return EdgeData();
        for (auto i = vertices[a].edges.first(); i; i = i->next()) if (i->data().to == b) return i->data().mark;
        return EdgeData();
    }
    bool set_vertex_mark(const std::string &name, const VertexData &mark)
    { size_t i = vertex_index(name); if (i == invalid()) return false; vertices[i].mark = mark; return true; }
    VertexData vertex_mark(const std::string &name) const
    { size_t i = vertex_index(name); return i == invalid() ? VertexData() : vertices[i].mark; }
    Vector<VertexData> vertex_marks() const
    { Vector<VertexData> result; result.resize(size()); for (size_t i = 0; i < size(); i++) result.set(i, vertices[i].mark); return result; }
    Iterator neighbors(const std::string &name) const
    { size_t i = vertex_index(name); return Iterator(this, i == invalid() ? nullptr : vertices[i].edges.first()); }
    size_t vertex_index(const std::string &name) const
    { for (size_t i = 0; i < size(); i++) if (vertices[i].name == name) return i; return invalid(); }
    std::string vertex_name(size_t i) const { return i < size() ? vertices[i].name : std::string(); }

    // Stream format: n m; n lines "vertex_name vertex_mark"; m lines "from to edge_mark".
    bool read(std::istream &input)
    {
        size_t n, m;
        if (!(input >> n >> m)) return false;
        Graph temp;
        for (size_t i = 0; i < n; i++) { std::string name; VertexData mark; if (!(input >> name >> mark) || !temp.add_vertex(name, mark)) return false; }
        for (size_t i = 0; i < m; i++) { std::string a, b; EdgeData mark; if (!(input >> a >> b >> mark) || !temp.add_edge(a, b, mark)) return false; }
        *this = std::move(temp);
        return true;
    }
private:
    static size_t invalid() { return static_cast<size_t>(-1); }
    std::vector<Vertex> vertices;
};

#endif
