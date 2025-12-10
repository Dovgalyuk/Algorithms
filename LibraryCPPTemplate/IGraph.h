#pragma once
#include <memory>
#include <vector>
#include "LibraryCPPTemplate/vector.h"

template<class VertexType, class EdgeType>
class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void initialize(std::size_t vertexCount) = 0;

    virtual std::size_t addVertex(const VertexType& vertex) = 0;
    virtual void deleteVertex(std::size_t index) = 0;
    virtual void setVertex(std::size_t idx, const VertexType& vertex) = 0;
    virtual const VertexType& getVertex(std::size_t idx) const = 0;

    virtual void addEdge(std::size_t from, std::size_t to, const EdgeType& edge) = 0;
    virtual void deleteEdge(std::size_t from, std::size_t to) = 0;
    virtual bool hasEdge(std::size_t from, std::size_t to) const = 0;
    virtual void setEdge(std::size_t from, std::size_t to, const EdgeType& edge) = 0;
    virtual const EdgeType& getEdge(std::size_t from, std::size_t to) const = 0;

    virtual std::size_t vertexCount() const = 0;
    virtual const Vector<VertexType>& getAllVertices() const = 0;

    class NeighborIterator {
    public:
        virtual ~NeighborIterator() = default;
        virtual bool hasNext() const = 0;
        virtual std::tuple<std::size_t, VertexType, EdgeType> next() = 0;
    };

    virtual std::unique_ptr<NeighborIterator> createNeighborIterator(std::size_t vertex) const = 0;
    virtual std::unique_ptr<NeighborIterator> begin(std::size_t vertex) const = 0;
    virtual std::unique_ptr<NeighborIterator> end(std::size_t vertex) const = 0;
};