#include "vector.h"
#include "list.h"

template <typename vertex_mark_type, typename edge_mark_type>
class Graph
{
public:
	struct edge;
	struct vertex;

	struct iterator {
		// This iterator includes all neighbors (both outgoing and incoming)

		vertex *ver;
		typename List<edge*>::Item *ptr;

		bool operator==(iterator &other)
		{
			return other.ptr == this->ptr;
		}

		bool operator!=(iterator &other)
		{
			return !((*this) == other);
		}

		iterator(vertex *ver) : ver(ver)
		{
			if (ver) 
				ptr = ver->edges.first();
			else
				ptr = nullptr;
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
			if (e->from->index == ver->index)
				return *(e->to);
			else
				return *(e->from);
		}
	};

	struct vertex {
		vertex_mark_type mark;
		size_t index;
		List<edge*> edges;

		vertex(vertex_mark_type mark, size_t ind) : mark(mark), index(ind) {};
		vertex(size_t ind) : index(ind) {};

		void set_mark(vertex_mark_type mark)
		{
			this->mark = mark;
		} 

		vertex_mark_type get_mark()
		{
			return mark;
		}

		void remove_edge(size_t ind)
		{
			typename List<edge*>::Item *item = this->edges.first();
			while (item) {
				if ((item->data()) and (item->data()->index == ind))
					break;
				item = item->next();
			}

			if (item) {
				if (item->prev())
					this->edges.erase_next(item->prev());
				else
					this->edges.erase_first();
			}
		}

		void remove_edge(edge *e)
		{
			if (!e)
				throw std::invalid_argument("[remove_edge] The edge pointer is nullptr");
			remove_edge(e->index);
		}

		iterator begin()
		{
			return iterator(this);
		}

		iterator end()
		{
			return iterator(nullptr);
		}
	};

	struct edge {
		edge_mark_type mark;
		vertex *from;
		vertex *to;
		size_t index;

		void set_mark(edge_mark_type mark)
		{
			this->mark = mark;
		} 

		edge_mark_type get_mark()
		{
			return mark;
		}

		edge(edge_mark_type mark, vertex *from, vertex *to, size_t ind) : mark(mark), from(from), to(to), index(ind) {}
	};

	Graph(size_t num_vertices) : count_vertices(num_vertices), count_edges(0)
	{
		vertices.resize(num_vertices, nullptr);
		for (size_t ind = 0; ind < num_vertices; ind++)
			vertices[ind] = new vertex(ind);
	}

	~Graph()
	{
		while (count_edges)
			delete_edge((size_t)0);

		while (count_vertices)
			delete_vertex((size_t)0);
	}

	void set_edge_mark(size_t ind, edge_mark_type mark) 
	{
		if (ind >= count_edges)
			throw std::out_of_range("[set_edge_mark] Incorrect index");

		(edges[ind])->set_mark(mark);
	}

	void set_vertex_mark(size_t ind, vertex_mark_type mark) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[set_vertex_mark] Incorrect index");

		(vertices[ind])->set_mark(mark);
	}

	edge_mark_type get_edge_mark(size_t ind)
	{
		if (ind >= count_edges)
			throw std::out_of_range("[edge_mark_type] Incorrect index");

		return (edges[ind])->get_mark();
	}

	vertex_mark_type get_vertex_mark(size_t ind) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[vertex_mark_type] Incorrect index");

		return (vertices[ind])->get_mark();
	}

	void add_vertex(vertex_mark_type mark) 
	{
		vertices.push_back(new vertex(mark, count_vertices++));
	}

	void add_edge(size_t from_vertex_ind, size_t to_vertex_ind, edge_mark_type mark) 
	{
		if ((from_vertex_ind >= count_vertices) or (to_vertex_ind >= count_vertices))
			throw std::out_of_range("[add_edge] Incorrect index");

		vertex *from_vertex = vertices[from_vertex_ind];
		vertex *to_vertex = vertices[to_vertex_ind];
		edge *new_edge = new edge(mark, from_vertex, to_vertex, count_edges++);
		edges.push_back(new_edge);
		from_vertex->edges.insert(new_edge);
		to_vertex->edges.insert(new_edge);
	}

	void delete_edge(size_t ind)
	{
		if (ind >= count_edges)
			throw std::out_of_range("[delete_edge] Incorrect index");

		edge *e = edges[ind];
		e->from->remove_edge(ind);
		e->to->remove_edge(ind);

		if (ind + 1 != count_edges) {
			edges[ind] = edges[count_edges - 1];
			(edges[ind])->index = ind;
		}

		edges.pop_back();
		count_edges--;
		delete e;
	}

	void delete_edge(edge *e)
	{
		if (!e)
			throw std::invalid_argument("[delete_edge] The edge pointer is nullptr");
		delete_edge(e->index);
	}

	void delete_vertex(size_t ind)
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[delete_vertex] Incorrect index");

		vertex *ver = vertices[ind];
		while (ver->edges.first()) {
			if (ver->edges.first()->data())
				delete_edge(ver->edges.first()->data());
		}

		if (ind + 1 != count_vertices) {
			vertices[ind] = vertices[count_vertices - 1];
			(vertices[ind])->index = ind;
		} 
		
		vertices.pop_back();
		count_vertices--;
		delete ver;
	}

	bool has_edge(vertex *v1, vertex *v2)
	{
		if (!v1 or !v2)
			throw std::invalid_argument("[has_edge] The vertex pointer is nullptr");

		typename List<edge*>::Item *item = v1->edges.first();
		while (item) {
			if (item->data()) {
				if (item->data()->to->index == v2->index)
					return true;
			}
			item = item->next();
		}

		return false;
	}

	bool has_edge(size_t v1, size_t v2)
	{
		if ((v1 >= count_vertices) or (v2 >= count_vertices))
			throw std::out_of_range("[has_edge] Incorrect index");

		return has_edge(vertices[v1], vertices[v2]);
	}

	vertex *get_vertex(size_t ind) 
	{
		if (ind >= count_vertices)
			throw std::out_of_range("[get_vertex] Incorrect index");

		return vertices[ind];
	}

	edge *get_edge(size_t ind) 
	{
		if (ind >= count_edges)
			throw std::out_of_range("[get_edge] Incorrect index");

		return edges[ind];
	}

	Vector<vertex_mark_type> get_all_vertex_marks()
	{
		Vector<vertex_mark_type> ans(count_vertices);
		for (size_t ind = 0; ind < count_vertices; ind++)
			ans[ind] = vertices[ind]->get_mark();
		return ans;
	}

private:
	size_t count_vertices;
	size_t count_edges;
	Vector<vertex*> vertices;
	Vector<edge*> edges;
};