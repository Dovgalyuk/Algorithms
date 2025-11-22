#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <stdexcept>
#include <vector>
#include "list.h"

template <typename VertexLabel, typename EdgeLabel> class Graph
{
public:
    using VertexIndex = size_t;

    // Ребро, указывающее на вершину `to` и содержащее метку.
    struct Edge
    {
        VertexIndex to = 0;
        EdgeLabel label{};
    };

    // Итератор по исходящим соседям вершины.
    class NeighborIterator
    {
    public:
        NeighborIterator() : _item(nullptr) {}
        explicit NeighborIterator(typename List<Edge>::Item* item) : _item(item) {}

        // Проверяет, указывает ли итератор на существующего соседа.
        bool valid() const { return _item != nullptr; }

        // Переходит к следующему соседу при его наличии.
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

        // Доступ к метке текущего ребра с возможностью изменения.
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

        // Проверяет корректность итератора перед обращением к данным.
        void ensure_item() const
        {
            if (!_item)
            {
                throw std::out_of_range("Iterator not valid");
            }
        }
    };

    // Инициализирует граф `vertex_count` пустыми вершинами.
    explicit Graph(size_t vertex_count = 0) : _vertices(vertex_count)
    {
    }

    // Возвращает текущее количество вершин.
    size_t vertex_count() const
    {
        return _vertices.size();
    }

    // Добавляет вершину с меткой и возвращает её индекс.
    VertexIndex add_vertex(const VertexLabel& label = VertexLabel())
    {
        Vertex vertex;
        vertex.label = label;
        _vertices.push_back(vertex);
        return _vertices.size() - 1;
    }

    // Удаляет вершину и все связанные с ней рёбра.
    void remove_vertex(size_t index)
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

    // Добавляет или обновляет ориентированное ребро from->to, возвращает true при создании.
    bool add_edge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel())
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

    // Удаляет ребро from->to, если оно существует.
    bool remove_edge(size_t from, size_t to)
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

    // Проверяет наличие ребра from->to.
    bool has_edge(size_t from, size_t to) const
    {
        validate_vertex(from);
        validate_vertex(to);
        return find_edge(from, to) != nullptr;
    }

    // Задаёт метку существующего ребра.
    void set_edge_label(size_t from, size_t to, const EdgeLabel& label)
    {
        Edge* edge = find_edge(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not exist");
        }
        edge->label = label;
    }

    // Возвращает метку ребра.
    EdgeLabel get_edge_label(size_t from, size_t to) const
    {
        const Edge* edge = find_edge(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not exist");
        }
        return edge->label;
    }

    // Обновляет метку указанной вершины.
    void set_vertex_label(size_t vertex, const VertexLabel& label)
    {
        validate_vertex(vertex);
        _vertices[vertex].label = label;
    }

    // Возвращает константную ссылку на метку вершины.
    const VertexLabel& get_vertex_label(size_t vertex) const
    {
        validate_vertex(vertex);
        return _vertices[vertex].label;
    }

    // Возвращает вектор меток всех вершин
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

    // Возвращает итератор по соседям вершины
    NeighborIterator neighbors(size_t vertex)
    {
        validate_vertex(vertex);
        return NeighborIterator(_vertices[vertex].edges.first());
    }

    // NeighborIterator neighbors(size_t vertex) const
    // {
    //     validate_vertex(vertex);
    //     return NeighborIterator(_vertices[vertex].edges.first());
    // }

private:
    // Внутреннее представление вершины: метка и список смежности.
    struct Vertex
    {
        VertexLabel label{};
        List<Edge> edges;
    };

    std::vector<Vertex> _vertices;

    // Бросает исключение, если индекс вершины вне диапазона.
    void validate_vertex(size_t vertex) const
    {
        if (vertex >= _vertices.size())
        {
            throw std::out_of_range("Vertex index out of range");
        }
    }

    // Удаляет все рёбра из списка смежности.
    void clear_edges(List<Edge>& edges)
    {
        while (edges.first())
        {
            edges.erase_first();
        }
    }

    // Находит и возвращает указатель на ребро from->to либо nullptr.
    Edge* find_edge(size_t from, size_t to)
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

    const Edge* find_edge(size_t from, size_t to) const
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

    // Удаляет элемент после `prev` (или первый, если prev == nullptr).
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
