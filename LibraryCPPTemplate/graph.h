#ifndef LIBRARY_CPP_TEMPLATE_GRAPH_H
#define LIBRARY_CPP_TEMPLATE_GRAPH_H

#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "list.h"

namespace graph {

class GraphError : public std::runtime_error {
public:
    explicit GraphError(const std::string& what) : std::runtime_error(what) {}
};

template <typename VLabel, typename ELabel>
class Graph {
public:
    struct Edge {
        std::size_t to;
        ELabel label;
        Edge() : to(0), label() {}
        Edge(std::size_t t, const ELabel& l) : to(t), label(l) {}
    };

    class NeighborIterator {
    public:
        NeighborIterator() : graph_(nullptr), index_(0) {}
        NeighborIterator(const Graph* g, std::size_t index) : graph_(g), index_(index) {}

        std::pair<std::size_t, const ELabel&> operator*() const {
            const Edge& e = graph_->adjacency_[index_].valueAt(0);
            (void)e;
            return std::pair<std::size_t, const ELabel&>(0, graph_->dummyLabel_);
        }

        NeighborIterator& operator++() { ++index_; return *this; }
        bool operator!=(const NeighborIterator& other) const { return index_ != other.index_; }
        bool operator==(const NeighborIterator& other) const { return index_ == other.index_; }

    private:
        const Graph* graph_;
        std::size_t index_;
    };

    Graph() : gridWidth_(0), gridHeight_(0), isGrid_(false) {}

    explicit Graph(std::size_t n) : gridWidth_(0), gridHeight_(0), isGrid_(false) {
        for (std::size_t i = 0; i < n; ++i) {
            addVertex();
        }
    }

    Graph(std::size_t width, std::size_t height) : gridWidth_(width), gridHeight_(height), isGrid_(true) {
        for (std::size_t i = 0; i < width * height; ++i) {
            addVertex();
        }
    }

    std::size_t vertexCount() const { return labels_.size(); }

    std::size_t addVertex() {
        labels_.push_back(VLabel());
        adjacency_.push_back(List<Edge>());
        return labels_.size() - 1;
    }

    std::size_t addVertex(const VLabel& label) {
        labels_.push_back(label);
        adjacency_.push_back(List<Edge>());
        return labels_.size() - 1;
    }

    void setGridSize(std::size_t width, std::size_t height) {
        *this = Graph(width, height);
    }

    void removeVertex(std::size_t v) {
        checkVertex(v);
        for (std::size_t u = 0; u < adjacency_.size(); ++u) {
            if (u == v) continue;
            removeEdgesTo(u, v);
        }
        labels_.erase(labels_.begin() + static_cast<long>(v));
        adjacency_.erase(adjacency_.begin() + static_cast<long>(v));
        for (std::size_t u = 0; u < adjacency_.size(); ++u) {
            for (std::size_t i = 0; i < adjacency_[u].size(); ++i) {
                Edge& e = adjacency_[u].valueAt(i);
                if (e.to > v) {
                    e.to -= 1;
                }
            }
        }
    }

    void addEdge(std::size_t from, std::size_t to) {
        addEdge(from, to, ELabel());
    }

    void addEdge(std::size_t from, std::size_t to, const ELabel& label) {
        checkVertex(from);
        checkVertex(to);
        for (std::size_t i = 0; i < adjacency_[from].size(); ++i) {
            Edge& e = adjacency_[from].valueAt(i);
            if (e.to == to) {
                e.label = label;
                return;
            }
        }
        adjacency_[from].push_back(Edge(to, label));
    }

    void removeEdge(std::size_t from, std::size_t to) {
        checkVertex(from);
        checkVertex(to);
        for (typename List<Edge>::iterator it = adjacency_[from].begin(); it != adjacency_[from].end(); ++it) {
            if (it->to == to) {
                adjacency_[from].erase(it);
                return;
            }
        }
    } 

    bool hasEdge(std::size_t from, std::size_t to) const {
        checkVertex(from);
        checkVertex(to);
        for (std::size_t i = 0; i < adjacency_[from].size(); ++i) {
            if (adjacency_[from].valueAt(i).to == to) {
                return true;
            }
        }
        return false;
    }

    ELabel& edgeLabel(std::size_t from, std::size_t to) {
        checkVertex(from);
        checkVertex(to);
        for (std::size_t i = 0; i < adjacency_[from].size(); ++i) {
            if (adjacency_[from].valueAt(i).to == to) {
                return adjacency_[from].valueAt(i).label;
            }
        }
        throw GraphError("Edge not found");
    }

    const ELabel& edgeLabel(std::size_t from, std::size_t to) const {
        checkVertex(from);
        checkVertex(to);
        for (std::size_t i = 0; i < adjacency_[from].size(); ++i) {
            if (adjacency_[from].valueAt(i).to == to) {
                return adjacency_[from].valueAt(i).label;
            }
        }
        throw GraphError("Edge not found");
    }

    VLabel& vertexLabel(std::size_t v) {
        checkVertex(v);
        return labels_[v];
    }

    const VLabel& vertexLabel(std::size_t v) const {
        checkVertex(v);
        return labels_[v];
    }

    std::vector<VLabel> vertexLabels() const {
        std::vector<VLabel> out;
        out.reserve(labels_.size());
        for (std::size_t i = 0; i < labels_.size(); ++i) {
            out.push_back(labels_[i]);
        }
        return out;
    }

    class Neighbors {
    public:
        Neighbors(const Graph* g, std::size_t v) : graph_(g), vertex_(v) {}

        class Iter {
        public:
            Iter(const Graph* g, std::size_t v, std::size_t idx) : graph_(g), vertex_(v), idx_(idx) {}
            std::pair<std::size_t, const ELabel&> operator*() const {
                const Edge& e = graph_->adjacency_[vertex_].valueAt(idx_);
                return std::pair<std::size_t, const ELabel&>(e.to, e.label);
            }
            Iter& operator++() { ++idx_; return *this; }
            bool operator!=(const Iter& o) const { return idx_ != o.idx_; }
            bool operator==(const Iter& o) const { return idx_ == o.idx_; }
        private:
            const Graph* graph_;
            std::size_t vertex_;
            std::size_t idx_;
        };

        Iter begin() const { return Iter(graph_, vertex_, 0); }
        Iter end() const { return Iter(graph_, vertex_, graph_->adjacency_[vertex_].size()); }

    private:
        const Graph* graph_;
        std::size_t vertex_;
    };

    Neighbors neighbors(std::size_t v) const {
        checkVertex(v);
        return Neighbors(this, v);
    }

    void readFrom(std::istream& in) {
        *this = Graph();
        std::size_t n = 0;
        in >> n;
        if (!in) throw GraphError("Failed to read vertex count");
        for (std::size_t i = 0; i < n; ++i) {
            VLabel lbl;
            in >> lbl;
            if (!in) throw GraphError("Failed to read vertex label");
            addVertex(lbl);
        }
        std::size_t m = 0;
        in >> m;
        if (!in) throw GraphError("Failed to read edge count");
        for (std::size_t i = 0; i < m; ++i) {
            std::size_t from = 0, to = 0;
            ELabel lbl;
            in >> from >> to >> lbl;
            if (!in) throw GraphError("Failed to read edge");
            addEdge(from, to, lbl);
        }
    }

    void writeTo(std::ostream& out) const {
        out << vertexCount() << '\n';
        for (std::size_t i = 0; i < labels_.size(); ++i) {
            out << labels_[i] << '\n';
        }
        std::size_t m = 0;
        for (std::size_t u = 0; u < adjacency_.size(); ++u) {
            m += adjacency_[u].size();
        }
        out << m << '\n';
        for (std::size_t u = 0; u < adjacency_.size(); ++u) {
            for (std::size_t i = 0; i < adjacency_[u].size(); ++i) {
                const Edge& e = adjacency_[u].valueAt(i);
                out << u << ' ' << e.to << ' ' << e.label << '\n';
            }
        }
    }

    const List<Edge>& adjacency(std::size_t v) const {
        checkVertex(v);
        return adjacency_[v];
    }

private:
    std::vector<VLabel> labels_;
    std::vector<List<Edge>> adjacency_;
    std::size_t gridWidth_;
    std::size_t gridHeight_;
    bool isGrid_;
    ELabel dummyLabel_;

    void checkVertex(std::size_t v) const {
        if (v >= labels_.size()) {
            throw GraphError("Vertex index out of range");
        }
    }

    void removeEdgesTo(std::size_t u, std::size_t v) {
        for (typename List<Edge>::iterator it = adjacency_[u].begin(); it != adjacency_[u].end(); ) {
            if (it->to == v) {
                it = adjacency_[u].erase(it);
            } else {
                ++it;
            }
        }
    }
};

}

#endif
