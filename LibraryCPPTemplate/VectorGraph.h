#pragma once
#include "BaseGraph.h"
#include "vector.h"
#include <memory>

using BoolMatrix = Vector<Vector<bool>>;

template<class EdgeType>
using EdgeMatrix = Vector<Vector<EdgeType>>;

template<class VertexType, class EdgeType>
class VectorGraph final : public BaseGraph<VertexType, EdgeType> {
public:

	VectorGraph() : VectorGraph(0) {}
	~VectorGraph() override = default;

	std::unique_ptr<IGraph<VertexType, EdgeType>> clone() const override {
		return std::make_unique<VectorGraph>(*this);
	}

	explicit VectorGraph(const std::size_t vertexCount) {
		for (std::size_t index{ 0 }; index < vertexCount; ++index) {
			addVertex(VertexType{});
		}
	}

	std::size_t addVertex(const VertexType& vertex) override {
		const std::size_t n = vertices.size();
		vertices.push_back(vertex);

		for (auto& row : weights)  row.resize(n + 1);
		for (auto& row : exists)  row.resize(n + 1, false);

		weights.emplace_back(n + 1);
		exists.emplace_back(n + 1);

		return n;
	}

	std::size_t addEdge(std::size_t from, std::size_t to, const EdgeType& edge) override {
		if (from >= vertices.size() || to >= vertices.size()) {
			throw std::out_of_range("index out of range");
		}

		weights[from][to] = std::move(edge);
		exists[from][to] = true;
		return from * vertices.size() + to;
	}

	void deleteVertex(std::size_t index) override {
		if (index >= vertices.size()) {
			throw std::out_of_range("index out of range");
		}

		for (auto& row : weights) row.erase(row.begin() + index);
		for (auto& row : exists) row.erase(row.begin() + index);

		weights.erase(weights.begin() + index);
		exists.erase(exists.begin() + index);

		vertices.erase(vertices.begin() + index);
	}

	VertexType& getVertex(std::size_t index) override {
		return vertices.at(index);
	}

	const VertexType& getVertex(std::size_t index) const override {
		return vertices.at(index);
	}

	std::size_t vertexCount() const override { return vertices.size(); }

	void setVertex(std::size_t index, const VertexType& vertex) override {
		vertices[index] = vertex;
	}

	Vector<VertexType>& getAllVertex() override {
		return vertices;
	}

	const Vector<VertexType>& getAllVertex() const override {
		return vertices;
	}

	void deleteEdge(std::size_t from, std::size_t to) override {
		if (from >= vertices.size() || to >= vertices.size()) {
			throw std::out_of_range("index out of range");
		}

		exists[from][to] = false;
	}

	bool hasEdge(std::size_t from, std::size_t to) const override {
		if (from >= vertices.size() || to >= vertices.size()) {
			return false;
		}

		return exists[from][to];
	}

	EdgeType& getEdge(std::size_t from, std::size_t to) override {
		if (!hasEdge(from, to)) {
			throw std::logic_error("vertex not exists");
		}

		return weights.at(from).at(to);
	}

	const EdgeType& getEdge(std::size_t from, std::size_t to) const override {
		if (!hasEdge(from, to)) {
			throw std::logic_error("vertex not exists");
		}
		return weights.at(from).at(to);
	}

	void setEdge(std::size_t from, std::size_t to, const EdgeType& edge) override {
		if (from >= vertices.size() || to >= vertices.size()) {
			throw std::out_of_range("index out of range");
		}

		weights[from][to] = edge;
		exists[from][to] = true;
	}

	class ConNeighborIterator {
	public:
		using value_type = std::tuple<std::size_t, VertexType, EdgeType>;
		using reference = std::tuple<std::size_t, const VertexType&, const EdgeType&>;

		ConNeighborIterator(const VectorGraph* graph, std::size_t row, std::size_t column)
			: graph(graph), row(row), column(column) {
			if (column < graph->exists[row].size()) {
				advance();
			}
		}

		reference operator*() const {
			return std::tie(column, graph->getVertex(column), graph->getEdge(row, column));
		}

		ConNeighborIterator& operator++() {
			++column;
			advance();
			return *this;
		}

		bool operator==(const ConNeighborIterator& other) const {
			return row == other.row && column == other.column;
		}

		bool operator!=(const ConNeighborIterator& other) const {
			return !(*this == other);
		}

	private:
		const VectorGraph* graph;
		std::size_t row;
		std::size_t column;

		void advance() {
			const auto& rowExists = graph->exists[row];
			const std::size_t size = rowExists.size();

			while (column < size && !rowExists[column]) {
				++column;
			}
		}
	};

	typename VectorGraph::NeighborIterator begin(std::size_t index) const override {
		return typename VectorGraph::NeighborIterator(ConNeighborIterator(this, index, 0));
	}

	typename VectorGraph::NeighborIterator end(std::size_t index) const override {
		return typename VectorGraph::NeighborIterator(ConNeighborIterator(this, index, exists[index].size()));
	}

private:
	Vector<VertexType> vertices;
	BoolMatrix exists;
	EdgeMatrix<EdgeType> weights;
};