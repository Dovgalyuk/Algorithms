//
// Created by Zaitunat on 07.11.2026.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H
#include <ios>
#include <istream>
#include <stdexcept>
#include "list.h"
#include "vector.h"

template <typename VertexData, typename EdgeData> class Graph
{
private:
    struct EdgeRec
    {
        size_t to;
        EdgeData label;
        EdgeRec() : to(0), label() {}
        EdgeRec(size_t t, const EdgeData &l) : to(t), label(l) {}
    };
    typedef List<EdgeRec> EdgeList;
    typedef typename EdgeList::Item EdgeItem;

public:
    class NeighborIterator
    {
    public:
        explicit NeighborIterator(EdgeItem *item) : cur_(item) {}
        bool valid() const { return cur_ != nullptr; }
        void next() { cur_ = cur_->next(); }
        size_t vertex() const { return cur_->data().to; }
        EdgeData label() const { return cur_->data().label; }

    private:
        EdgeItem *cur_;
    };

    explicit Graph(size_t vertexCount = 0)
    {
        labels_.resize(vertexCount);
        adj_.resize(vertexCount);
        for (size_t i = 0; i < vertexCount; i++) {
            adj_.set(i, new EdgeList());
        }
    }


    Graph(size_t rows, size_t cols) : Graph(rows * cols)
    {
        for (size_t r = 0; r < rows; r++)
        {
            for (size_t c = 0; c < cols; c++)
            {
                size_t v = r * cols + c;
                if (c + 1 < cols)
                {
                    addEdge(v, v + 1);
                    addEdge(v + 1, v);
                }
                if (r + 1 < rows)
                {
                    addEdge(v, v + cols);
                    addEdge(v + cols, v);
                }
            }
        }
    }

    Graph(const Graph &a) : labels_(a.labels_), adj_()
    {
        copyLists(a);
    }

    Graph &operator=(const Graph &a)
    {
        if (this != &a)
        {
            clearLists();
            labels_ = a.labels_;
            copyLists(a);
        }
        return *this;
    }

    ~Graph()
    {
        clearLists();
    }

    size_t vertexCount() const
    {
        return labels_.size();
    }

    size_t addVertex(const VertexData &label = VertexData())
    {
        size_t index = labels_.size();
        EdgeList *list = new EdgeList();
        labels_.resize(index + 1);
        labels_.set(index, label);
        adj_.resize(index + 1);
        adj_.set(index, list);
        return index;
    }

    void removeVertex(size_t v)
    {
        checkVertex(v);
        size_t n = labels_.size();
        delete adj_.get(v);
        for (size_t i = v; i + 1 < n; i++)
        {
            labels_.set(i, labels_.get(i + 1));
            adj_.set(i, adj_.get(i + 1));
        }
        labels_.resize(n - 1);
        adj_.resize(n - 1);

        dropVertexFromLists(v);
    }


    void addEdge(size_t from, size_t to, const EdgeData &label = EdgeData())
    {
        checkVertex(from);
        checkVertex(to);
        EdgeList *list = adj_.get(from);
        EdgeItem *prev = nullptr;
        EdgeItem *found = findEdge(list, to, prev);
        if (found != nullptr)
        {
            list->erase_next(prev);
            list->insert_after(prev, EdgeRec(to, label));
        }
        else
        {
            list->insert(EdgeRec(to, label));
        }
    }
    void removeEdge(size_t from, size_t to)
    {
        checkVertex(from);
        checkVertex(to);
        EdgeList *list = adj_.get(from);
        EdgeItem *prev = nullptr;
        if (findEdge(list, to, prev) != nullptr)
            list->erase_next(prev);
    }
    bool hasEdge(size_t from, size_t to) const
    {
        checkVertex(from);
        checkVertex(to);
        EdgeItem *prev = nullptr;
        return findEdge(adj_.get(from), to, prev) != nullptr;
    }

    void setEdgeLabel(size_t from, size_t to, const EdgeData &label)
    {
        checkVertex(from);
        checkVertex(to);
        EdgeList *list = adj_.get(from);
        EdgeItem *prev = nullptr;
        if (findEdge(list, to, prev) == nullptr)
            throw std::invalid_argument("Graph: edge does not exist");
        list->erase_next(prev);
        list->insert_after(prev, EdgeRec(to, label));
    }
    EdgeData getEdgeLabel(size_t from, size_t to) const
    {
        checkVertex(from);
        checkVertex(to);
        EdgeItem *prev = nullptr;
        EdgeItem *found = findEdge(adj_.get(from), to, prev);
        if (found == nullptr)
            throw std::invalid_argument("Graph: edge does not exist");
        return found->data().label;
    }

    void setVertexLabel(size_t v, const VertexData &label)
    {
        checkVertex(v);
        labels_.set(v, label);
    }

    VertexData getVertexLabel(size_t v) const
    {
        checkVertex(v);
        return labels_.get(v);
    }

    Vector<VertexData> getVertexLabels() const
    {
        return labels_;
    }
    size_t findVertex(const VertexData &label) const
    {
        for (size_t i = 0; i < labels_.size(); i++)
        {
            if (labels_.get(i) == label)
                return i;
        }
        throw std::invalid_argument("Graph: vertex not found");
    }
    NeighborIterator neighbors(size_t v) const
    {
        checkVertex(v);
        return NeighborIterator(adj_.get(v)->first());
    }

    std::istream &read(std::istream &in)
    {
        size_t n = 0;
        if (!(in >> n))
            return in;

        Graph tmp(n);
        for (size_t i = 0; i < n; i++)
        {
            VertexData name;
            if (!(in >> name))
                return in;
            for (size_t j = 0; j < i; j++)
            {
                if (tmp.labels_.get(j) == name)
                {
                    in.setstate(std::ios::failbit);
                    return in;
                }
            }
            tmp.labels_.set(i, name);
        }

        size_t m = 0;
        if (!(in >> m))
            return in;
        for (size_t k = 0; k < m; k++)
        {
            VertexData a;
            VertexData b;
            EdgeData w;
            if (!(in >> a >> b >> w))
                return in;
            try
            {
                tmp.addEdge(tmp.findVertex(a), tmp.findVertex(b), w);
            }
            catch (const std::invalid_argument &)
            {
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        *this = tmp;
        return in;
    }

private:
    void checkVertex(size_t v) const
    {
        if (v >= labels_.size())
            throw std::out_of_range("Graph: vertex index out of range");
    }

    static EdgeItem *findEdge(EdgeList *list, size_t to, EdgeItem *&prev)
    {
        prev = nullptr;
        for (EdgeItem *p = list->first(); p != nullptr; p = p->next())
        {
            if (p->data().to == to)
                return p;
            prev = p;
        }
        return nullptr;
    }
    void dropVertexFromLists(size_t v)
    {
        for (size_t u = 0; u < adj_.size(); u++)
        {
            EdgeList *old = adj_.get(u);
            EdgeList *fresh = new EdgeList();
            EdgeItem *last = nullptr;
            for (EdgeItem *p = old->first(); p != nullptr; p = p->next())
            {
                EdgeRec rec = p->data();
                if (rec.to == v)
                    continue;
                if (rec.to > v)
                    rec.to--;
                last = fresh->insert_after(last, rec);
            }
            delete old;
            adj_.set(u, fresh);
        }
    }

    void clearLists()
    {
        for (size_t i = 0; i < adj_.size(); i++)
            delete adj_.get(i);
        adj_.resize(0);
    }

    void copyLists(const Graph &a)
    {
        adj_.resize(a.adj_.size());
        for (size_t i = 0; i < a.adj_.size(); i++)
            adj_.set(i, new EdgeList(*a.adj_.get(i)));
    }

    Vector<VertexData> labels_;
    Vector<EdgeList *> adj_;
};

#endif //ALGORITHMS_GRAPH_H
