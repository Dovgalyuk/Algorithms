#pragma once
#include "IGraph.h"
#include "LibraryCPPTemplate/vector.h"

template<class VertexType, class EdgeType>
class AdjacencyMatrixGraph : public IGraph<VertexType, EdgeType> {
private:
    Vector<VertexType> vertices;
    Vector<Vector<std::optional<EdgeType>>> adjacencyMatrix;

    class MatrixNeighborIterator : public IGraph<VertexType, EdgeType>::NeighborIterator {
    private:
        const AdjacencyMatrixGraph& graph;
        std::size_t vertex;
        std::size_t current;

    public:
        MatrixNeighborIterator(const AdjacencyMatrixGraph& g, std::size_t v, bool end = false)
            : graph(g), vertex(v), current(end ? g.vertexCount() : 0) {
            if (!end) {
                while (current < graph.vertexCount() &&
                    !graph.adjacencyMatrix[vertex][current].has_value()) {
                    ++current;
                }
            }
        }

        bool hasNext() const override {
            return current < graph.vertexCount();
        }

        std::tuple<std::size_t, VertexType, EdgeType> next() override {
            if (!hasNext()) {
                throw std::out_of_range("No more neighbors");
            }

            auto result = std::make_tuple(
                current,
                graph.vertices[current],
                graph.adjacencyMatrix[vertex][current].value()
            );

            ++current;
            while (current < graph.vertexCount() &&
                !graph.adjacencyMatrix[vertex][current].has_value()) {
                ++current;
            }

            return result;
        }
    };

public:
    AdjacencyMatrixGraph() = default;

    void initialize(std::size_t vertexCount) override {
        vertices = Vector<VertexType>(vertexCount);
        adjacencyMatrix = Vector<Vector<std::optional<EdgeType>>>(vertexCount);
        for (auto& row : adjacencyMatrix) {
            row = Vector<std::optional<EdgeType>>(vertexCount);
        }
    }

    std::size_t addVertex(const VertexType& vertex) override {
        std::size_t index = vertices.size();
        vertices.push_back(vertex);

        for (auto& row : adjacencyMatrix) {
            row.push_back(std::nullopt);
        }

        adjacencyMatrix.push_back(Vector<std::optional<EdgeType>>(vertices.size()));

        return index;
    }

    void deleteVertex(std::size_t index) override {
        if (index >= vertices.size()) return;

        vertices.erase(vertices.begin() + index);
        adjacencyMatrix.erase(adjacencyMatrix.begin() + index);

        for (auto& row : adjacencyMatrix) {
            row.erase(row.begin() + index);
        }
    }

    void setVertex(std::size_t idx, const VertexType& vertex) override {
        if (idx < vertices.size()) {
            vertices[idx] = vertex;
        }
    }

    const VertexType& getVertex(std::size_t idx) const override {
        return vertices[idx];
    }

    void addEdge(std::size_t from, std::size_t to, const EdgeType& edge) override {
        if (from < vertices.size() && to < vertices.size()) {
            adjacencyMatrix[from][to] = edge;
        }
    }

    void deleteEdge(std::size_t from, std::size_t to) override {
        if (from < vertices.size() && to < vertices.size()) {
            adjacencyMatrix[from][to] = std::nullopt;
        }
    }

    bool hasEdge(std::size_t from, std::size_t to) const override {
        if (from >= vertices.size() || to >= vertices.size()) return false;
        return adjacencyMatrix[from][to].has_value();
    }

    void setEdge(std::size_t from, std::size_t to, const EdgeType& edge) override {
        addEdge(from, to, edge);
    }

    const EdgeType& getEdge(std::size_t from, std::size_t to) const override {
        if (!hasEdge(from, to)) {
            throw std::runtime_error("Edge does not exist");
        }
        return adjacencyMatrix[from][to].value();
    }

    std::size_t vertexCount() const override {
        return vertices.size();
    }

    const Vector<VertexType>& getAllVertices() const override {
        return vertices;
    }

    std::unique_ptr<typename IGraph<VertexType, EdgeType>::NeighborIterator>
        createNeighborIterator(std::size_t vertex) const override {
        return std::make_unique<MatrixNeighborIterator>(*this, vertex);
    }

    std::unique_ptr<typename IGraph<VertexType, EdgeType>::NeighborIterator>
        begin(std::size_t vertex) const override {
        return std::make_unique<MatrixNeighborIterator>(*this, vertex, false);
    }

    std::unique_ptr<typename IGraph<VertexType, EdgeType>::NeighborIterator>
        end(std::size_t vertex) const override {
        return std::make_unique<MatrixNeighborIterator>(*this, vertex, true);
    }
};