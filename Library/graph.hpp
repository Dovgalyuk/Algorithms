#ifndef GRAPH_H
#define GRAPH_H
#include "vector.hpp"
template<typename tags_type>
class VertexIterator;

template <typename tags_type = int>
class Graph
{
	friend class VertexIterator<tags_type>;
	Vector<Vector<bool>> mat;
	size_t size;
	Vector<tags_type> vertex_tags;
	Vector<Vector<tags_type>> edge_tags;
public:
	Graph();
	Graph(size_t start_size);
	void add_vertex();
	bool add_edge(size_t a, size_t b);
	bool remove_vertex(size_t i);
	bool remove_edge(size_t a, size_t b);
	bool is_edge(size_t a, size_t b);
	tags_type& vertex(size_t i);
	tags_type& edge(size_t a, size_t b);

	VertexIterator<tags_type> vertex_n(size_t pos);
};

template <typename tags_type>
Graph<tags_type>::Graph()
{
	size = 0;
};

template <typename tags_type>
Graph<tags_type>::Graph(size_t start_size)
{
	size = start_size;
	mat.resize(size, Vector<bool>(size, false));
	vertex_tags.resize(size);
	edge_tags.resize(size, Vector<tags_type>(size));
};

template <typename tags_type>
void Graph<tags_type>::add_vertex()
{
	size++;
	for (size_t i = 0; i < mat.size(); i++)
		mat[i].resize(size, false);
	mat.resize(size, Vector<bool>(size, false));
	vertex_tags.resize(size);
	for (size_t i = 0; i < edge_tags.size(); i++)
		edge_tags[i].resize(size);
	edge_tags.resize(size, Vector<tags_type>(size));
};

template <typename tags_type>
bool Graph<tags_type>::add_edge(size_t a, size_t b)
{
	if (a >= size || b >= size)
		return false;
	mat[a][b] = true;
	return true;
};

template <typename tags_type>
bool Graph<tags_type>::remove_vertex(size_t i)
{
	if (i >= size)
		return false;
	size--;
	for (size_t j = i + 1; i < size; i++)
		vertex_tags[j] = vertex_tags[j + 1];
	vertex_tags.resize(size);
	for (size_t j = 0; j < i; j++)
	{
		edge_tags[j].resize(size);
		mat[i].resize(size);
	}
	for (size_t j = i; i < size; i++)
	{
		edge_tags[j + 1].resize(size);
		mat[j + 1].resize(size);
		edge_tags[j] = edge_tags[j + 1];
		mat[j] = mat[j + 1];
	}
	edge_tags.resize(size);
	mat.resize(size);
};

template <typename tags_type>
bool Graph<tags_type>::remove_edge(size_t a, size_t b)
{
	if (a >= size || b >= size)
		return false;
	mat[a][b] = false;
	return true;
};

template <typename tags_type>
bool Graph<tags_type>::is_edge(size_t a, size_t b)
{
	if (a >= size || b >= size)
		return false;
	return mat[a][b];
};

template <typename tags_type>
tags_type& Graph<tags_type>::vertex(size_t i)
{
	return vertex_tags[i];
};

template <typename tags_type>
tags_type& Graph<tags_type>::edge(size_t a, size_t b)
{
	if (a >= size || b >= size)
		return tags_type();
	return edge_tags[a][b];
};

template <typename tags_type>
VertexIterator<tags_type> Graph<tags_type>::vertex_n(size_t pos)
{
	return VertexIterator<tags_type>(this, pos);
};

template<typename tags_type>
class VertexIterator
{
	friend class Graph<tags_type>;
	size_t vertex;
	size_t curr_n;
	Graph<tags_type>* base;
public:
	VertexIterator(Graph<tags_type>* base, size_t vertex);
	size_t operator++();
	size_t operator*();
	bool operator==(VertexIterator<tags_type>& n);
	bool operator!=(VertexIterator<tags_type>& n);
};

template<typename tags_type>
VertexIterator<tags_type>::VertexIterator(Graph<tags_type>* base, size_t vertex)
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

template<typename tags_type>
size_t VertexIterator<tags_type>::operator++()
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
};

template<typename tags_type>
size_t VertexIterator<tags_type>::operator*()
{
	return curr_n;
};

template<typename tags_type>
bool VertexIterator<tags_type>::operator==(VertexIterator<tags_type>& n)
{
	return (&base == &(n.base) && n.curr_n == curr_n && n.vertex == vertex);
};

template<typename tags_type>
bool VertexIterator<tags_type>::operator!=(VertexIterator<tags_type>& n)
{
	return !(n == *this);
};
#endif