#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <vector>
#include "list.h"

using namespace std;

template<typename vertex, typename edge>
class Graph
{
public:

    struct EdgeInfo
    {
        size_t to;
        edge value;
    };

    // Создание по количеству вершин
    explicit Graph(size_t count)
    {
        vertex_count = count;
        vertex_labels.resize(count);
        alive.resize(count, true);
        adj.resize(count);
    }

    // Конструктор копирования 
    Graph(const Graph& g)
    {
        vertex_count = g.vertex_count;
        vertex_labels = g.vertex_labels;
        alive = g.alive;
        adj = g.adj;
    }

    // Перегрузка оператора присваивания
    Graph& operator=(const Graph& g)
    {
        if (this == &g)
            return *this;

        vertex_count = g.vertex_count;
        vertex_labels = g.vertex_labels;
        alive = g.alive;
        adj = g.adj;

        return *this;
    }

    // Деструктор
    ~Graph()
    {

    }

    // Возвращает количество вершин в графе
    size_t get_vertex_count() const
    {
        return vertex_count;
    }

    // Добавляет вершину
    size_t add_vertex(vertex value)
    {
        vertex_labels.push_back(value);
        alive.push_back(true);
        adj.push_back(List<EdgeInfo>());
        vertex_count++;
        return vertex_count - 1;
    }

    template<typename Lambd>
    void remove(List<EdgeInfo>& edges, Lambd lambd)
    {
        typename List<EdgeInfo>::Item* prev = nullptr;
        typename List<EdgeInfo>::Item* cur = edges.first();

        while (cur != nullptr)
        {
            if (lambd(cur->data()))
            {
                if (prev == nullptr)
                {
                    cur = edges.erase_first();
                }
                else
                {
                    cur = edges.erase_next(prev);
                }
            }
            else
            {
                prev = cur;
                cur = cur->next();
            }
        }
    }

    // Удаляет вершину по id
    void remove_vertex(size_t vertex_id)
    {
        if (!alive[vertex_id])
            return;

        alive[vertex_id] = false;

        adj[vertex_id] = List<EdgeInfo>();

        for (size_t i = 0; i < vertex_count; ++i)
        {
            if (!alive[i])
                continue;

            remove(adj[i], [&](const EdgeInfo& e) { return e.to == vertex_id; });
        }
    }

    // Поставить метку для вершины
    void set_vertex_label(size_t vertex_id, vertex value)
    {
        vertex_labels[vertex_id] = value;
    }

    // Получить метку для вершины
    vertex get_vertex_label(size_t vertex_id) const
    {
        return vertex_labels[vertex_id];
    }

    // Получить все метки для вершин
    vector<vertex> get_all_vertex_labels() const
    {
        return vertex_labels;
    }

    // Добавляет ребро
    void add_edge(size_t from, size_t to, edge value)
    {
        if (!alive[from] || !alive[to])
            return;

        EdgeInfo info;
        info.to = to;
        info.value = value;

        adj[from].insert(info);
    }

    // Удаляет ребро
    void remove_edge(size_t from, size_t to)
    {
        if (!alive[from] || !alive[to])
            return;

        remove(adj[from], [&](const EdgeInfo& e) { return e.to == to; });
    }

    // Проверка ребра между вершинами
    bool has_edge(size_t from, size_t to) const
    {
        if (!alive[from] || !alive[to])
            return false;

        typename List<EdgeInfo>::Item* cur = adj[from].first();
        while (cur != nullptr)
        {
            if (cur->data().to == to)
                return true;
            cur = cur->next();
        }
        return false;
    }

    // Поставить метку для ребра
    void set_edge_label(size_t from, size_t to, edge value)
    {
        if (!alive[from] || !alive[to])
            return;

        typename List<EdgeInfo>::Item* cur = adj[from].first();
        while (cur != nullptr)
        {
            if (cur->data().to == to)
            {
                cur->data().value = value;
                return;
            }
            cur = cur->next();
        }
    }

    // Получить метку для ребра
	edge get_edge_label(size_t from, size_t to) const
    {
        if (!alive[from] || !alive[to])
            return edge();

        typename List<EdgeInfo>::Item* cur = adj[from].first();
        while (cur != nullptr)
        {
            if (cur->data().to == to)
                return cur->data().value;
            cur = cur->next();
        }
        return edge();
    }

    class NeighborIterator
    {
    public:
        // Конструктор по умолчанию
        NeighborIterator()
        {
            current = nullptr;
        }

        // Есть ли текущий сосед
        bool valid() const
        {
            return current != nullptr;
        }

        // Перейти к следующему соседу
        void next()
        {
            if (current != nullptr)
            {
                current = current->next();
            }
        }

        // Получить id текущего соседа
        size_t vertex_id() const
        {
            return current->data().to;
        }

        // Получить метку ребра до текущего соседа
        edge edge_label() const
        {
            return current->data().value;
        }

    private:
        typename List<EdgeInfo>::Item* current;

        NeighborIterator(typename List<EdgeInfo>::Item* start)
        {
            current = start;
        }

        friend class Graph<vertex, edge>;
    };

    // Получить итератор для перебора всех соседей вершины from
    NeighborIterator neighbors(size_t from) const
    {
        NeighborIterator it(adj[from].first());
        return it;
    }

private:
    size_t vertex_count;
    vector<vertex> vertex_labels;
    vector<bool> alive;
    vector<List<EdgeInfo>> adj;
};

#endif