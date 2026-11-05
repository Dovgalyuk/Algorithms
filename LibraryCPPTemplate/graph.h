#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

#include <cstddef>
#include <istream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

template <typename VertexLabel, typename EdgeLabel>
class Graph
{
public:
    explicit Graph(std::size_t vertexCount = 0)
    {
        resize(vertexCount);
    }

    Graph(std::size_t rows, std::size_t cols)
    {
        resize(rows * cols);
        buildGrid(rows, cols);
    }

    void addVertex(const VertexLabel& label)
    {
        if (indexToLabel_.find(label) != indexToLabel_.end())
            throw std::invalid_argument("Graph::addVertex: vertex already exists");

        std::size_t newIndex = vertexLabels_.size();
        vertexLabels_.push_back(label);
        indexToLabel_[label] = newIndex;

        Vector<std::optional<EdgeLabel>> newRow;
        newRow.resize(newIndex + 1);
        adj_.push_back(newRow);

        for (std::size_t i = 0; i < newIndex; ++i)
            resizeRow(i, newIndex + 1);
    }

    void resize(std::size_t newVertexCount)
    {
        std::size_t oldCount = vertexLabels_.size();
        if (newVertexCount == oldCount)
            return;

        if (newVertexCount < oldCount) {
            while (vertexLabels_.size() > newVertexCount)
                removeLastVertex();
            return;
        }

        for (std::size_t i = oldCount; i < newVertexCount; ++i)
            addVertex(VertexLabel("v") + std::to_string(i));
    }

    void removeVertex(const VertexLabel& label)
    {
        std::size_t idx = indexOf(label);
        std::size_t last = vertexLabels_.size() - 1;

        for (std::size_t i = 0; i <= last; ++i)
            removeColumn(i, idx, last);

        for (std::size_t i = idx; i < last; ++i)
            adj_.set(i, adj_.get(i + 1));
        adj_.resize(last);

        for (std::size_t i = idx; i < last; ++i)
            vertexLabels_.set(i, vertexLabels_.get(i + 1));
        vertexLabels_.resize(last);

        indexToLabel_.erase(label);
        for (std::size_t i = 0; i < last; ++i)
            indexToLabel_[vertexLabels_.get(i)] = i;
    }

    void addEdge(const VertexLabel& from, const VertexLabel& to,
        const EdgeLabel& label = EdgeLabel{})
    {
        setCell(indexOf(from), indexOf(to), label);
    }

    void removeEdge(const VertexLabel& from, const VertexLabel& to)
    {
        setCell(indexOf(from), indexOf(to), std::nullopt);
    }

    bool hasEdge(const VertexLabel& from, const VertexLabel& to) const
    {
        return getCell(indexOf(from), indexOf(to)).has_value();
    }

    void setEdgeLabel(const VertexLabel& from, const VertexLabel& to,
        const EdgeLabel& label)
    {
        setCell(indexOf(from), indexOf(to), label);
    }

    EdgeLabel getEdgeLabel(const VertexLabel& from, const VertexLabel& to) const
    {
        std::optional<EdgeLabel> cell = getCell(indexOf(from), indexOf(to));
        if (!cell.has_value())
            throw std::runtime_error("Graph::getEdgeLabel: edge does not exist");
        return *cell;
    }

    void setVertexLabel(const VertexLabel& oldLabel, const VertexLabel& newLabel)
    {
        if (oldLabel == newLabel)
            return;
        if (indexToLabel_.find(newLabel) != indexToLabel_.end())
            throw std::invalid_argument("Graph::setVertexLabel: label already exists");

        std::size_t idx = indexOf(oldLabel);
        vertexLabels_.set(idx, newLabel);
        indexToLabel_.erase(oldLabel);
        indexToLabel_[newLabel] = idx;
    }

    VertexLabel getVertexLabel(std::size_t index) const
    {
        if (index >= vertexLabels_.size())
            throw std::out_of_range("Graph::getVertexLabel: index out of range");
        return vertexLabels_.get(index);
    }

    std::vector<VertexLabel> getAllVertexLabels() const
    {
        std::vector<VertexLabel> result;
        result.reserve(vertexLabels_.size());
        for (std::size_t i = 0; i < vertexLabels_.size(); ++i)
            result.push_back(vertexLabels_.get(i));
        return result;
    }

    std::size_t vertexCount() const { return vertexLabels_.size(); }

    std::vector<std::vector<EdgeLabel>>
        toWeightMatrix(const EdgeLabel& absent, const EdgeLabel& diag) const
    {
        const std::size_t n = vertexLabels_.size();
        std::vector<std::vector<EdgeLabel>> m(
            n, std::vector<EdgeLabel>(n, absent));

        for (std::size_t i = 0; i < n; ++i) {
            m[i][i] = diag;
            for (std::size_t j = 0; j < n; ++j) {
                std::optional<EdgeLabel> cell = getCell(i, j);
                if (cell.has_value())
                    m[i][j] = *cell;
            }
        }
        return m;
    }

    void readFromStream(std::istream& is)
    {
        std::size_t n = 0;
        if (!(is >> n))
            throw std::runtime_error("Graph::readFromStream: cannot read vertex count");

        vertexLabels_.resize(0);
        adj_.resize(0);
        indexToLabel_.clear();

        for (std::size_t i = 0; i < n; ++i) {
            VertexLabel label;
            if (!(is >> label))
                throw std::runtime_error("Graph::readFromStream: cannot read vertex label");
            addVertex(label);
        }

        std::size_t m = 0;
        if (!(is >> m))
            throw std::runtime_error("Graph::readFromStream: cannot read edge count");

        for (std::size_t k = 0; k < m; ++k) {
            VertexLabel from, to;
            EdgeLabel label{};
            if (!(is >> from >> to >> label))
                throw std::runtime_error("Graph::readFromStream: cannot read edge");
            addEdge(from, to, label);
        }
    }

    class NeighborIterator
    {
    public:
        NeighborIterator(const Graph* g, std::size_t source, std::size_t current)
            : graph_(g), source_(source), current_(current)
        {
            skipEmpty();
        }

        VertexLabel operator*() const
        {
            return graph_->vertexLabels_.get(current_);
        }

        NeighborIterator& operator++()
        {
            ++current_;
            skipEmpty();
            return *this;
        }

        bool operator!=(const NeighborIterator& other) const
        {
            return current_ != other.current_;
        }

        bool operator==(const NeighborIterator& other) const
        {
            return current_ == other.current_;
        }

    private:
        void skipEmpty()
        {
            std::size_t n = graph_->vertexLabels_.size();
            while (current_ < n && !graph_->getCell(source_, current_).has_value())
                ++current_;
        }

        const Graph* graph_;
        std::size_t source_;
        std::size_t current_;
    };

    NeighborIterator neighborsBegin(const VertexLabel& vertex) const
    {
        return NeighborIterator(this, indexOf(vertex), 0);
    }

    NeighborIterator neighborsEnd(const VertexLabel& vertex) const
    {
        return NeighborIterator(this, indexOf(vertex), vertexLabels_.size());
    }

    template <typename F>
    void forEachEdge(F&& fn) const
    {
        const std::size_t n = vertexLabels_.size();
        for (std::size_t i = 0; i < n; ++i) {
            auto row = adj_.get(i);
            for (std::size_t j = 0; j < row.size(); ++j) {
                auto cell = row.get(j);
                if (cell.has_value())
                    fn(i, j, *cell);
            }
        }
    }

private:
    std::size_t indexOf(const VertexLabel& label) const
    {
        auto it = indexToLabel_.find(label);
        if (it == indexToLabel_.end())
            throw std::invalid_argument("Graph: unknown vertex label");
        return it->second;
    }

    std::optional<EdgeLabel> getCell(std::size_t i, std::size_t j) const
    {
        return adj_.get(i).get(j);
    }

    void setCell(std::size_t i, std::size_t j, const std::optional<EdgeLabel>& value)
    {
        Vector<std::optional<EdgeLabel>> row = adj_.get(i);
        row.set(j, value);
        adj_.set(i, row);
    }

    void resizeRow(std::size_t rowIndex, std::size_t newSize)
    {
        Vector<std::optional<EdgeLabel>> row = adj_.get(rowIndex);
        row.resize(newSize);
        adj_.set(rowIndex, row);
    }

    void removeColumn(std::size_t rowIndex, std::size_t colIndex, std::size_t last)
    {
        Vector<std::optional<EdgeLabel>> row = adj_.get(rowIndex);
        for (std::size_t j = colIndex; j < last; ++j)
            row.set(j, row.get(j + 1));
        row.resize(last);
        adj_.set(rowIndex, row);
    }

    void removeLastVertex()
    {
        std::size_t last = vertexLabels_.size() - 1;
        indexToLabel_.erase(vertexLabels_.get(last));
        vertexLabels_.resize(last);
        adj_.resize(last);
        for (std::size_t i = 0; i < last; ++i)
            resizeRow(i, last);
    }

    void buildGrid(std::size_t rows, std::size_t cols)
    {
        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) {
                std::size_t u = r * cols + c;
                if (c + 1 < cols)
                    setCell(u, u + 1, EdgeLabel{});
                if (r + 1 < rows)
                    setCell(u, u + cols, EdgeLabel{});
            }
        }
    }

    Vector<VertexLabel> vertexLabels_;
    Vector<Vector<std::optional<EdgeLabel>>> adj_;
    std::unordered_map<VertexLabel, std::size_t> indexToLabel_;
};

#endif