#include <iostream>
#include "graph.h"



	Vertex::Vertex(size_t id, int data){
		this->id = id;
		this->data = data;
	};

	size_t const Vertex::getId() {
		return id;
	};

	int const Vertex::getData(){
		return data;
	};
	void Vertex::setData(int data){
		this->data = data;
	};



	Graph::Graph() :
		vertexCounter(0),
		vertices(),
		edges()
	{};

	Vertex* Graph::AddVertex(const int data) {
		auto vertex = std::make_unique<Vertex>(vertexCounter, data);
		vertexCounter++;
		auto* const rawPointer = vertex.get();
		vertices.emplace(rawPointer, std::move(vertex));
		return rawPointer;
	};

	bool Graph::AddEdge(Vertex& u, Vertex& v) {
		auto& uSuccessors = edges[&u];
		if (uSuccessors.find(&v) != uSuccessors.end()) {
			return false;
		}
		else {
			uSuccessors.insert(&v);
			return true;
		}

	};

	bool Graph::RemoveVertex(Vertex& u) {
		if (vertices.find(&u) != vertices.end()) {

			vertices.erase(&u);

			edges.erase(&u);

			for (auto& pair : edges) {
				auto& successors = pair.second;
				if (successors.find(&u) != successors.end()) {
					successors.erase(&u);
				}
			}
			return true;
		}
		else {
			return false;
		}
	};

	bool Graph::RemoveEdge(Vertex& u, Vertex& v) {
		if (vertices.find(&u) != vertices.end() && vertices.find(&v) != vertices.end()) {
			auto& uSuccessors = edges[&u];
			if (uSuccessors.find(&v) != uSuccessors.end()) {
				uSuccessors.erase(&v);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	};
	bool Graph::GetEdge(Vertex& u, Vertex& v) {
		if (vertices.find(&u) != vertices.end() && vertices.find(&v) != vertices.end()) {
			auto& uSuccessors = edges[&u];
			if (uSuccessors.find(&v) != uSuccessors.end()) {
				return true;
			}
			else {
				return false;
			}
		}

	};
	std::vector<Vertex*> Graph::GetVertices() {
		std::vector<Vertex*> copy_vertices;
		copy_vertices.reserve(vertices.size());
		for (auto& pair : vertices) {
			copy_vertices.push_back(pair.first);
		}
		return copy_vertices;
	};


	std::vector<Vertex*> Graph::GetSuccessors(Vertex& u) {
		auto& uSuccessors = edges[&u];
		
		return std::vector<Vertex*>(
			uSuccessors.begin(),
			uSuccessors.end()
		);
	};
