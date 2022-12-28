#include <iostream>
#include "dgraph.h"
#include <vector>
#include <climits>

const int VERTICES_COUNT = 5;
const int FIRST_VERTEX = 0;
const int SECOND_VERTEX = 4;

struct Data 
{
    int index = -1;
    int cost = INT_MAX;
    //bool was = false;
    Data(int index) : index(index) {}
};

void fillGraph(DGraph<Data> &graph) 
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
    DGraph<Data> graph(0, Data(-1));
    fillGraph(graph);

    auto* vertex = graph.get_vertex(FIRST_VERTEX);
    DGraph<Data>::Vertex* min_cost_vertex;
    vertex->data.cost = 0;
    do
    {
        min_cost_vertex = nullptr;
        auto near_iter = graph.get_near_vertex_iterator(vertex->data.index);
        for (int i = 0; i < graph.get_vertex_amount(); ++i)
        {
            auto* new_vertex = graph.get_vertex(near_iter.last_index);
            if(near_iter.last_index!=-1)
            { 
                int new_cost = new_vertex->data.cost ;
                if (graph.contains_edge_between_vertices(vertex->data.index, new_vertex->data.index))
                {
                    new_cost = std::min(new_cost, vertex->data.cost + graph.get_edge_weight(vertex->data.index, new_vertex->data.index));
                    new_vertex->data.cost = new_cost;
                }
                if (min_cost_vertex == nullptr || new_cost < min_cost_vertex->data.cost) 
                {
                    std::cout << vertex->data.index << "->";
                    min_cost_vertex = new_vertex;
                }
            }
            near_iter++;
        }
        vertex = min_cost_vertex;
    } while (min_cost_vertex!=nullptr);
    std::cout <<SECOND_VERTEX;
}
