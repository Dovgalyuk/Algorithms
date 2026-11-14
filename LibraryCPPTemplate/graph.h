#pragma once
#include <cstddef>
#include <istream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "list.h"
using namespace std;

// Ориентированный граф. Списки смежности лежат в List<Edge>.
// EdgeLabel   - тип пометки ребра
// VertexLabel - тип пометки вершины
template <class EdgeLabel, class VertexLabel>
class Graph {
public:
    struct Edge {
        size_t to;
        EdgeLabel label;
    };
    using EdgeList = List<Edge>;
    using EdgeItem = typename EdgeList::Item;

    // Итератор по соседям вершины: идёт по элементам списка смежности
    class Neighbourhood {
    public:
        Neighbourhood(const Graph& g, EdgeItem* cur) : g_(g), cur_(cur) {}

        bool Valid() const { return cur_ != nullptr; }      // есть ли ещё сосед
        void Next() { cur_ = cur_->next(); }                 // к следующему
        size_t To() const { return cur_->data().to; }   // индекс соседа
        const string& ToName() const { return g_.names_[cur_->data().to]; }
        EdgeLabel Label() const { return cur_->data().label; } // пометка ребра (копия)
    private:
        const Graph& g_;
        EdgeItem* cur_;
    };

    // ---------- Создание ----------
    explicit Graph(size_t vertexCount = 0) {
        for (size_t i = 0; i < vertexCount; ++i) AddVertex(to_string(i));
    }

    Graph(size_t rows, size_t cols) {
        for (size_t r = 0; r < rows; ++r)
            for (size_t c = 0; c < cols; ++c)
                AddVertex(Name(r, c));
        for (size_t r = 0; r < rows; ++r)
            for (size_t c = 0; c < cols; ++c) {
                string v = Name(r, c);
                if (c + 1 < cols) {
                    AddEdge(v, Name(r, c + 1), EdgeLabel());
                    AddEdge(Name(r, c + 1), v, EdgeLabel());
                }
                if (r + 1 < rows) {
                    AddEdge(v, Name(r + 1, c), EdgeLabel());
                    AddEdge(Name(r + 1, c), v, EdgeLabel());
                }
            }
    }

    // ---------- Вершины ----------
    // Добавить вершину; бросает invalid_argument, если имя занято
    size_t AddVertex(const string& name, const VertexLabel& label = VertexLabel()) {
        if (index_.count(name)) throw invalid_argument("vertex exists: " + name);
        size_t id = names_.size();
        names_.push_back(name);
        labels_.push_back(label);
        adj_.push_back(EdgeList());
        index_[name] = id;
        return id;
    }
    // Изменить размерность: добавляет вершины с именами-числами или удаляет последние
    void Resize(size_t newSize) {
        while (Size() > newSize) RemoveVertex(names_.back());
        while (Size() < newSize) {
            string name = to_string(Size());
            while (index_.count(name)) name += "_";
            AddVertex(name);
        }
    }
    // Удалить вершину вместе со всеми входящими и исходящими рёбрами
    void RemoveVertex(const std::string& name) {
        size_t k = Idx(name);
        adj_.erase(adj_.begin() + k);
        names_.erase(names_.begin() + k);
        labels_.erase(labels_.begin() + k);
        for (size_t u = 0; u < adj_.size(); ++u) {
            // собираем новый список: без рёбер в k и со сдвинутыми индексами
            EdgeList fresh;
            for (EdgeItem* p = adj_[u].first(); p; p = p->next()) {
                Edge e = p->data();
                if (e.to == k) continue;
                if (e.to > k) --e.to;
                fresh.insert_after(fresh.last(), e);
            }
            adj_[u] = fresh;
        }
        index_.clear();
        for (size_t i = 0; i < names_.size(); ++i) index_[names_[i]] = i;
    }
    bool HasVertex(const string& name) const { return index_.count(name) > 0; }
    size_t Size() const { return names_.size(); }
    size_t IndexOf(const string& name) const { return Idx(name); }
    const string& NameOf(size_t i) const { return names_.at(i); }

    // Рёбра
    // false, если такое ребро уже есть
    bool AddEdge(const string& from, const string& to, const EdgeLabel& label = EdgeLabel()) {
        size_t u = Idx(from), v = Idx(to);
        if (FindEdge(u, v)) return false;
        adj_[u].insert_after(adj_[u].last(), Edge{v, label});  // вставка в конец
        return true;
    }
    // false, если такого ребра не было
    bool RemoveEdge(const string& from, const string& to) {
        size_t u = Idx(from), v = Idx(to);
        EdgeItem* prev = nullptr;
        for (EdgeItem* p = adj_[u].first(); p; prev = p, p = p->next()) {
            if (p->data().to == v) {
                adj_[u].erase_next(prev);  // удаляет элемент после prev (то есть p)
                return true;
            }
        }
        return false;
    }
    bool HasEdge(const string& from, const string& to) const {
        return FindEdge(Idx(from), Idx(to)) != nullptr;
    }

    // ---------- Пометки ----------
    // data() отдаёт копию, поэтому ребро заменяем на новое на том же месте
    void SetEdgeLabel(const string& from, const string& to, const EdgeLabel& label) {
        size_t u = Idx(from), v = Idx(to);
        EdgeItem* prev = nullptr;
        for (EdgeItem* p = adj_[u].first(); p; prev = p, p = p->next()) {
            if (p->data().to == v) {
                adj_[u].erase_next(prev);
                adj_[u].insert_after(prev, Edge{v, label});
                return;
            }
        }
        throw out_of_range("no such edge");
    }
    EdgeLabel GetEdgeLabel(const string& from, const string& to) const {
        EdgeItem* p = FindEdge(Idx(from), Idx(to));
        if (!p) throw out_of_range("no such edge");
        return p->data().label;
    }
    void SetVertexLabel(const string& name, const VertexLabel& label) { labels_[Idx(name)] = label; }
    VertexLabel GetVertexLabel(const string& name) const { return labels_[Idx(name)]; }
    vector<VertexLabel> GetVertexLabels() const { return labels_; }

    // ---------- Соседи ----------
    Neighbourhood Neighbors(const string& name) const { return NeighborsOf(Idx(name)); }
    Neighbourhood NeighborsOf(size_t v) const {
        return Neighbourhood(*this, adj_.at(v).first());
    }

    // ---------- Чтение ----------
    // Формат: n m
    //         n строк "имя пометка_вершины"
    //         m строк "откуда куда пометка_ребра"
    // false при ошибке формата.
    bool Read(istream& in) {
        names_.clear(); labels_.clear(); adj_.clear(); index_.clear();
        size_t n, m;
        if (!(in >> n >> m)) return false;
        try {
            for (size_t i = 0; i < n; ++i) {
                string name; VertexLabel l;
                if (!(in >> name >> l)) return false;
                AddVertex(name, l);
            }
            for (size_t j = 0; j < m; ++j) {
                string a, b; EdgeLabel w;
                if (!(in >> a >> b >> w)) return false;
                if (!HasVertex(a) || !HasVertex(b)) return false;
                AddEdge(a, b, w);
            }
        } catch (const std::invalid_argument&) {
            return false;  // повторное имя вершины
        }
        return true;
    }

private:
    vector<string> names_;
    vector<VertexLabel> labels_;
    mutable vector<EdgeList> adj_;
    map<string, size_t> index_;

    static string Name(size_t r, size_t c) {
        return to_string(r) + "_" + to_string(c);
    }
    size_t Idx(const string& name) const {
        auto it = index_.find(name);
        if (it == index_.end()) throw out_of_range("no such vertex: " + name);
        return it->second;
    }
    // Элемент списка с ребром u->v или nullptr
    EdgeItem* FindEdge(size_t u, size_t v) const {
        for (EdgeItem* p = adj_[u].first(); p; p = p->next())
            if (p->data().to == v) return p;
        return nullptr;
    }
};