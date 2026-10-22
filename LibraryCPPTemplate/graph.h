#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include <map>
#include <stdexcept>
#include <utility>

#include "list.h"
#include "vector.h"

template <typename VertexLabel, typename EdgeLabel>
class Graph
{
public:
    using IndexType = std::size_t;
    using IndexMap = std::map<VertexLabel, IndexType>;

    struct Edge
    {
        IndexType to;
        EdgeLabel label;
    };

    using ArcList = List<Edge>;
    using Item = typename ArcList::Item;
    using Labels = Vector<VertexLabel>;

    class NeighborIterator
    {
    public:
        using value_type = std::pair<IndexType, EdgeLabel>;

        NeighborIterator() : item_(nullptr) {}
        explicit NeighborIterator(const Item *item) : item_(item) {}

        bool operator!=(const NeighborIterator &other) const { return item_ != other.item_; }

        NeighborIterator &operator++()
        {
            if (item_) item_ = item_->next();
            return *this;
        }

        value_type operator*() const
        {
            const Edge &e = item_->data();
            return value_type(e.to, e.label);
        }

    private:
        const Item *item_;
    };

    Graph() = default;
    explicit Graph(IndexType vertex_count) { resize(vertex_count); }
    Graph(IndexType rows, IndexType cols) : Graph(rows * cols) { build_grid(rows, cols); }

    IndexType vertex_count() const { return names_.size(); }

    void resize(IndexType new_count)
    {
        IndexType old_count = names_.size();
        if (new_count < old_count)
        {
            for (IndexType u = 0; u < new_count; ++u)
                remove_out_of_range(adjacency_.get(u), new_count);
        }
        names_.resize(new_count);
        adjacency_.resize(new_count);
    }

    IndexType add_vertex(const VertexLabel &label = VertexLabel())
    {
        IndexType id = names_.size();
        names_.push_back(label);
        adjacency_.push_back(ArcList());
        return id;
    }

    void remove_vertex(IndexType vertex)
    {
        check_vertex(vertex);
        IndexType n = names_.size();

        for (IndexType u = 0; u < n; ++u)
        {
            if (u == vertex) continue;
            ArcList &lst = adjacency_.get(u);
            Item *prev = nullptr;
            for (Item *it = lst.first(); it; )
            {
                if (it->data().to == vertex)
                    it = prev ? lst.erase_next(prev) : lst.erase_first();
                else
                {
                    if (it->data().to > vertex) --it->data().to;
                    prev = it;
                    it = it->next();
                }
            }
        }

        names_.erase(vertex);
        adjacency_.erase(vertex);
    }

    void add_edge(IndexType from, IndexType to, const EdgeLabel &label = EdgeLabel())
    {
        check_vertex(from);
        check_vertex(to);
        Item *it = find_arc(from, to);
        if (it) { it->data().label = label; return; }
        adjacency_.get(from).insert(Edge{to, label});
    }

    void remove_edge(IndexType from, IndexType to)
    {
        check_vertex(from);
        check_vertex(to);
        ArcList &lst = adjacency_.get(from);
        Item *prev = nullptr;
        for (Item *it = lst.first(); it; )
        {
            if (it->data().to == to)
            {
                if (prev) lst.erase_next(prev);
                else      lst.erase_first();
                return;
            }
            prev = it;
            it = it->next();
        }
    }

    bool has_edge(IndexType from, IndexType to) const
    {
        check_vertex(from);
        check_vertex(to);
        return find_arc(from, to) != nullptr;
    }

    EdgeLabel edge_label(IndexType from, IndexType to) const
    {
        check_vertex(from);
        check_vertex(to);
        const Item *it = find_arc(from, to);
        if (!it) throw std::logic_error("Edge does not exist");
        return it->data().label;
    }

    void set_edge_label(IndexType from, IndexType to, const EdgeLabel &label)
    {
        check_vertex(from);
        check_vertex(to);
        Item *it = find_arc(from, to);
        if (!it) throw std::logic_error("Edge does not exist");
        it->data().label = label;
    }

    void set_vertex_label(IndexType vertex, const VertexLabel &label)
    {
        check_vertex(vertex);
        names_.set(vertex, label);
    }

    VertexLabel vertex_label(IndexType vertex) const
    {
        check_vertex(vertex);
        return names_.get(vertex);
    }

    Labels vertex_labels() const { return names_; }

    NeighborIterator begin(IndexType vertex) const
    {
        check_vertex(vertex);
        return NeighborIterator(adjacency_.get(vertex).first());
    }

    NeighborIterator end(IndexType) const { return NeighborIterator(); }

    bool read(std::istream &input)
    {
        IndexType n = 0;
        if (!(input >> n)) return false;

        Graph parsed(n);
        IndexMap index;
        for (IndexType i = 0; i < n; ++i)
        {
            VertexLabel name;
            if (!(input >> name)) return false;
            if (index.count(name)) return false;
            index[name] = i;
            parsed.set_vertex_label(i, name);
        }

        IndexType m = 0;
        if (!(input >> m)) return false;
        for (IndexType i = 0; i < m; ++i)
        {
            VertexLabel from_name, to_name;
            EdgeLabel label;
            if (!(input >> from_name >> to_name >> label)) return false;
            auto from_it = index.find(from_name);
            auto to_it   = index.find(to_name);
            if (from_it == index.end() || to_it == index.end()) return false;
            parsed.add_edge(from_it->second, to_it->second, label);
        }

        *this = parsed;
        return true;
    }

private:
    void check_vertex(IndexType vertex) const
    {
        if (vertex >= names_.size())
            throw std::out_of_range("Vertex index out of range");
    }

    Item *find_arc(IndexType from, IndexType to) const
    {
        for (Item *it = adjacency_.get(from).first(); it; it = it->next())
            if (it->data().to == to) return it;
        return nullptr;
    }

    static void remove_out_of_range(ArcList &lst, IndexType bound)
    {
        Item *prev = nullptr;
        for (Item *it = lst.first(); it; )
        {
            if (it->data().to >= bound)
                it = prev ? lst.erase_next(prev) : lst.erase_first();
            else
            {
                prev = it;
                it = it->next();
            }
        }
    }

    void build_grid(IndexType rows, IndexType cols)
    {
        for (IndexType r = 0; r < rows; ++r)
            for (IndexType c = 0; c < cols; ++c)
            {
                IndexType u = r * cols + c;
                if (c + 1 < cols) add_edge(u, u + 1, EdgeLabel());
                if (r + 1 < rows) add_edge(u, u + cols, EdgeLabel());
            }
    }

    Vector<VertexLabel> names_;
    Vector<ArcList> adjacency_;
};

#endif