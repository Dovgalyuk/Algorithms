#ifndef GRAPH_H
#define GRAPH_H
#include "vector.hpp"
template <typename vertex_tag, typename edge_tag>
class VertexIterator;

template <typename vertex_tag, typename edge_tag>
class Graph
{
	friend class VertexIterator<vertex_tag, edge_tag>;
	Vector<Vector<bool>> mat;
	size_t size;
	Vector<vertex_tag> vertex_tags;
	Vector<Vector<edge_tag>> edge_tags;
public:
	Graph();
	Graph(const size_t start_size);
	void add_vertex();
	bool add_edge(const size_t a, const size_t b);
	bool remove_vertex(const size_t i);
	bool remove_edge(const size_t a, const size_t b);
	bool is_edge(const size_t a, const size_t b);
	vertex_tag& vertex(const size_t i);
	edge_tag& edge(const size_t a, const size_t b);

	VertexIterator<vertex_tag, edge_tag> vertex_n(const size_t pos);
};

template <typename vertex_tag, typename edge_tag>
Graph<vertex_tag, edge_tag>::Graph()
{
	size = 0;
};

template <typename vertex_tag, typename edge_tag>
Graph<vertex_tag, edge_tag>::Graph(const size_t start_size)
{
	size = start_size;
	mat.resize(size, Vector<bool>(size, false));
	vertex_tags.resize(size);
	edge_tags.resize(size, Vector<edge_tag>(size));
};

template <typename vertex_tag, typename edge_tag>
void Graph<vertex_tag, edge_tag>::add_vertex()
{
	size++;
	for (size_t i = 0; i < mat.size(); i++)
		mat[i].resize(size, false);
	mat.resize(size, Vector<bool>(size, false));
	vertex_tags.resize(size);
	for (size_t i = 0; i < edge_tags.size(); i++)
		edge_tags[i].resize(size);
	edge_tags.resize(size, Vector<edge_tag>(size));
};

template <typename vertex_tag, typename edge_tag>
bool Graph<vertex_tag, edge_tag>::add_edge(const size_t a, const size_t b)
{
	if (a >= size || b >= size)
		return false;
	mat[a][b] = true;
	return true;
};

template <typename vertex_tag, typename edge_tag>
bool Graph<vertex_tag, edge_tag>::remove_vertex(const size_t i)
{
	if (i >= size)
		return false;
	size--;
	for (size_t j = i + 1; j < size; j++)
		vertex_tags[j] = vertex_tags[j + 1];
	vertex_tags.resize(size);
	for (size_t j = 0; j < i; j++)
	{
		for (size_t k = i + 1; k < size; k++)
			edge_tags[j][k] = edge_tags[j][k + 1];
		edge_tags[j].resize(size);
		for (size_t k = i + 1; k < size; k++)
			mat[j][k] = mat[j][k + 1];
		mat[j].resize(size);
	}
	for (size_t j = i; i < size; j++)
	{
		for (size_t k = i + 1; k < size; k++)
			edge_tags[j + 1][k] = edge_tags[j + 1][k + 1];
		edge_tags[j + 1].resize(size);
		for (size_t k = i + 1; k < size; k++)
			mat[j + 1][k] = mat[j + 1][k + 1];
		mat[j + 1].resize(size);
		edge_tags[j] = edge_tags[j + 1];
		mat[j] = mat[j + 1];
	}
	edge_tags.resize(size);
	mat.resize(size);
	return true;
};

template <typename vertex_tag, typename edge_tag>
bool Graph<vertex_tag, edge_tag>::remove_edge(const size_t a, const size_t b)
{
	if (a >= size || b >= size)
		return false;
	mat[a][b] = false;
	return true;
};

template <typename vertex_tag, typename edge_tag>
bool Graph<vertex_tag, edge_tag>::is_edge(const size_t a, const size_t b)
{
	if (a >= size || b >= size)
		return false;
	return mat[a][b];
};

template <typename vertex_tag, typename edge_tag>
vertex_tag& Graph<vertex_tag, edge_tag>::vertex(const size_t i)
{
	return vertex_tags[i];
};

template <typename vertex_tag, typename edge_tag>
edge_tag& Graph<vertex_tag, edge_tag>::edge(const size_t a, const size_t b)
{
	return edge_tags[a][b];
};

template <typename vertex_tag, typename edge_tag>
VertexIterator<vertex_tag, edge_tag> Graph<vertex_tag, edge_tag>::vertex_n(const size_t pos)
{
	return VertexIterator<vertex_tag, edge_tag>(this, pos);
};

template <typename vertex_tag, typename edge_tag>
class VertexIterator
{
	friend class Graph<vertex_tag, edge_tag>;
	size_t vertex;
	size_t curr_n;
	Graph<vertex_tag, edge_tag>* base;
public:
	VertexIterator(Graph<vertex_tag, edge_tag>* base, const size_t vertex);
	size_t operator++();
	size_t operator*();
	bool operator==(const VertexIterator<vertex_tag, edge_tag>& n);
	bool operator!=(const VertexIterator<vertex_tag, edge_tag>& n);
};

template <typename vertex_tag, typename edge_tag>
VertexIterator<vertex_tag, edge_tag>::VertexIterator(Graph<vertex_tag, edge_tag>* base, const size_t vertex)
{
	this->vertex = vertex;
	curr_n = -1;
	this->base = base;
	for (size_t i = 0; i < base->mat.size(); i++)
		if (base->mat[vertex][i])
		{
			curr_n = i;
			return;
		}
};

template <typename vertex_tag, typename edge_tag>
size_t VertexIterator<vertex_tag, edge_tag>::operator++()
{
	if (curr_n == -1)
		return curr_n;
	for (size_t i = curr_n + 1; i < base->mat.size(); i++)
		if (base->mat[vertex][i])
		{
			curr_n = i;
			return curr_n;
		}
	for (size_t i = 0; i <= curr_n; i++)
		if (base->mat[vertex][i])
		{
			curr_n = i;
			return curr_n;
		}
	return curr_n;
};

template <typename vertex_tag, typename edge_tag>
size_t VertexIterator<vertex_tag, edge_tag>::operator*()
{
	return curr_n;
};

template <typename vertex_tag, typename edge_tag>
bool VertexIterator<vertex_tag, edge_tag>::operator==(const VertexIterator<vertex_tag, edge_tag>& n)
{
	return (base == n.base && n.curr_n == curr_n && n.vertex == vertex);
};

template <typename vertex_tag, typename edge_tag>
bool VertexIterator<vertex_tag, edge_tag>::operator!=(const VertexIterator<vertex_tag, edge_tag>& n)
{
	return !(*this == n);
};
#endif