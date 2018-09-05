#include "orgraph.h"

struct OrGraph {
	int *vertices;
	int **edges;
	int size;
};

OrGraph *create_orghraph(int vertices) {
	OrGraph *orgraph = new OrGraph;
	orgraph->vertices = new int[vertices];
	orgraph->edges = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		orgraph->vertices[i] = 1;
		orgraph->edges[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			orgraph->edges[i][j] = -1;
		}
	}
	orgraph->size = vertices;
	return orgraph;
}

void delete_orgraph(OrGraph *orgraph) {
	for (int i = 0; i < orgraph->size; i++) {
		delete[] orgraph->edges[i];
	}
	delete[] orgraph->edges;
	delete[] orgraph->vertices;
	delete orgraph;
}

int orgraph_add_vertex(OrGraph *orgraph) {
	orgraph->size++;
	int **tmpEdges = new int*[orgraph->size];
	for (int i = 0; i < orgraph->size - 1; i++) {
		tmpEdges[i] = new int[orgraph->size];
		for (int j = 0; j < orgraph->size - 1; j++) {
			tmpEdges[i][j] = orgraph->edges[i][j];
		}
		tmpEdges[i][orgraph->size - 1] = -1;
	}
	for (int j = 0; j < orgraph->size; j++) {
		tmpEdges[orgraph->size - 1] = new int[orgraph->size];
		tmpEdges[orgraph->size - 1][j] = -1;
		if (j < orgraph->size - 1) {
			delete[] orgraph->edges[j];
		}
	}
	delete[] orgraph->edges;
	orgraph->edges = tmpEdges;

	int *tmpVertices = new int[orgraph->size];
	for (int i = 0; i < orgraph->size - 1; i++) {
		tmpVertices[i] = orgraph->vertices[i];
	}
	tmpVertices[orgraph->size - 1] = 1;
	delete[] orgraph->vertices;
	orgraph->vertices = tmpVertices;
	return orgraph->size - 1;
}

void orgraph_del_vertex(OrGraph *orgraph, int index) {
	orgraph->size--;
	int **tmpEdges = new int*[orgraph->size];
	for (int i = 0; i < orgraph->size; i++) {
		tmpEdges[i] = new int[orgraph->size];
		for (int j = 0; j < orgraph->size; j++) {
			tmpEdges[i][j] = orgraph->edges[i < index ? i : i - 1][
					j < index ? j : j - 1];
		}
	}
	for (int i = 0; i <= orgraph->size; i++) {
		delete[] orgraph->edges[i];
	}
	delete[] orgraph->edges;
	orgraph->edges = tmpEdges;
	int *tmpVertices = new int[orgraph->size];
	for (int i = 0; i < orgraph->size; i++) {
		tmpVertices[i] = orgraph->vertices[i < index ? i : i - 1];
	}
	delete[] orgraph->vertices;
	orgraph->vertices = tmpVertices;
}

void orgraph_add_edge(OrGraph *orgraph, int indexFrom, int indexTo) {
	orgraph->edges[indexFrom][indexTo] = 1;
}

void orgraph_del_edge(OrGraph *orgraph, int indexFrom, int indexTo) {
	orgraph->edges[indexFrom][indexTo] = -1;
}

bool orgraph_edge_exist(OrGraph *orgraph, int indexFrom, int indexTo) {
	return orgraph->edges[indexFrom][indexTo] != -1;
}

void orgraph_set_edge_weight(OrGraph *orgraph, int indexFrom, int indexTo,
		unsigned short weight) {
	orgraph->edges[indexFrom][indexTo] = (int) weight;
}

int orgraph_get_edge_weight(OrGraph *orgraph, int indexFrom, int indexTo) {
	return orgraph->edges[indexFrom][indexTo];
}
void orgraph_set_vertex_label(OrGraph *orgraph, int index, int label) {
	orgraph->vertices[index] = label;
}

int orgraph_get_vertex_label(OrGraph *orgraph, int index) {
	return orgraph->vertices[index];
}

