#ifndef GRAPH_H
#define GRAPH_H

#include "list.h" 
#include <vector>

template<typename Data>
class Graph {
public:
	
	struct Vertex;

	struct Edge {
		Vertex* vertex;
		int weight;
	};
	
	struct Vertex {
		
		struct Iterator;

		Data data;
		List<Edge> edges;

		Iterator begin() {
			return Iterator{ this->edges.first() };
		}

		struct Iterator {
			typename List<Edge>::Item* item;
			void operator++() {
				item = item->next();
			}
		};

	};

	Graph(int size, Data data) {
		this->vertexes.resize(size);
		for (int i = 0; i < size; i++)
			this->vertexes[i] = new Vertex{ data, List<Edge>() };
	}
	
	~Graph() 
	{
		for (auto vertex : this->vertexes) delete vertex;
	}

	void add_vertex(Data data) {
		auto new_vertex = new Vertex{ data, List<Edge>() };
		this->vertexes.push_back(new_vertex);
	}
	
	void remove_vertex(int index) {
		if (index >= this->vertexes.size() || index < 0) return;
		auto to = vertexes[index];
		for (auto from : vertexes) {
			this->remove_edge(from, to);
		}
		delete to;
		this->vertexes.erase(vertexes.begin() + index);
	}
	
	Vertex* get_vertex(int index) {
		if (index >= this->vertexes.size() || index < 0) return 0;
		return this->vertexes[index];
	}
	
	bool is_edge_exists(Vertex* from, Vertex* to) {
		for (auto i = from->begin(); i.item != 0; ++i) {
			if (i.item->data().vertex == to) {
				return true;
			}
		}
		return false;
	}

	void add_edge(Vertex* from, Vertex* to, int weight) {
		from->edges.insert({ to,weight });
	}

	Edge get_edge(Vertex* from, Vertex* to) {
		for (auto i = from->begin(); i.item != 0; ++i) {
			auto edge = i.item->data();
			if (edge.vertex == to) return edge;
		}
		throw std::runtime_error("There are no edges between these vertices");
	}

	void remove_edge(Vertex* from, Vertex* to) {
		for (auto i = from->begin(); i.item != 0; ++i) {
			if (i.item->data().vertex == to) {
				from->edges.erase(i.item);
				return;
			}
		}
	}

	int size() {
		return this->vertexes.size();
	}

private:
	std::vector<Vertex*> vertexes;
};
#endif