#pragma once
#include "list.h"
#include <vector>
#include <utility>
#include <cstddef>

using namespace std;

// Класс графа на списках смежности (метки на вершинах и рёбрах).

template <class VLabel, class ELabel>
class Graph {
public:
    using VertexId = size_t;
    struct Edge {
        VertexId to;
        ELabel label;
    };
    using AdjList = List<Edge>;

    // Итератор для обхода соседей вершины.

    struct NeighborIterator {
        const typename AdjList::Item* it = nullptr;
        NeighborIterator() = default;
        explicit NeighborIterator(const typename AdjList::Item* p) : it(p) {}

        bool valid() const { return it != nullptr; }
        void next() { if (it) it = it->next(); }
        VertexId to() const { return it->data().to; }
        const ELabel& edge_label() const { return it->data().label; }
    };

    // Конструктор: создаёт граф из n пустых вершин.

    explicit Graph(size_t n = 0) : g_(n), vlabel_(n) {}

    // Функция для получения числа вершин.

    size_t vertex_count() const { return g_.size(); }

    // Функция для добавления вершины.

    VertexId add_vertex(const VLabel& label = VLabel()) {
        g_.push_back(AdjList());
        vlabel_.push_back(label);
        return g_.size() - 1;
    }

    // Метки вершин.

    void set_vertex_label(VertexId v, const VLabel& label) { vlabel_[v] = label; }
    const VLabel& vertex_label(VertexId v) const { return vlabel_[v]; }

    // Функция для добавления ребра u->v с меткой.

    void add_edge(VertexId u, VertexId v, const ELabel& label = ELabel()) {
        ensure_vertex(u);
        ensure_vertex(v);

        for (auto p = g_[u].first(); p; p = p->next()) {
            if (p->data().to == v) {
                p->data().label = label;
                return;
            }
        }

        Edge e;
        e.to = v;
        e.label = label;
        g_[u].insert(e);
    }

    // Функция для проверки наличия ребра u->v.

    bool has_edge(VertexId u, VertexId v) const {
        for (auto p = g_[u].first(); p; p = p->next())
            if (p->data().to == v)
                return true;

        return false;
    }

    // Функция для удаления ребра u->v.

    void remove_edge(VertexId u, VertexId v) {
        typename AdjList::Item* prev = nullptr;
        for (auto p = g_[u].first(); p; p = p->next()) {
            if (p->data().to == v) {
                if (prev)
                    g_[u].erase_after(prev);
                else
                    g_[u].erase_first();
                break;
            }

            prev = p;
        }
    }

    // Функция для изменения метки ребра u->v.

    void set_edge_label(VertexId u, VertexId v, const ELabel& label) {
        for (auto p = g_[u].first(); p; p = p->next()) {
            if (p->data().to == v) {
                p->data().label = label;
                break;
            }
        }
    }

    // Функция для получения метки ребра u->v.

    ELabel edge_label(VertexId u, VertexId v) const {
        for (auto p = g_[u].first(); p; p = p->next())
            if (p->data().to == v)
                return p->data().label;

        return ELabel();
    }

    // Функция для удаления вершины v.

    void remove_vertex(VertexId v) {
        for (size_t u = 0; u < g_.size(); ++u)
            if (u != v)
                remove_edge(u, v);

        g_[v] = AdjList();
        vlabel_[v] = VLabel();
    }

    // Функция для получения копии всех меток вершин.

    vector<VLabel> vertex_labels() const { return vlabel_; }

    // Функция для получения итератора по соседям вершины u.

    NeighborIterator neighbors_begin(VertexId u) const { return NeighborIterator(g_[u].first()); }

private:
    // Вспомогательная функция: расширяет граф, чтобы индекс v был валиден.

    void ensure_vertex(VertexId v) {
        while (v >= g_.size())
            add_vertex();
    }

    vector<AdjList> g_;
    vector<VLabel> vlabel_;
};