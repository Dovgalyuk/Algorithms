#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"
#include "list.h"

template <typename vertex_mark_type, typename edge_mark_type>
class Graph
{
public:
	struct vertex;
	struct edge;

	//............................................................................
	struct iterator {
		// This iterator includes all neighbors (both outgoing and incoming)

		vertex *ver;
		typename List<edge*>::Item *ptr;

		iterator(vertex *ver) : ver(ver)
		{
			if (ver and ver->edges) {
				ptr = ver->edges->first();
			} else {
				ptr = nullptr;
			}
		} 

		bool operator==(iterator &other)
		{
			return other.ptr == this->ptr;
		}

		bool operator!=(iterator &other)
		{
			return !((*this) == other);
		}

		iterator &operator++()
		{
			if (ptr) 
				ptr = ptr->next();

			return *this;
		}

		iterator &operator++(int)
		{
			iterator *temp = this;
			++(*this);
			return *temp;
		}

		vertex operator*()
		{
			if (!ptr)
				throw std::runtime_error("Dereferencing a null iterator");

			edge *e = ptr->data();
			if (e->from == ver)
				return *(e->to);
			else
				return *(e->from);
		}
	};

	struct vertex {
		vertex_mark_type mark;
		List<edge*> *edges; 

		vertex(vertex_mark_type mark, List<edge*> *edges) : mark(mark), edges(edges) {};
		vertex(vertex_mark_type mark) : mark(mark), edges(nullptr) {};
		vertex(List<edge*> *edges) : edges(edges) {};
		vertex() : edges(nullptr) {};

		void set_mark(vertex_mark_type mark)
		{
			this->mark = mark;
		} 

		void set_list_edges(List<edge*> *ptr) 
		{
			edges = ptr;
		}

		vertex_mark_type get_mark()
		{
			return mark;
		}
	};

	struct edge {
		edge_mark_type mark;
		vertex *from;
		vertex *to;
		size_t id;

		edge(edge_mark_type mark, vertex *from, vertex *to, size_t id) : mark(mark), from(from), to(to), id(id) {};
		edge(vertex *from, vertex *to, size_t id) : from(from), to(to), id(id) {};

		void set_mark(vertex_mark_type mark)
		{
			this->mark = mark;
		} 

		edge_mark_type get_mark()
		{
			return mark;
		}
	};

	Graph(size_t num_vertices) : count_vertices(num_vertices), next_edge_id(0)
	{
		adjacency_list.resize(num_vertices, nullptr);
		vertices.resize(num_vertices);
		for (size_t ind = 0; ind < num_vertices; ind++) {
			adjacency_list[ind] = new List<edge*>;
			vertices[ind] = new vertex(adjacency_list[ind]);
		}
	}

	~Graph()
	{
		while (count_vertices)
			delete_vertex((size_t)0);
	}

	void set_edge_mark(size_t id, edge_mark_type mark) 
	{
		edge *e = find_edge(id);
		if (!e)
			throw std::out_of_range("[set_edge_mark] Incorrect id");

		return e->set_mark(mark);
	}

	void set_vertex_mark(size_t ind, vertex_mark_type mark) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[set_vertex_mark] Incorrect index");

		(vertices[ind])->set_mark(mark);
	}

	edge_mark_type get_edge_mark(size_t id)
	{
		edge *e = find_edge(id);
		if (!e)
			throw std::out_of_range("[get_edge_mark] Incorrect id");

		return e->get_mark();
	}

	vertex_mark_type get_vertex_mark(size_t ind) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[get_vertex_mark] Incorrect index");

		return (vertices[ind])->get_mark();
	}

	void add_vertex(vertex_mark_type mark) 
	{
		adjacency_list.push_back(new List<edge*>);
		vertices.push_back(new vertex(mark, adjacency_list[count_vertices++]));
	}

	size_t add_edge(size_t from_vertex_ind, size_t to_vertex_ind, edge_mark_type mark) 
	{
		if ((from_vertex_ind >= count_vertices) or (to_vertex_ind >= count_vertices))
			throw std::out_of_range("[add_edge] Incorrect index");

		vertex *from_vertex = vertices[from_vertex_ind];
		vertex *to_vertex = vertices[to_vertex_ind];
		edge *new_edge = new edge(mark, from_vertex, to_vertex, next_edge_id++);
		adjacency_list[from_vertex_ind]->insert(new_edge);
		adjacency_list[to_vertex_ind]->insert(new_edge);

		return next_edge_id - 1;
	}

	bool has_edge(size_t from_index, size_t to_index)
	{
		if ((from_index >= count_vertices) or (to_index >= count_vertices))
			throw std::out_of_range("[has_edge] Incorrect index");

		typename List<edge*>::Item *item = adjacency_list[from_index]->first();
		while (item) {
			if (item->data()) {
				if (item->data()->to == vertices[to_index])
					return true;
			}
			item = item->next();
		}

		return false;
	}

	edge *find_edge(size_t vertex_index, size_t id)
	{
		typename List<edge*>::Item *item = adjacency_list[vertex_index]->first();
		while (item) {
			if ((item->data()) and (item->data()->id == id))
				break;
			item = item->next();
		}

		if (item)
			return item->data();
		else
			return nullptr;
	}

	edge *find_edge(size_t id)
	{
		edge *ans = nullptr;
		for (size_t ind = 0; (ind < count_vertices) and (!ans); ind++)
			ans = find_edge(ind, id);
		return ans;
	}

	void delete_edge(size_t id)
	{
		edge *e = find_edge(id);
		if (!e)
			throw std::invalid_argument("[delete_edge] The edge was not found");
		delete_edge(e);
	}

	void delete_vertex(size_t ind)
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[delete_vertex] Incorrect index");

		vertex *ver = vertices[ind];
		List<edge*> *edges = adjacency_list[ind];
		while (edges->first()) {
			delete_edge(edges->first()->data());
		}

		if (ind + 1 != count_vertices) {
			adjacency_list[ind] = adjacency_list[count_vertices - 1];
			vertices[ind] = vertices[count_vertices - 1];
		} 
		
		vertices.pop_back();
		adjacency_list.pop_back();
		count_vertices--;
		delete ver;
		delete edges;
	}

	vertex *get_vertex(size_t ind) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[get_vertex] Incorrect index");

		return vertices[ind];
	}

	Vector<vertex_mark_type> get_all_vertex_marks()
	{
		Vector<vertex_mark_type> ans(count_vertices);
		for (size_t ind = 0; ind < count_vertices; ind++)
			ans[ind] = vertices[ind]->get_mark();
		return ans;
	}

	iterator begin(size_t ver_ind)
	{
		if (ver_ind >= count_vertices)
			throw std::out_of_range("[iterator begin] Incorrect index");

		return iterator(vertices[ver_ind]);
	}

	iterator end(size_t ver_ind)
	{
		if (ver_ind >= count_vertices)
			throw std::out_of_range("[iterator end] Incorrect index");
		
		return iterator(nullptr);
	}

private:
	size_t count_vertices;
	size_t next_edge_id;
	Vector<vertex*> vertices;
	Vector<List<edge*>*> adjacency_list;

	void remove_edge(vertex *ver, size_t id)
	{
		typename List<edge*>::Item *item = ver->edges->first();
		while (item) {
			if ((item->data()) and (item->data()->id == id))
				break;
			item = item->next();
		}

		if (item) {
			if (item->prev())
				ver->edges->erase_next(item->prev());
			else
				ver->edges->erase_first();
		}
	}

	void delete_edge(edge *e)
	{
		if (!e)
			throw std::invalid_argument("[delete_edge] The pointer is nullptr");

		remove_edge(e->from, e->id);
		remove_edge(e->to, e->id);

		delete e;
	}
};

#endif