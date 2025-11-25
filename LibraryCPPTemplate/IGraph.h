#pragma once
#include <utility>
#include "PolymorphicIterator.h"
#include "vector.h"

template<class VertexType, class EdgeType>
class IGraph {
public:
	virtual ~IGraph() = default;

	virtual std::unique_ptr<IGraph> clone() const = 0;

	virtual std::size_t addVertex(const VertexType& vertex) = 0;
	virtual void deleteVertex(std::size_t index) = 0;

	virtual void deleteEdge(std::size_t from, std::size_t to) = 0;
	virtual std::size_t addEdge(std::size_t from, std::size_t to, const EdgeType& edge) = 0;

	virtual bool hasEdge(std::size_t from, std::size_t to) const = 0;

	virtual void setVertex(std::size_t idx, const VertexType& vertex) = 0;

	virtual VertexType& getVertex(std::size_t it) = 0;
	virtual const VertexType& getVertex(std::size_t it) const = 0;
	virtual std::size_t vertexCount() const = 0;
	
	virtual void setEdge(std::size_t from, std::size_t to, const EdgeType& edge) = 0;
	virtual EdgeType& getEdge(std::size_t from, std::size_t to) = 0;
	virtual const EdgeType& getEdge(std::size_t from, std::size_t to) const = 0;

	virtual Vector<VertexType>& getAllVertex() = 0;
	virtual const Vector<VertexType>& getAllVertex() const = 0;

	using NeighborIterator = PolymorphicIterator<std::tuple<std::size_t, VertexType, EdgeType>>;

	virtual NeighborIterator begin(std::size_t index) const = 0;
	virtual NeighborIterator end(std::size_t index) const = 0;
};
