#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include "vector.h"

template <typename VertexData, typename EdgeData>
class Graph
{
public:
    struct Cell {
        VertexData vertexData;
        EdgeData edgeData;
        bool edgeExists = true; // По умолчанию все соседи соединены
    };

    class Iterator {
    public:
        Iterator(const Graph* graph, size_t row, size_t col, int dir, int max_dir)
            : graph_(graph), row_(row), col_(col), dir_(dir), max_dir_(max_dir) {
            skipInvalid();
        }

        bool operator!=(const Iterator& other) const { return dir_ != other.dir_; }

        Iterator& operator++() {
            ++dir_;
            skipInvalid();
            return *this;
        }

        size_t operator*() const {
            int r, c;
            getNeighborCoords(dir_, r, c);
            return graph_->toIndex(r, c);
        }

    private:
        const Graph* graph_;
        size_t row_, col_;
        int dir_, max_dir_;

        void skipInvalid() {
            while (dir_ < max_dir_) {
                int r, c;
                getNeighborCoords(dir_, r, c);
                if (r >= 0 && r < (int)graph_->rows_ && c >= 0 && c < (int)graph_->cols_) {
                    if (graph_->grid_.get(graph_->toIndex(r, c)).edgeExists) {
                        break;
                    }
                }
                ++dir_;
            }
        }

        void getNeighborCoords(int dir, int& out_row, int& out_col) const {
            out_row = (int)row_; out_col = (int)col_;
            if (row_ % 2 == 0) {
                if (dir == 0) { out_row--; out_col--; }
                else if (dir == 1) { out_row--; }
                else if (dir == 2) { out_col++; }
                else if (dir == 3) { out_row++; }
                else if (dir == 4) { out_row++; out_col--; }
                else if (dir == 5) { out_col--; }
            }
            else {
                if (dir == 0) { out_row--; }
                else if (dir == 1) { out_row--; out_col++; }
                else if (dir == 2) { out_col++; }
                else if (dir == 3) { out_row++; out_col++; }
                else if (dir == 4) { out_row++; }
                else if (dir == 5) { out_col--; }
            }
        }
    };

    Graph(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        grid_.resize(rows_ * cols_);
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    VertexData getVertexData(size_t row, size_t col) const {
        return grid_.get(toIndex(row, col)).vertexData;
    }

    void setVertexData(size_t row, size_t col, VertexData data) {
        size_t idx = toIndex(row, col);
        Cell c = grid_.get(idx);
        c.vertexData = data;
        grid_.set(idx, c);
    }

    Vector<VertexData> getVertices() const {
        Vector<VertexData> res;
        res.resize(rows_ * cols_);
        for (size_t i = 0; i < rows_ * cols_; ++i) {
            res.set(i, grid_.get(i).vertexData);
        }
        return res;
    }

    bool hasEdge(size_t r1, size_t c1, size_t r2, size_t c2) const {
        if (r1 >= rows_ || c1 >= cols_ || r2 >= rows_ || c2 >= cols_) return false;
        size_t idx = toIndex(r2, c2);
        for (auto it = begin(r1, c1); it != end(r1, c1); ++it) {
            if (*it == idx) return true;
        }
        return false;
    }

    void removeEdge(size_t r1, size_t c1, size_t r2, size_t c2) {
        if (!hasEdge(r1, c1, r2, c2)) return;
        size_t idx = toIndex(r2, c2);
        Cell c = grid_.get(idx);
        c.edgeExists = false;
        grid_.set(idx, c);
    }

    void addEdge(size_t, size_t, size_t r2, size_t c2) {
        size_t idx = toIndex(r2, c2);
        Cell c = grid_.get(idx);
        c.edgeExists = true;
        grid_.set(idx, c);
    }

    EdgeData getEdgeData(size_t, size_t, size_t r2, size_t c2) const {
        return grid_.get(toIndex(r2, c2)).edgeData;
    }

    void setEdgeData(size_t, size_t, size_t r2, size_t c2, EdgeData data) {
        size_t idx = toIndex(r2, c2);
        Cell c = grid_.get(idx);
        c.edgeData = data;
        grid_.set(idx, c);
    }

    Iterator begin(size_t row, size_t col) const { return Iterator(this, row, col, 0, 6); }
    Iterator end(size_t row, size_t col) const { return Iterator(this, row, col, 6, 6); }

private:
    size_t rows_, cols_;
    Vector<Cell> grid_;
    size_t toIndex(size_t row, size_t col) const { return row * cols_ + col; }
};

#endif