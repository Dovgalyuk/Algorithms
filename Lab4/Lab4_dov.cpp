#include <iostream>
#include "d_graph.h"
#include <vector>

using namespace std;

const int VERTICES_COUNT = 5;
const int FIRST_VERTEX = 0;
const int SECOND_VERTEX = 4;

struct Data 
{
    int index = -1;
    int cost = INT_MAX;
    bool was = false;
    Data(int index) : index(index) {}
};

void fillGraph(DGraph<Data>* graph) 
{
    for (int i = 0; i < VERTICES_COUNT; ++i) 
    {
        graph->add_vertex(Data(i));
    }
    graph->add_edge(FIRST_VERTEX, 1, 10);
    graph->add_edge(FIRST_VERTEX, 3, 30);
    graph->add_edge(FIRST_VERTEX, 4, 100);
    graph->add_edge(1, 2, 50);
    graph->add_edge(3, 4, 60);
    graph->add_edge(3, 2, 20);
    graph->add_edge(2, 4, 10);

}

int main() 
{
    DGraph<Data>* graph = new DGraph<Data>(0, Data(-1));
    fillGraph(graph);

    auto* vertex = graph->get_vertex(FIRST_VERTEX);
    vertex->data.cost = 0;
    bool is_empty = false;
    while (!is_empty) 
    {
        is_empty = true;
        DGraph<Data>::Vertex* min_cost_vertex = nullptr;
        vertex->data.was = true;
        for (int i = 0; i < graph->get_vertex_amount(); ++i) 
        {
            DGraph<Data>::VertexIterator vertex_iter = graph;
            auto* new_vertex = vertex_iter.graph->get_vertex(i);
            if (!new_vertex->data.was) 
            {
                int new_cost = new_vertex->data.cost;
                if (graph->contains_edge_between_vertices(vertex->data.index, i)) 
                {
                    new_cost = min(new_cost, vertex->data.cost + graph->get_edge_weight(vertex->data.index, i));
                    new_vertex->data.cost = new_cost;
                }
                if (min_cost_vertex == nullptr || new_cost < min_cost_vertex->data.cost) 
                {
                    min_cost_vertex = new_vertex;
                }
                is_empty = false;
            }
        }
        vertex = min_cost_vertex;
    }
    cout << graph->get_vertex(SECOND_VERTEX)->data.cost;
    delete graph;
}
