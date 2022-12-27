#include <iostream>
#include "graph.h"
#include <vector>

using namespace std;

const int VERTICES_COUNT = 5;
const int FIRST_VERTEX = 0;
bool visited[VERTICES_COUNT];
vector <int> comp;

void dfs(int v, Graph<Data> graph) {
    visited[v] = true;
    comp.push_back(v);
    for (size_t i = 0; i < graph.get_vertex_amount(); i++) {
        if ((graph.contains_edge_between_vertices(v, i) != false) && (!visited[i])) {
            dfs(i, graph);
        }
    }
}

void find_comp(Graph<Data> graph) {
    for (int i = 0; i < VERTICES_COUNT; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < VERTICES_COUNT; i++) {
        if (!visited[i]) {
            comp.clear();
            dfs(i, graph);

            cout << "Component:";
            for (size_t j = 0; j < comp.size(); ++j)
                cout << ' ' << comp[j];
            cout << endl;
        }
    }
}

int main() {
	Graph<Data> graph(0, 0);
	for (int i = 0; i < VERTICES_COUNT; i++) {
		graph.add_vertex(i);
	}
    graph.add_edge(FIRST_VERTEX, 1, 10);
    graph.add_edge(FIRST_VERTEX, 3, 30);
    graph.add_edge(FIRST_VERTEX, 4, 100);
    graph.add_edge(1, 2, 50);
    graph.add_edge(3, 4, 60);
    graph.add_edge(3, 2, 20);
    graph.add_edge(2, 4, 10);
    find_comp(graph);
    return 0;
}