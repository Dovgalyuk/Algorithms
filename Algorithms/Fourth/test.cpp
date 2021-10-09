#include <iostream>
#include "directed_graph.h"
#include <vector>
#include <climits>

typedef int Data;
const int VERTICES_COUNT = 5;
const int FIRST_VERTEX = 0;
const int SECOND_VERTEX = 4;

void fillGraph(DirectedGraph<Data>* graph) {
    graph->add_edge(FIRST_VERTEX, 1, 10);
    graph->add_edge(FIRST_VERTEX, 3, 30);
    graph->add_edge(FIRST_VERTEX, 4, 100);
    graph->add_edge(1, 2, 50);
    graph->add_edge(3, 4, 60);
    graph->add_edge(3, 2, 20);
    graph->add_edge(2, 4, 10);

}

template<typename Data>
void fill(Data array[], size_t size, Data value) {
    for (int i = 0; i < size; ++i) {
        array[i] = value;
    }
}

template<typename Data>
bool is_all(Data array[], size_t size, Data value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] != value) return false;
    }
    return true;
}

int main() {
    DirectedGraph<Data>* graph = new DirectedGraph<Data>(VERTICES_COUNT);
    fillGraph(graph);

    int vertex = FIRST_VERTEX;
    int cost = 0;
    int costs[graph->get_vertex_amount()];
    fill(costs, graph->get_vertex_amount(), INT_MAX);

    bool was[graph->get_vertex_amount()];
    fill(was, graph->get_vertex_amount(), false);
    while (!is_all(was, graph->get_vertex_amount(), true)) {
        int min_cost = INT_MAX;
        int min_cost_vertex = -1;
        was[vertex] = true;
        for (int i = 0; i < graph->get_vertex_amount(); ++i) {
            if (!was[i]) {
                int new_cost = costs[i];
                if (graph->contains_edge_between_vertices(vertex, i)) {
                    new_cost = std::min(costs[i], cost + graph->get_edge_weight(vertex, i));
                    costs[i] = new_cost;
                }
                if (new_cost < min_cost) {
                    min_cost = new_cost;
                    min_cost_vertex = i;
                }
            }
        }
        vertex = min_cost_vertex;
        cost = min_cost;
    }
    std::cout << costs[SECOND_VERTEX];
    delete graph;
}