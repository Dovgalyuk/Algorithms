#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <cstddef>

class Graph {
public:

	class Vertex {
	public:
		Vertex(size_t id, int data);
		size_t GetId();
		int GetData();
		void SetData(int data);
		
	private:
		size_t id = 0;
		int data = 0;
	};

	class Edge {
	public:

		Edge() {
			weight = 0;
            id = 0;
			auto* v = new Vertex(id,0);
		}

		Vertex* GetPointV();
		void SetPointV(Vertex& v);
        void SetId(Vertex& v);
        size_t GetId();
		void SetWeight(int weight);		
		int GetWeight();

		~Edge() {
			delete v;
		}

	private:
		Vertex* v = new Vertex(0, 0);
		int weight = 0;
        size_t id = 0;
	};

	Graph();

	Vertex* AddVertex(const int data);

	bool AddEdge(Vertex& u, Vertex& v, int weight);

	bool IsEdge(Vertex& u, Vertex& v);

	bool RemoveVertex(Vertex& u);

	bool RemoveEdge(Vertex& u, Vertex& v);
	
	std::vector<Vertex*> GetVertices();

	std::vector<Vertex*> GetSuccessors(Vertex& u);

private:

	size_t vertexCounter = 0;
	int vertsAmount = 0;

	std::unordered_map<Vertex*, std::unique_ptr<Vertex>> vertices;

	std::unordered_map<Vertex*, std::unordered_set<Edge*>> edges;

};

#endif