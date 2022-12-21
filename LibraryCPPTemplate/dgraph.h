#ifndef DGRAPH_H
#define DGRAPH_H

#include "vector.h"

template <typename Data> class DGraph 
{
public:
	DGraph(size_t vertex_amount, Data vertex_data)
	{
		vertexes = new Vector<Vertex*>;
		vertexes->resize(vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++)
			vertexes->set(i, new Vertex(vertex_data));
		edge_matrix = new Vector<Edge>;
		edge_matrix->resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < edge_matrix->size(); i++)
			edge_matrix->set(i, NULL);
	}

	~DGraph()
	{
		delete vertexes;
		delete edge_matrix;
	}

	struct Vertex
	{
	protected:
		Data data_vertex;
	public:
		Vertex(Data vertex_data)
		{
			this->data_vertex = vertex_data;
		}	
		void setVertexData(Data vertex_data)
		{
			this->data_vertex = vertex_data;
		}
		Data getVertexData()
		{
			return data_vertex;
		}
	};

	struct Edge
	{
	protected:
		Data data_edge;
	public:
		Edge(Data edge_data)
		{
			this->data_edge = edge_data;
		}
		void setEdgeData(Data edge_data)
		{
			this->data_edge = edge_data;
		}
		Data getEdgeData()
		{
			return data_edge;
		}
	};

	size_t getVertexAmount()
	{
		return vertexes->size();
	}

	struct Iterator
	{
	protected:
		DGraph* graph;
		size_t begin;
		int end = -1;
		int getNearVertexId()
		{
			for (int i = end + 1; i < graph->getVertexAmount; i++)
			{
				if (graph->isEdge(begin, i))
					return i;
			}
			return -1;
		}
	public:
		Iterator(DGraph* graph, size_t begin)
		{
			this->graph = graph;
			this->begin = begin;
			this->end = getNearVertexId();
		}
		Vertex* operator*()
		{
			if (end != -1)
				return graph->getVertex(end);
			else
				return nullptr;
		}
		void operator ++()
		{
			end = getNearVertexId();
		}
	};

	Iterator getIterator(size_t begin)
	{
		return Iterator(this, begin);
	}

	size_t addVertex(Data vertex_data)
	{
		size_t index = vertexes->size();
		vertexes->resize(index + 1);
		vertexes->set(index, new Vertex(vertex_data));
		size_t vertex_amount = getVertexAmount();
		Vector<Edge>* buff_matrix = new Vector<Edge>;
		buff_matrix->resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++)
		{
			for (size_t j = 0; j < vertex_amount; j++)
				buff_matrix->set((i * vertex_amount) + j, edge_matrix->get(i * index + j));
		}
		delete edge_matrix;
		edge_matrix = buff_matrix;
		return index;
	}

	void removeVertex(size_t index)
	{
		size_t _vertex_amount = getVertexAmount();

		if (index >= _vertex_amount)
			return;
		Vertex* vertex = vertexes->get(index);
		delete vertex;
		for (size_t i = index; i < _vertex_amount - 1; i++)
			vertexes->set(i, vertexes->get(i + 1));
		vertexes->resize(_vertex_amount - 1);
		size_t vertex_amount = getVertexAmount();
		Vector<Edge>* buff_matrix = new Vector<Edge>;
		buff_matrix->resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++)
		{
			for (size_t j = 0; j < vertex_amount; j++)
			{
				Edge edge = edge_matrix->get(((i + (i >= index)) * _vertex_amount) + (j + (j >= index)));
				buff_matrix->set((i * vertex_amount) + j, edge);
			}
		}
		delete edge_matrix;
		edge_matrix = buff_matrix;
	}

	Vertex* getVertex(size_t index)
	{
		return vertexes->get(index);
	}

	void addEdge(size_t from_vertex_index, size_t where_vertex_index, Data edge_data)
	{
		Edge edge = Edge(edge_data);
		size_t vertex_amount = getVertexAmount();
		edge_matrix->set(from_vertex_index * vertex_amount + where_vertex_index,edge);
	}

	void removeEdge(size_t from_vertex_index, size_t where_vertex_index)
	{
		size_t vertex_amount = getVertexAmount();
		edge_matrix->set(from_vertex_index * vertex_amount + where_vertex_index, NULL);
	}

	Edge getEdge(size_t from_vertex_index, size_t where_vertex_index)
	{
		size_t vertex_amount = getVertexAmount();
		return edge_matrix->get(from_vertex_index * vertex_amount + where_vertex_index);
	}

	bool isEdge(size_t from_vertex_index, size_t where_vertex_index)
	{
		Edge* edge = new Edge(getEdge(from_vertex_index, where_vertex_index));
		return  edge != nullptr;
	}

	protected:
		Vector<Vertex*>* vertexes;
		Vector<Edge>* edge_matrix;
};
#endif
