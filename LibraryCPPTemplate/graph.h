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
	typedef vector<VLabel> Vertex_Labels;

	struct Edge {

		VertexId to;
		ELabel label;
		Edge(VertexId t, ELabel l = ELabel()) : to(t), label(l) {}
	};

	vector<List<typename Graph<VLabel, ELabel>::Edge>> Arr;
	vector<string> names;
	Vertex_Labels vlabels;

	size_t find_vertex(const string& name) {

		for (size_t i = 0; i < names.size(); i++) {

			if (names[i] == name) {
				return i;
			}
		}

		return names.size();
	}


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

		size_t u = find_vertex(name);
		if (u >= names.size()) {
			return NeighborIterator(nullptr);
		}

		return NeighborIterator(Arr[u].first());
	}


	Graph(size_t n = 0) {

		names.resize(n);
		Arr.resize(n);
		vlabels.resize(n);
	}

	VertexId add_vertex(string& name,VLabel vlabel = VLabel()) {

		names.push_back(name);
		Arr.emplace_back();
		vlabels.push_back(vlabel);

		return names.size() - 1;
	}
	
	bool add_edge(string& from, string& to, ELabel& elabel = ELabel()) {
		size_t u = find_vertex(from);
		size_t v = find_vertex(to);

		if (u >= names.size() || v >= names.size()) {
			return false;
		}

		if (edge_exists(from, to)) {
			return false;
		}

		Arr[u].insert({v, elabel });
		return true;
	}

	bool remove_edge(string& from, string& to) {
		size_t u = find_vertex(from);
		size_t v = find_vertex(to);

		if (u >= names.size() || v >= names.size()) {
			return false;
		}

		auto* It = Arr[u].first();

		while (It) {

			if (It->data().to == v) {

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

		size_t u = find_vertex(name);
		if (u >= names.size()) {
			return false;
		}

		for (size_t i = 0; i < Arr.size(); i++) {

			if (i == u) {
				continue;
			}

			remove_edge(names[i], name);
		}
		Arr.erase(Arr.begin() + u);
		names.erase(names.begin() + u);
		vlabels.erase(vlabels.begin() + u);

		return true;
	}

	bool edge_exists(string& from, string& to) {
		size_t u = find_vertex(from);
		size_t v = find_vertex(to);

		if (u >= names.size() || v >= names.size()) {
			return false;
		}
		for (auto* it = Arr[u].first(); it; it = it->next()) {

			if (it->data().to == v) {
				return true;
			}
		}

		return false;
	}

	bool set_vertex_label(string& name, VLabel& vlabel) {
		size_t u = find_vertex(name);
		if (u >= names.size()) {
			return false;
		}
		vlabels[u] = vlabel;
		return true;
	}

	bool get_vertex_label(string& name, VLabel& vlabel) {
		size_t u = find_vertex(name);

		if (u >= names.size()){
			return false;
		}

		vlabel = vlabels[u]; 
		return true;
	}

	bool set_edge_label(string& from, string& to, ELabel& elabel) {
		size_t u = find_vertex(from);
		size_t v = find_vertex(to);

		if (u >= names.size() || v >= names.size()) {
			return false;
		}

		auto* It = Arr[u].first();

		while (It) {

			if (It->data().to == v) {
				It->data().label = elabel;
				return true;
			}

			It = It->next();
		}

		return false;
	}
	bool get_edge_label(string& from, string& to, ELabel& elabel) {

		size_t u = find_vertex(from);
		size_t v = find_vertex(to);
		if (u >= names.size() || v >= names.size()) {
			return false;
		}
		auto* It = Arr[u].first();

		while (It) {

			if (It->data().to == v) {
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

	Vertex_Labels all_vertex_label() {
		return vlabels;
	}

	string vertex_name(VertexId id) {
		if (id >= names.size()) {
			return "";
		}
		return names[id];
	}
};

#endif