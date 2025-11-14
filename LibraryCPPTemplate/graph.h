#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "list.h"
#include <iostream>

using namespace std;
template<typename VLabel, typename ELabel>

class Graph {

public:

	using VertexId = size_t;

	struct Edge {

		VertexId to;
		ELabel label;
		Edge(VertexId t, ELabel l = ELabel()) : to(t), label(l) {}
	};

private:
	vector<List<typename Graph<VLabel, ELabel>::Edge>> Arr;
	vector<string> names;
	vector<VLabel> vlabels;

	int find_vertex(string& name) {

		for (int i = 0; i < names.size(); i++) {

			if (names[i] == name) {
				return i;
			}
		}

		return -1;
	}
public:

	class NeighborIterator {

	private:
		typename List<Edge>::Item* current_;

	public:
		NeighborIterator(typename List<Edge>::Item* start = nullptr) : current_(start) {}

		VertexId current() const {
			if (current_) {
				return current_->data().to;
			}
			else {
				return VertexId(-1);
			}
		}

		ELabel edge_data() const {
			if (current_) {
				return current_->data().label;
			}
			else {
				return ELabel();
			}
		}
		void next() {
			if (current_) {
				current_ = current_->next();
			}
		}

		bool valid() const {
			return current_ != nullptr;
		}
	};

	NeighborIterator get_neighbors(const string& name) {

		int u = find_vertex(name);
		if (u < 0) {
			return NeighborIterator(nullptr);
		}

		return NeighborIterator(Arr[u].first());
	}


	Graph(size_t n = 0) {

		names.resize(n);
		Arr.resize(n);
		vlabels.resize(n);
	}

	VertexId add_vertex(string& name,VLabel& vlabel = VLabel()) {

		names.push_back(name);
		Arr.emplace_back();
		vlabels.push_back(vlabel);

		return names.size() - 1;
	}
	
	bool add_edge(string& from, string& to, ELabel& elabel = ELabel()) {
		int u = find_vertex(from);
		int v = find_vertex(to);

		if (u < 0 || v < 0) {
			return false;
		}

		Arr[u].insert({(size_t)v, elabel });
		return true;
	}

	bool remove_edge(string& from, string& to) {
		int u = find_vertex(from);
		int v = find_vertex(to);

		if (u < 0 || v < 0) {
			return false;
		}

		auto* It = Arr[u].first();
		typedef typename List<Edge>::Item Item;

		while (It) {

			if (It->data().to == (size_t)v) {

				if (It->prev())
					Arr[u].erase_next(It->prev());
				else
					Arr[u].erase_first();

				return true;
			}

			It = It->next();
		}

		return false;
	}

	bool remove_vertex(string& name) {

		int u = find_vertex(name);
		if (u < 0) {
			return false;
		}

		for (size_t i = 0; i < Arr.size(); i++) {

			if (i == (size_t)u) {
				continue;
			}

			auto* It = Arr[i].first();
			typedef typename List<Edge>::Item Item;

			while (It) {

				if (It->data().to == (size_t)u) {

					Arr[i].erase_next(It->prev());
					It = Arr[i].first();
					continue;
				}


				It = It->next();
			}
		}
		Arr.erase(Arr.begin() + u);
		names.erase(names.begin() + u);
		vlabels.erase(vlabels.begin() + u);

		return true;
	}

	bool edge_exists(string& from, string& to) {
		int u = find_vertex(from);
		int v = find_vertex(to);

		if (u < 0 || v < 0) {
			return false;
		}
		for (auto* it = Arr[u].first(); it; it = it->next()) {

			if (it->data().to == (size_t)v) {
				return true;
			}
		}

		return false;
	}

	bool set_vertex_label(string& name, VLabel& vlabel) {
		int u = find_vertex(name);
		if (u < 0) {
			return false;
		}
		vlabels[u] = vlabel;
		return true;
	}

	bool get_vertex_label(string& name, VLabel& vlabel) {
		int u = find_vertex(name); 

		if (u < 0){
			return false;
		}

		vlabel = vlabels[u]; 
		return true;
	}

	bool set_edge_label(string& from, string& to, ELabel& elabel) {
		int u = find_vertex(from);
		int v = find_vertex(to);

		if (u < 0 || v < 0) {
			return false;
		}

		auto* It = Arr[u].first();
		typedef typename List<Edge>::Item Item;

		while (It) {

			if (It->data().to == (size_t)v) {
				It->data().label = elabel;
				return true;
			}

			It = It->next();
		}

		return false;
	}
	bool get_edge_label(string& from, string& to, ELabel& elabel) {

		int u = find_vertex(from);
		int v = find_vertex(to);
		if (u < 0 || v < 0) {
			return false;
		}
		auto* It = Arr[u].first();
		typedef typename List<Edge>::Item Item;
		while (It) {

			if (It->data().to == (size_t)v) {
				elabel = It->data().label;
				return true;
			}

			It = It->next();
		}
		return false;
	}

	size_t vertex_count() {
		return names.size();
	}

	vector<VLabel> all_vertex_label() {
		return vlabels;
	}

	string vertex_name(VertexId id) {
		if (id >= names.size()) {
			return "";
		}
		return names[id];
	}

	List<Edge>& neighbors(string& name) {
	
		int u = find_vertex(name);
		if (u < 0) {
			throw out_of_range("Vertex not found");
		}
		return Arr[u];
	}

};

#endif