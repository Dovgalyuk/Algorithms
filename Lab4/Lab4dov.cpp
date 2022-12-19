#include <iostream>
#include "dgraph.h"
#include <vector>
#include <climits>

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

void fillGraph(DGraph<Data> graph) 
{
    for (int i = 0; i < VERTICES_COUNT; ++i) 
    {
        graph.add_vertex(Data(i));
    }
    graph.add_edge(FIRST_VERTEX, 1, 10);
    graph.add_edge(FIRST_VERTEX, 3, 30);
    graph.add_edge(FIRST_VERTEX, 4, 100);
    graph.add_edge(1, 2, 50);
    graph.add_edge(3, 4, 60);
    graph.add_edge(3, 2, 20);
    graph.add_edge(2, 4, 10);
}

int main() 
{
    DGraph<Data> graph(0,Data(-1));
    fillGraph(graph);

    auto* vertex = graph.get_vertex(FIRST_VERTEX);
    vertex->cost = 0;
    Data* min_cost_vertex;
    do
    {
        min_cost_vertex = nullptr;
        vertex->was = true;
        for (int i = 0; i < graph.get_vertex_amount(); ++i)
        {
            DGraph<Data>::VertexIterator vertex_iter = graph;
            auto* new_vertex = vertex_iter.graph.get_vertex(i);
            if (!new_vertex->was) 
            {
                int new_cost = new_vertex->cost;
                if (graph.contains_edge_between_vertices(vertex->index, i)) 
                {
                    new_cost = min(new_cost, vertex->cost + graph.get_edge_weight(vertex->index, i));
                    new_vertex->cost = new_cost;
                }
                if (min_cost_vertex == nullptr || new_cost < min_cost_vertex->cost) 
                {
                    cout << vertex->index<<"->";
                    min_cost_vertex = new_vertex;
                }
            }
        }
        vertex = min_cost_vertex;
    } while (min_cost_vertex == nullptr);
    cout<<"\n" << graph.get_vertex(SECOND_VERTEX)->cost;
}
