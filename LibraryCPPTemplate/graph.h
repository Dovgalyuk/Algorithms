#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <vector>

#include "list.h"

template <typename VertexLabel, typename EdgeLabel>
class Graph
{
public:
    using VertexIndex = size_t;

    // Ребро (to - вершина, label - метка)
    struct Edge
    {
        VertexIndex to = 0;
        EdgeLabel label{};

        Edge(VertexIndex i, const EdgeLabel& l) : to(i), label(l) {}
    };

    // Вершина (label - метка, edges - список исходящих ребер)
    struct Vertex
    {
        VertexLabel label{};
        List<Edge> edges;
    };

    // Итератор по соседям вершины
    class NeighborIterator
    {
    public:
        using ListItem = typename List<Edge>::Item;

        NeighborIterator(ListItem* item) : _item(item) {}

        // Проверяет, указывает ли итератор на реального соседа
        bool valid() const { return _item != nullptr; }
        // Переходит к следующему соседу
        void next()
        {
            if (_item)
            {
                _item = _item->next();
            }
        }

        // Возвращает индекс текущей соседней вершины
        VertexIndex vertex() const
        {
            return _item->data().to;
        }

        // Возвращает метку ребра, ведущего к соседу
        const EdgeLabel& label() const
        {
            return _item->data().label;
        }

    private:
        ListItem* _item;
    };

    // Создаёт граф с указанным числом пустых вершин
    explicit Graph(size_t vertex_count = 0) : _vertices(vertex_count) {}

    // Добавляет вершину с меткой и возвращает её индекс
    VertexIndex add_vertex(const VertexLabel& label = VertexLabel())
    {
        Vertex vertex;
        vertex.label = label;
        _vertices.push_back(vertex);
        return _vertices.size() - 1;
    }
    // Удаляет вершину и обновляет рёбра
    void remove_vertex(VertexIndex index)
    {
        if (index >= _vertices.size()) return;
        // Удаляем саму вершину из вектора (это сдвинет все последующие вершины в векторе)
        _vertices.erase(_vertices.begin() + index);

        // Проходим по всем оставшимся вершинам и чистим ссылки на удаленную
        for (auto& vertex : _vertices) {
            auto* item = vertex.edges.first();
            while (item) {
                Edge& edge = item->data();
                auto* next_item = item->next();

                if (edge.to == index) {
                    // Ребро вело в удаленную вершину -> удаляем ребро
                    if (item == vertex.edges.first())
                        vertex.edges.erase_first();
                    else
                        vertex.edges.erase_next(item->prev());
                }
                else if (edge.to > index) {
                    // Ребро вело в вершину, которая сместилась -> корректируем индекс
                    edge.to -= 1;
                }

                item = next_item;
            }
        }
    }

    // Добавляет/обновляет ориентированное ребро from->to
    void add_edge(VertexIndex from, VertexIndex to, const EdgeLabel& label = EdgeLabel())
    {
        // Ищем, существует ли ребро
        auto* item = _vertices[from].edges.first();
        while (item) {
            if (item->data().to == to) {
                item->data().label = label;
                return;
            }
            item = item->next();
        }

        // Не нашли — добавляем новое
        _vertices[from].edges.insert(Edge(to, label));
    }
    // Удаляет ребро from->to, если оно существует
    void remove_edge(VertexIndex from, VertexIndex to)
    {
        auto* item = _vertices[from].edges.first();
        while (item) {
            if (item->data().to == to) {
                if (item == _vertices[from].edges.first())
                    _vertices[from].edges.erase_first();
                else
                    _vertices[from].edges.erase_next(item->prev());
                return;
            }
            item = item->next();
        }
    }
    // Проверяет наличие ребра из from в to
    bool has_edge(VertexIndex from, VertexIndex to) const {
        if (from >= _vertices.size()) return false;

        auto* item = _vertices[from].edges.first();
        while (item) {
            if (item->data().to == to) return true;
            item = item->next();
        }
        return false;
    }

    // Устанавливает метку существующего ребра
    void set_edge_label(VertexIndex from, VertexIndex to, const EdgeLabel& label) {
        auto* item = _vertices[from].edges.first();
        while (item) {
            if (item->data().to == to) {
                item->data().label = label;
                return;
            }
            item = item->next();
        }
    }
    // Возвращает копию метки ребра
    EdgeLabel get_edge_label(VertexIndex from, VertexIndex to) const {
        auto* item = _vertices[from].edges.first();
        while (item) {
            if (item->data().to == to) return item->data().label;
            item = item->next();
        }
        return EdgeLabel();
    }

    // Изменяет метку вершины
    void set_vertex_label(VertexIndex vertex, const VertexLabel& label)
    {
        _vertices[vertex].label = label;
    }
    // Возвращает метку вершины
    VertexLabel get_vertex_label(VertexIndex index) const {
        return _vertices[index].label;
    }
    // Возвращает метки всех вершин
    std::vector<VertexLabel> vertex_labels() const
    {
        std::vector<VertexLabel> labels;
        labels.reserve(_vertices.size());
        for (const auto& v : _vertices) {
            labels.push_back(v.label);
        }
        return labels;
    }

    // Возвращает итератор по исходящим соседям вершины
    NeighborIterator neighbors(VertexIndex vertex)
    {
        return NeighborIterator(_vertices[vertex].edges.first());
    }

private:
    std::vector<Vertex> _vertices;
};

#endif
