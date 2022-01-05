#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <cstddef>

class Vertex {
	public:
		Vertex(size_t id, int data);

		size_t const getId();

		int const getData();
		void setData(int data);

	private:
		size_t id = 0;
		int data = 0;
};

class Graph {
	public:

		Graph();

		Vertex* AddVertex(const int data);

		bool AddEdge(Vertex& u, Vertex& v);
		bool GetEdge(Vertex& u, Vertex& v);

		bool RemoveVertex(Vertex& u);

		bool RemoveEdge(Vertex& u, Vertex& v);

		std::vector<Vertex*> GetVertices();
		//std::vector<const Vertex*> GetVertices() const;
		std::vector<Vertex*> GetSuccessors(Vertex& u);
		//std::vector< const Vertex*> GetSuccessors() const ;


	private:
		size_t vertexCounter = 0;

		std::unordered_map<Vertex*, std::unique_ptr<Vertex>> vertices;

		std::unordered_map<Vertex*, std::unordered_set<Vertex*>> edges;
};

















#endif