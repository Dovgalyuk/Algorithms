#include <iostream>
#include "dgraph.h"
#include <climits>

using namespace std;

const int VERTICES_COUNT = 5;
const int FIRST_VERTEX = 0;
const int SECOND_VERTEX = 4;

struct Data
{
    size_t index = -1;
    int cost = INT_MAX;
    bool was = false;
    Data(int index) : index(index) {};
};

void fillDGraph(DGraph<Data> graph)
{
    for (int i = 0; i < VERTICES_COUNT; i++)
        graph.addVertex(Data(i));
    graph.addEdge(FIRST_VERTEX, 1, 10);
    graph.addEdge(FIRST_VERTEX, 3, 30);
    graph.addEdge(FIRST_VERTEX, 4, 100);
    graph.addEdge(1, 2, 50);
    graph.addEdge(3, 4, 60);
    graph.addEdge(3, 2, 20);
    graph.addEdge(2, 4, 10);
}

int main()
{
    DGraph<Data> graph(0, Data(- 1));
    fillDGraph(graph);

    auto* vertex = graph.getVertex(FIRST_VERTEX);
    auto get_vertex = vertex->getVertexData();
    Data test1 = get_vertex.cost = 0;
    vertex->setVertexData(test1);
    DGraph<Data>::Vertex* min_cost_vertex;
    auto get_min_cost_vertex = min_cost_vertex->getVertexData();
    do
    {
        min_cost_vertex = nullptr;
        get_vertex.was = true;
        for (size_t i = 0; i < graph.getVertexAmount(); ++i)
        {
            auto* new_vertex = graph.getVertex(i);
            auto get_new_vertex = new_vertex->getVertexData();
            if (!get_new_vertex.was)
            {
                int new_cost = get_new_vertex.cost;
                if (graph.isEdge(get_vertex.index, i))
                {
                    auto get_edge = graph.getEdge(get_vertex.index, i);
                    auto get_data_edge = get_edge.getEdgeData();
                    new_cost = min(new_cost, get_vertex.cost + get_data_edge.cost);
                    get_new_vertex.cost = new_cost;
                }
                if (min_cost_vertex == nullptr || new_cost < get_min_cost_vertex.cost)
                {
                    cout << get_vertex.index << "->";
                    min_cost_vertex = new_vertex;
                }
            }
        }
        vertex = min_cost_vertex;
    } while (min_cost_vertex == nullptr);
    auto* second_vert = graph.getVertex(SECOND_VERTEX);
    auto get_second_vertex = second_vert->getVertexData();
    cout << "\n" << get_second_vertex.cost;
}
