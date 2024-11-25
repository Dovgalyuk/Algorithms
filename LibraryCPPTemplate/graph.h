#ifndef GRAPH_H
#define GRAPH_H
#include "vector.h"
#include <vector>
#include <stdexcept>


template<typename Data>
class Graph {
public:
	enum class GraphType {
		Directed,
		Undirected
	};

	Graph(size_t qty_vertex, GraphType type) : type(type) {
		vertices.resize(qty_vertex);
		for (size_t i = 0; i < qty_vertex; i++) {
			vertices.set(i, Vertex(static_cast<int>(i)));
		}
		edgeMatrix.resize(qty_vertex * qty_vertex);
		for (size_t i = 0;i < edgeMatrix.size();i++) {
			edgeMatrix.set(i, nullptr);
		}
	}

	~Graph() {
		clearEdges();
	}

	Graph(const Graph& other) : type(other.type), vertices(other.vertices) {
		edgeMatrix.resize(other.edgeMatrix.size());
		for (size_t i = 0; i < other.edgeMatrix.size(); ++i) {
			if (other.edgeMatrix[i] != nullptr) {
				edgeMatrix[i] = new Edge(*other.edgeMatrix[i]);
			}
			else {
				edgeMatrix[i] = nullptr;
			}
		}
	}

	Graph& operator=(const Graph& other) {
		if (this == &other) {
			return *this;
		}
		clearEdges();

		vertices = other.vertices;
		edgeMatrix.resize(other.edgeMatrix.size());
		for (size_t i = 0; i < other.edgeMatrix.size(); ++i) {
			if (other.edgeMatrix[i] != nullptr) {
				edgeMatrix[i] = new Edge(*other.edgeMatrix[i]);
			}
			else {
				edgeMatrix[i] = nullptr;
			}
		}

		type = other.type;
		return *this;
	}


	struct Edge {
	private:
		Data edgeData;
	public:
		Edge(Data data) : edgeData(data) {}

		void set_EdgeData(Data data) {
			edgeData = data;
		}

		Data get_EdgeData() const {
			return edgeData;
		}
	};

	void add_Edge(size_t startIv, size_t endIv, Data edge_data) {
		size_t qty_vertex = get_VertexAmount();

		Edge*& exists_edge = edgeMatrix[startIv * qty_vertex + endIv];

		if (exists_edge != nullptr) {
			delete exists_edge;
		}

		exists_edge = new Edge(edge_data);

		if (type == GraphType::Undirected) {
			Edge*& exists_ReverseEdge = edgeMatrix[endIv * qty_vertex + startIv];

			if (exists_ReverseEdge != nullptr) {
				delete exists_ReverseEdge;
			}

			exists_ReverseEdge = new Edge(edge_data);
		}
	}




	void remove_Edge(size_t startIv, size_t endIv) {
		if (startIv >= get_VertexAmount() || endIv >= get_VertexAmount()) {
			throw std::out_of_range("Vertex index out of range.");
		}

		size_t index = startIv * get_VertexAmount() + endIv;
		delete edgeMatrix[index];
		edgeMatrix[index] = nullptr;


		if (type == GraphType::Undirected) {
			size_t reverse_Index = endIv * get_VertexAmount() + startIv;
			delete edgeMatrix[reverse_Index];
			edgeMatrix[reverse_Index] = nullptr;
		}
	}

	Edge* get_Edge(size_t startIv, size_t endIv) const {
		size_t qty_vertex = get_VertexAmount();
		return edgeMatrix[startIv * qty_vertex + endIv];
	}

	bool isEdgeExist(size_t startIv, size_t endIv) const {
		return get_Edge(startIv, endIv) != nullptr;
	}


	struct Vertex {
	private:
		Data vertexData;
	public:
		Vertex() : vertexData(Data()) {}

		Vertex(Data vertexData) : vertexData(vertexData) {}

		void set_VertexData(Data newVertexData) {
			this->vertexData = newVertexData;
		}

		Data get_VertexData() const {
			return this->vertexData;
		}


	};

	Vertex& get_Vertex(size_t index) {
		return vertices[index];
	}

	size_t get_VertexAmount() const {
		return vertices.size();
	}


	size_t add_Vertex(Data vertex_data) {
		size_t index = vertices.size();
		vertices.resize(index + 1);
		vertices.set(index, Vertex(vertex_data));

		size_t qty_vertex = get_VertexAmount();
		Vector<Edge*> TimeMatrix;
		TimeMatrix.resize((qty_vertex + 1) * (qty_vertex + 1));


		for (size_t i = 0; i < qty_vertex; i++) {
			for (size_t j = 0; j < qty_vertex; j++) {
				TimeMatrix.set((i * (qty_vertex + 1)) + j, edgeMatrix.get(i * qty_vertex + j));
			}
		}
		edgeMatrix.swap_data(TimeMatrix);
		return index;
	}


	void remove_Vertex(size_t index) {
		size_t qty_vertex = get_VertexAmount();
		if (index >= qty_vertex) {
			return;
		}


		for (size_t i = 0; i < qty_vertex; ++i) {
			Edge* edge = edgeMatrix.get(index * qty_vertex + i);
			if (edge) {
				delete edge;
			}
			edge = edgeMatrix.get(i * qty_vertex + index);
			if (edge) {
				delete edge;
			}
		}


		Vector<Edge*> TimeMatrix;
		TimeMatrix.resize((qty_vertex - 1) * (qty_vertex - 1));

		size_t newIndex = 0;
		for (size_t i = 0; i < qty_vertex; ++i) {
			if (i == index) continue;

			size_t newInnerIndex = 0;
			for (size_t j = 0; j < qty_vertex; ++j) {
				if (j == index) continue;

				Edge* edge = edgeMatrix.get(i * qty_vertex + j);
				TimeMatrix.set(newIndex * (qty_vertex - 1) + newInnerIndex, edge ? new Edge(*edge) : nullptr);
				newInnerIndex++;
			}
			newIndex++;
		}

		edgeMatrix.swap_data(TimeMatrix);
		vertices.resize(qty_vertex - 1);
	}


	std::vector<int> get_AllVertexData() const {
		std::vector<int> allData;
		for (size_t i = 0;i < vertices.size();i++) {
			allData.push_back(vertices[i].get_VertexData());
		}
		return allData;
	}

	struct Iterator {
	private:
		Graph* graph;
		size_t start;
		size_t end;

		size_t get_index_Vertex_near() {
			for (size_t i = end + 1; i < graph->get_VertexAmount(); i++) {
				if (graph->isEdgeExist(start, i)) {
					return i;
				}
			}
			return static_cast<size_t>(-1);
		}

	public:
		Iterator(Graph* graph, size_t start) : graph(graph), start(start), end(static_cast<size_t>(-1)) {
			end = get_index_Vertex_near();
		}

		bool hasNext() const {
			return end != static_cast<size_t>(-1);
		}

		size_t next() {
			if (!hasNext()) {
				throw std::out_of_range("No more adjacent vertices");
			}
			size_t current = end;
			end = get_index_Vertex_near();
			return current;
		}

		size_t get_Index() const {
			return end;
		}

		int get_Start() const {
			return start;
		}
	};


	Iterator get_Iterator(size_t start) {
		return Iterator(this, start);
	}




private:
	void clearEdges() {
		for (size_t i = 0; i < edgeMatrix.size(); i++) {
			delete edgeMatrix.get(i);
			edgeMatrix.set(i, nullptr);
		}
	}
	Vector<Vertex> vertices;
	Vector<Edge*> edgeMatrix;
	GraphType type;
};
#endif