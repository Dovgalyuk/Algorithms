#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include "vector.h"
#include "queue.h"
using namespace std;

Vector* breadth_first_search(Vector** graph, size_t vertices_count, size_t start_vertex) {
	Vector* distances = vector_create();
	vector_resize(distances, vertices_count);
	for (size_t i = 0; i <= vertices_count; i++) {
		vector_set(distances, i, INT_MAX);
	}
	Vector* vertex_from = vector_create();
	vector_resize(vertex_from, vertices_count);
	for (size_t i = 0; i <= vertices_count; i++) {
		vector_set(vertex_from, i, -1);
	}
	vector_set(distances, start_vertex, 0);
	Queue* queue = queue_create();
	queue_insert(queue, (int)start_vertex);
	while (!queue_empty(queue)) {
		int vertex = queue_get(queue);
		queue_remove(queue);
		for (size_t i = 0; i < vector_size(graph[vertex]); i++) {
			size_t neighbor = vector_get(graph[vertex], i);
			if (vector_get(distances, neighbor) == INT_MAX) {
				vector_set(distances, neighbor, vector_get(distances, (size_t)vertex) + 1);
				vector_set(vertex_from, neighbor, vertex);
				queue_insert(queue, (int)neighbor);
			}
		}
	}
	queue_delete(queue);
	vector_delete(distances);
	return vertex_from;
}

Vector* vertices_in_shortest_path(Vector* vertex_from, int end_vertex) {
	Vector* shortest_path = vector_create();
	int vertex = end_vertex;
	while (vertex != -1) {
		vector_resize(shortest_path, vector_size(shortest_path) + 1);
		vector_set(shortest_path, vector_size(shortest_path) - 1, vertex);
		vertex = vector_get(vertex_from, vertex);
	}
	return shortest_path;
}

Vector** graph_create_and_read(ifstream& input, size_t& vertices_count, size_t& start_vertex, int& end_vertex) {
	input >> vertices_count >> start_vertex >> end_vertex;
	Vector** graph = (Vector**)malloc((vertices_count + 1) * sizeof(Vector*));
	if (graph != nullptr) {
		for (size_t i = 0; i <= vertices_count; i++) {
			graph[i] = vector_create();
		}
		while (!input.eof()) {
			int arc_start, arc_end;
			input >> arc_start >> arc_end;
			vector_resize(graph[arc_start], vector_size(graph[arc_start]) + 1);
			vector_resize(graph[arc_end], vector_size(graph[arc_end]) + 1);
			vector_set(graph[arc_start], vector_size(graph[arc_start]) - 1, arc_end);
			vector_set(graph[arc_end], vector_size(graph[arc_end]) - 1, arc_start);
		}
	}
	return graph;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		return 1;
	}
	setlocale(LC_ALL, "RUS");
	size_t vertices_count, start_vertex;
	int end_vertex;
	ifstream input(argv[1]);
	if (!(input.is_open())) {
		cout << "Не удалось открыть файл.";
		return 1;
	}
	Vector** graph = graph_create_and_read(input, vertices_count, start_vertex, end_vertex);
	Vector* vertex_from = breadth_first_search(graph, vertices_count, start_vertex);
	Vector* shortest_path = vertices_in_shortest_path(vertex_from, end_vertex);
	ofstream output("output.txt");
	size_t path_size = vector_size(shortest_path);
	if (path_size == 1 && (int)start_vertex != end_vertex) {
		output << "IMPOSSIBLE";
	}
	else {
		for (size_t i = 0; i < path_size; i++) {
			output << vector_get(shortest_path, path_size - 1 - i) << " ";
		}
	}
	for (size_t i = 0; i <= vertices_count; i++) {
		vector_delete(graph[i]);
	}
	free(graph);
	vector_delete(vertex_from);
	vector_delete(shortest_path);
	input.close();
	output.close();
	return 0;
}