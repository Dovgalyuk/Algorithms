#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>
#include <cstddef>
#include "vector.h"

template<typename VertexLabel = int, typename EdgeLabel = int>
class Digraph {
private:
    // The adjacency matrix
    Vector<Vector<EdgeLabel>> admatrix;
    // Vertex labels
    Vector<VertexLabel> vertlabels;
    // Verifying the validity of the vertex label
    bool validvertid(size_t v) const {
        return v < countvert();
    }
public:
    Digraph() = default;

    explicit Digraph(size_t pcountvert) : admatrix(pcountvert, Vector<EdgeLabel>(pcountvert, EdgeLabel{}))
        , vertlabels(pcountvert) {
    }

    Digraph(const Digraph& other) : admatrix(other.admatrix), vertlabels(other.vertlabels) {
    }

    Digraph& operator=(const Digraph& other) {
        if (this != &other) {
            admatrix = other.admatrix;
            vertlabels = other.vertlabels;
        }
        return *this;
    }

    // Add a vertex
    size_t addvertex() {
        size_t old_size = countvert();
        for (size_t i = 0; i < old_size; ++i) {
            admatrix[i].push_back(EdgeLabel{});
        }
        Vector<EdgeLabel> admatrixnewline(old_size + 1, EdgeLabel{});
        admatrix.push_back(admatrixnewline);
        vertlabels.push_back(VertexLabel{});
        return old_size;
    }

    // Set a label for a vertex
    bool setvertlabel(size_t v, const VertexLabel& label) {
        if (!validvertid(v)) {
            return false;
        }
        vertlabels[v] = label;
        return true;
    }

    // Add an edge with a label
    bool addedge(size_t from, size_t to, const EdgeLabel& label) {
        if (!validvertid(from) || !validvertid(to)) {
            return false;
        }
        if (admatrix[from][to] != EdgeLabel{}) {
            return false;
        }
        admatrix[from][to] = label;
        return true;
    }
    // Check if there is an edge between the vertices
    bool hasedge(size_t from, size_t to) const {
        if (!validvertid(from) || !validvertid(to)) {
            return false;
        }
        return admatrix[from][to] != EdgeLabel{};
    }
    // Set a label for an edge
    bool setedgelabel(size_t from, size_t to, const EdgeLabel& label) {
        if (!validvertid(from) || !validvertid(to)) {
            return false;
        }
        if (admatrix[from][to] == EdgeLabel{}) {
            return false;
        }
        admatrix[from][to] = label;
        return true;
    }

    // Get a label for an edge
    EdgeLabel getedgelabel(size_t from, size_t to) const {
        if (!validvertid(from) || !validvertid(to)) {
            return EdgeLabel{};
        }
        EdgeLabel label = admatrix[from][to];
        if (label == EdgeLabel{}) {
            return EdgeLabel{};
        }
        return label;
    }

    // Get the label for the vertex
    VertexLabel getvertexlabel(size_t v) const {
        if (!validvertid(v)) {
            return VertexLabel{};
        }
        return vertlabels[v];
    }

    int getvertexlabelid(const VertexLabel& v) const {
        int res = -1;
        size_t vertlablessize = vertlabels.size();
        for (size_t i = 0; i < vertlablessize; i++) {
            if (v == getvertexlabel(i)) {
                res = (int)i;
                break;
            }
        }
        return res;
    }

    // Delete an edge
    bool removeedge(size_t from, size_t to) {
        if (!validvertid(from) || !validvertid(to)) {
            return false;
        }
        if (admatrix[from][to] == EdgeLabel{}) {
            return false;
        }
        admatrix[from][to] = EdgeLabel{};
        return true;
    }
    // Delete vertex
    bool removevertex(size_t v) {
        if (!validvertid(v)) {
            return false;
        }
        if (countvert() == 0) {
            return false;
        }
        if (countvert() == 1) {
            admatrix.resize(0);
            vertlabels.resize(0);
            return true;
        }
        size_t new_size = countvert() - 1;
        Vector<Vector<EdgeLabel>> new_matrix(new_size);
        Vector<VertexLabel> new_labels(new_size);
        size_t new_i = 0;
        for (size_t i = 0; i < countvert(); i++) {
            if (i == v) continue;
            Vector<EdgeLabel> new_row(new_size);
            size_t new_j = 0;
            for (size_t j = 0; j < countvert(); j++) {
                if (j == v) continue;
                new_row[new_j] = admatrix[i][j];
                new_j++;
            }
            new_matrix[new_i] = new_row;
            new_labels[new_i] = vertlabels[i];
            new_i++;
        }
        admatrix = new_matrix;
        vertlabels = new_labels;
        return true;
    }
    // Get the labels of all vertices as a vector
    Vector<VertexLabel> getallvertexlabels() const {
        return vertlabels;
    }
    size_t countvert() const {
        return vertlabels.size();
    }
    void printadmatrix(std::ostream& os = std::cout) const {
        os << "The adjacency matrix (" << countvert() << " vertexes):\n";
        for (size_t i = 0; i < countvert(); ++i) {
            os << vertlabels.get(i) << '\t' << "  ";
            for (size_t j = 0; j < countvert(); ++j) {
                EdgeLabel label = admatrix[i][j];
                if (label == EdgeLabel{}) {
                    os << " . " << '\t';
                }
                else {
                    os << " " << label << '\t';
                }
            }
            os << "\n";
        }
    }

public:
    class NIterator {
    private:
        const Digraph* ngraph;
        size_t svert;
        size_t currneighbor;
        void nextneighbor() {
            while (currneighbor < ngraph->countvert()) {
                if (ngraph->admatrix[svert][currneighbor] != EdgeLabel{}) {
                    return;
                }
                ++currneighbor;
            }
        }

    public:
        using value_type = std::pair<size_t, EdgeLabel>;
        NIterator(const Digraph* graph, size_t source, size_t start = 0)
            : ngraph(graph), svert(source), currneighbor(start) {
            if (currneighbor < ngraph->countvert()) {
                if (ngraph->admatrix[svert][currneighbor] == EdgeLabel{}) {
                    nextneighbor();
                }
            }
        }
        value_type operator*() const {
            return std::make_pair(
                currneighbor,
                ngraph->admatrix[svert][currneighbor]
            );
        }
        NIterator& operator++() {
            ++currneighbor;
            nextneighbor();
            return *this;
        }
        bool operator==(const NIterator& other) const {
            return ngraph == other.ngraph &&
                svert == other.svert &&
                currneighbor == other.currneighbor;
        }
        bool operator!=(const NIterator& other) const {
            return !(*this == other);
        }
        size_t neighborid() const {
            return currneighbor;
        }
        EdgeLabel edgelabel() const {
            return ngraph->admatrix[svert][currneighbor];
        }
    };
    NIterator nbegin(size_t vertex) const {
        if (!validvertid(vertex)) {
            return NIterator(this, vertex, countvert());
        }
        return NIterator(this, vertex, 0);
    }
    NIterator nend(size_t vertex) const {
        return NIterator(this, vertex, countvert());
    }

};

#endif // GRAPH_H