#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "list.h"

// Интерфейс ориентированного графа с метками вершин и рёбер.
template <typename VertexLabel, typename EdgeLabel> class Graph
{
public:
    using VertexIndex = size_t;

    // Ребро графа.
    struct Edge
    {
        VertexIndex to = 0;
        EdgeLabel label{};
    };
    // Вершина графа.
    struct Vertex
    {
        VertexLabel label{};
        List<Edge> edges;
    };

    // Итератор для обхода соседей вершины.
    class NeighborIterator
    {
    public:
        NeighborIterator() : _item(nullptr) {}
        explicit NeighborIterator(typename List<Edge>::Item* item) : _item(item) {}

        // Проверяет, указывает ли итератор на текущего соседа.
        bool valid() const { return _item != nullptr; }
        // Переходит к следующему соседу.
        void next()
        {
            if (_item)
            {
                _item = _item->next();
            }
        }

        // Возвращает индекс текущего соседа.
        VertexIndex vertex() const
        {
            ensure_item();
            return _item->data().to;
        }

        // Доступ к метке ребра (можно менять).
        EdgeLabel& label()
        {
            ensure_item();
            return _item->data().label;
        }

        // Доступ к метке ребра только для чтения.
        const EdgeLabel& label() const
        {
            ensure_item();
            return _item->data().label;
        }

    private:
        typename List<Edge>::Item* _item;

        // Проверяет валидность итератора.
        void ensure_item() const
        {
            if (!_item)
            {
                throw std::out_of_range("Iterator is invalid");
            }
        }
    };

    // Создает граф с заданным числом вершин.
    explicit Graph(size_t vertex_count = 0) : _vertices(vertex_count) {}

    // Добавляет вершину и возвращает ее индекс.
    VertexIndex add_vertex(const VertexLabel& label = VertexLabel())
    {
        Vertex vertex;
        vertex.label = label;
        _vertices.push_back(vertex);
        return _vertices.size() - 1;
    }
    // Удаляет вершину и все инцидентные рёбра.
    void remove_vertex(VertexIndex index)
    {
        validate_vertex(index);
        clear_edges(_vertices[index].edges);
        _vertices.erase(_vertices.begin() + index);

        for (auto& vertex : _vertices)
        {
            typename List<Edge>::Item* prev = nullptr;
            auto* item = vertex.edges.first();
            while (item)
            {
                Edge& edge = item->data();
                if (edge.to == index)
                {
                    item = remove_edge_item(vertex.edges, prev);
                }
                else
                {
                    if (edge.to > index)
                    {
                        edge.to -= 1;
                    }
                    prev = item;
                    item = item->next();
                }
            }
        }
    }

    // Добавляет или обновляет ребро.
    bool add_edge(VertexIndex from, VertexIndex to, const EdgeLabel& label = EdgeLabel())
    {
        validate_vertex(from);
        validate_vertex(to);

        Edge* existing = find_edge(from, to);
        if (existing)
        {
            existing->label = label;
            return false;
        }

        Edge edge;
        edge.to = to;
        edge.label = label;
        _vertices[from].edges.insert(edge);
        return true;
    }
    // Удаляет ребро from->to.
    bool remove_edge(VertexIndex from, VertexIndex to)
    {
        validate_vertex(from);
        validate_vertex(to);

        auto& edges = _vertices[from].edges;
        typename List<Edge>::Item* prev = nullptr;
        auto* item = edges.first();
        while (item)
        {
            if (item->data().to == to)
            {
                remove_edge_item(edges, prev);
                return true;
            }
            prev = item;
            item = item->next();
        }
        return false;
    }
    // Проверяет наличие ребра между вершинами.
    bool has_edge(VertexIndex from, VertexIndex to) const
    {
        validate_vertex(from);
        validate_vertex(to);
        return find_edge(from, to) != nullptr;
    }

    // Устанавливает метку ребра.
    void set_edge_label(VertexIndex from, VertexIndex to, const EdgeLabel& label)
    {
        Edge* edge = find_edge(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not found");
        }
        edge->label = label;
    }
    // Возвращает копию метки ребра.
    EdgeLabel get_edge_label(VertexIndex from, VertexIndex to) const
    {
        const Edge* edge = find_edge(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not found");
        }
        return edge->label;
    }

    // Устанавливает метку вершины.
    void set_vertex_label(VertexIndex vertex, const VertexLabel& label)
    {
        validate_vertex(vertex);
        _vertices[vertex].label = label;
    }
    // Возвращает ссылку на метку вершины.
    const VertexLabel& get_vertex_label(VertexIndex vertex) const
    {
        validate_vertex(vertex);
        return _vertices[vertex].label;
    }
    // Собирает метки всех вершин в вектор.
    std::vector<VertexLabel> vertex_labels() const
    {
        std::vector<VertexLabel> labels;
        labels.reserve(_vertices.size());
        for (const auto& vertex : _vertices)
        {
            labels.push_back(vertex.label);
        }
        return labels;
    }

    // Итератор по соседям (можно менять метки рёбер).
    NeighborIterator neighbors(VertexIndex vertex)
    {
        validate_vertex(vertex);
        return NeighborIterator(_vertices[vertex].edges.first());
    }
    // Константный итератор по соседям.
    NeighborIterator neighbors(VertexIndex vertex) const
    {
        validate_vertex(vertex);
        return NeighborIterator(_vertices[vertex].edges.first());
    }

private:
    std::vector<Vertex> _vertices;


    // ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ:
    // Проверяет корректность индекса вершины.
    void validate_vertex(VertexIndex vertex) const
    {
        if (vertex >= _vertices.size())
        {
            throw std::out_of_range("Vertex index out of range");
        }
    }

    // Удаляет все рёбра вершины.
    void clear_edges(List<Edge>& edges)
    {
        while (edges.first())
        {
            edges.erase_first();
        }
    }

    // Находит ребро from->to для изменения.
    Edge* find_edge(VertexIndex from, VertexIndex to)
    {
        validate_vertex(from);
        validate_vertex(to);
        auto* item = _vertices[from].edges.first();
        while (item)
        {
            Edge& edge = item->data();
            if (edge.to == to)
            {
                return &edge;
            }
            item = item->next();
        }
        return nullptr;
    }

    // Находит ребро from->to только для чтения.
    const Edge* find_edge(VertexIndex from, VertexIndex to) const
    {
        validate_vertex(from);
        validate_vertex(to);
        auto* item = _vertices[from].edges.first();
        while (item)
        {
            const Edge& edge = item->data();
            if (edge.to == to)
            {
                return &edge;
            }
            item = item->next();
        }
        return nullptr;
    }

    // Удаляет элемент списка смежности.
    typename List<Edge>::Item* remove_edge_item(List<Edge>& edges, typename List<Edge>::Item* prev)
    {
        if (!prev)
        {
            return edges.erase_first();
        }
        return edges.erase_next(prev);
    }
};

#endif
