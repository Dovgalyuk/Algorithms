#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"

#include <istream>
#include <stdexcept>
#include <string>

template <typename EdgeLabel, typename VertexLabel> class Graph
{
private:
    struct Vertex
    {
        std::string name;
        VertexLabel label{};
    };

    struct Edge
    {
        bool exists = false;
        EdgeLabel label{};
    };

public:
    explicit Graph(size_t count = 0)
    {
        vertices.resize(count);
        edges.resize(count);
        for (size_t i = 0; i < count; ++i)
        {
            vertices[i].name = std::to_string(i);
            edges[i].resize(count);
        }
    }

    void addVertex(const std::string &name, const VertexLabel &label)
    {
        if (name.empty() || findVertex(name) != vertices.size())
            throw std::invalid_argument("Имя вершины пустое или уже занято");

        Graph larger(vertices.size() + 1);
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            larger.vertices[i] = vertices[i];
            for (size_t j = 0; j < vertices.size(); ++j)
                larger.edges[i][j] = edges[i][j];
        }
        larger.vertices[vertices.size()] = {name, label};
        vertices.swap(larger.vertices);
        edges.swap(larger.edges);
    }

    void removeVertex(const std::string &name)
    {
        size_t removed = vertexIndex(name);
        Graph smaller(vertices.size() - 1);
        for (size_t i = 0; i < smaller.vertices.size(); ++i)
        {
            size_t oldRow = i < removed ? i : i + 1;
            smaller.vertices[i] = vertices[oldRow];
            for (size_t j = 0; j < smaller.vertices.size(); ++j)
            {
                size_t oldColumn = j < removed ? j : j + 1;
                smaller.edges[i][j] = edges[oldRow][oldColumn];
            }
        }
        vertices.swap(smaller.vertices);
        edges.swap(smaller.edges);
    }

    void addEdge(const std::string &from, const std::string &to, const EdgeLabel &label)
    {
        Edge &edge = edges[vertexIndex(from)][vertexIndex(to)];
        if (edge.exists)
            throw std::invalid_argument("Ребро уже существует");
        edge.label = label;
        edge.exists = true;
    }

    void removeEdge(const std::string &from, const std::string &to)
    {
        edges[vertexIndex(from)][vertexIndex(to)].exists = false;
    }

    bool hasEdge(const std::string &from, const std::string &to) const
    {
        return edges[vertexIndex(from)][vertexIndex(to)].exists;
    }

    void setEdgeLabel(const std::string &from, const std::string &to, const EdgeLabel &label)
    {
        Edge &edge = edges[vertexIndex(from)][vertexIndex(to)];
        if (!edge.exists)
            throw std::out_of_range("Ребро не существует");
        edge.label = label;
    }

    EdgeLabel edgeLabel(const std::string &from, const std::string &to) const
    {
        const Edge &edge = edges[vertexIndex(from)][vertexIndex(to)];
        if (!edge.exists)
            throw std::out_of_range("Ребро не существует");
        return edge.label;
    }

    void setVertexLabel(const std::string &name, const VertexLabel &label)
    {
        vertices[vertexIndex(name)].label = label;
    }

    VertexLabel vertexLabel(const std::string &name) const
    {
        return vertices[vertexIndex(name)].label;
    }

    Vector<VertexLabel> vertexLabels() const
    {
        Vector<VertexLabel> labels;
        labels.resize(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i)
            labels[i] = vertices[i].label;
        return labels;
    }

    Vector<std::string> vertexNames() const
    {
        Vector<std::string> names;
        names.resize(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i)
            names[i] = vertices[i].name;
        return names;
    }

    // Перебор исходящих соседей
    struct NeighborIterator
    {
        NeighborIterator(const Graph &graph, size_t row, size_t column)
            : graph(graph), row(row), column(column)
        {
            skipEmpty();
        }

        const std::string &operator*() const { return graph.vertices[column].name; }

        NeighborIterator &operator++()
        {
            ++column;
            skipEmpty();
            return *this;
        }

        bool operator!=(const NeighborIterator &other) const
        {
            return &graph != &other.graph || row != other.row || column != other.column;
        }

    private:
        const Graph &graph;
        size_t row;
        size_t column;

        void skipEmpty()
        {
            while (column < graph.vertices.size() && !graph.edges[row][column].exists)
                ++column;
        }
    };

    struct NeighborRange
    {
        const Graph &graph;
        size_t row;

        NeighborIterator begin() const { return {graph, row, 0}; }
        NeighborIterator end() const { return {graph, row, graph.vertices.size()}; }
    };

    NeighborRange neighbors(const std::string &name) const
    {
        return {*this, vertexIndex(name)};
    }

    friend std::istream &operator>>(std::istream &input, Graph &graph)
    {
        int vertexCount, edgeCount;
        if (!(input >> vertexCount >> edgeCount))
            return input;
        if (vertexCount < 0 || edgeCount < 0)
        {
            input.setstate(std::ios::failbit);
            return input;
        }

        Graph parsed;
        parsed.vertices.resize(vertexCount);
        for (int i = 0; i < vertexCount; ++i)
        {
            Vertex vertex;
            if (!(input >> vertex.name >> vertex.label))
                return input;
            if (parsed.findVertex(vertex.name) != parsed.vertices.size())
            {
                input.setstate(std::ios::failbit);
                return input;
            }
            parsed.vertices[i] = vertex;
        }

        parsed.edges.resize(vertexCount);
        for (int i = 0; i < vertexCount; ++i)
            parsed.edges[i].resize(vertexCount);

        for (int i = 0; i < edgeCount; ++i)
        {
            std::string from, to;
            EdgeLabel label{};
            if (!(input >> from >> to >> label))
                return input;
            size_t row = parsed.findVertex(from);
            size_t column = parsed.findVertex(to);
            if (row == parsed.vertices.size() || column == parsed.vertices.size()
                || parsed.edges[row][column].exists)
            {
                input.setstate(std::ios::failbit);
                return input;
            }
            parsed.edges[row][column] = {true, label};
        }

        graph.vertices.swap(parsed.vertices);
        graph.edges.swap(parsed.edges);
        return input;
    }

private:
    Vector<Vertex> vertices;
    Vector<Vector<Edge>> edges;

    size_t findVertex(const std::string &name) const
    {
        size_t i = 0;
        while (i < vertices.size() && vertices[i].name != name)
            ++i;
        return i;
    }

    size_t vertexIndex(const std::string &name) const
    {
        size_t i = findVertex(name);
        if (i == vertices.size())
            throw std::out_of_range("Неизвестная вершина: " + name);
        return i;
    }
};

#endif
