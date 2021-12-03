#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

struct directed_graph
{
	struct vertex
	{
		int label = -1;
	};

	struct edge
	{
		bool exists = 0;
		int label = -1;
	};

	struct iterator
	{
		int	CurrentNeighbor = 0;
		int GivenVertex = -1;
		directed_graph* DirectedGraphPtr;

		bool NeighborListEmpty(int vertex)
		{
			GivenVertex = vertex;
			for (int i = CurrentNeighbor; i < DirectedGraphPtr->vertexes_amount; i++)
			{
				if (DirectedGraphPtr->matrix[(vertex * DirectedGraphPtr->vertexes_amount) + i].exists == 1)
					return false;
			}
			CurrentNeighbor = 0;
			return true;
		}

		int NextNeighborIndex(int vertex)
		{
			GivenVertex = vertex;
			while (DirectedGraphPtr->matrix[(vertex * DirectedGraphPtr->vertexes_amount) + CurrentNeighbor].exists == 0)
			{
				CurrentNeighbor++;
			}
			CurrentNeighbor++;
			return CurrentNeighbor - 1;
		}
		~iterator()
		{
			DirectedGraphPtr->iter = nullptr;
		}
	};

	vertex* vertex_labels;
	edge* matrix;
	iterator* iter;
	int vertexes_amount;

	iterator* createIterator()
	{
		iter = new iterator;
		iter->DirectedGraphPtr = this;
		return iter;
	}

	directed_graph(int vertexes_amount)
	{
		this->vertexes_amount = vertexes_amount;
		vertex_labels = new vertex[vertexes_amount];
		matrix = new edge[vertexes_amount * vertexes_amount];
	}
	~directed_graph()
	{
		delete[] vertex_labels;
		delete[] matrix;
		delete iter;
	}

};

directed_graph* create_directed_graph(int vertexes_amount);

void delete_directed_graph(directed_graph* graph);

void add_vertex(struct directed_graph* graph); //add an vertex by copying the old array to the new array (where is 1 element more)

void add_edge(directed_graph* graph, int vertex1, int vertex2);

void remove_vertex(struct directed_graph* graph, int vertex); //add an vertex by copying the old array to the new array (where is 1 element less)

void remove_edge(directed_graph* graph, int vertex1, int vertex2);

void set_vertex_label(directed_graph* graph, int vertex_index, int vertex_label);

void set_edge_label(directed_graph* graph, int vertex1, int vertex2, int edge_label);

int get_vertex_label(directed_graph* graph, int vertex_index);

int get_edge_label(directed_graph* graph, int vertex1, int vertex2);

bool edge_exists(directed_graph* graph, int vertex1, int vertex2);

directed_graph::iterator* new_iterator(directed_graph* graph);

#endif