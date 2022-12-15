#include "d_graph.h"

using namespace std;

int main() 
{
    int amount = 10;
    auto* graph = new DGraph<int>(amount, 1);
    for (int i = 0; i < amount; ++i) 
    {
        graph->set_vertex_data(i, i);
    }

    for (int i = 0; i < graph->get_vertex_amount(); ++i) 
    {
        if (graph->get_vertex_data(i) != i) 
        {
            cout << "Adding a vertex to the graph does not work correctly.";
            return 1;
        }
    }

    int data = 0;
    auto iterator = graph->get_vertex_iterator();
    while((*iterator) != nullptr) 
    {
        if ((*iterator)->data != data++) 
        {
            std::cout << "The iterator is not working correctly.";
            return 1;
        }
        iterator++;
    }

    graph->add_edge(0, 1, 1);
    graph->add_edge(0, 2, 2);

    for (int i = 0; i < 2; ++i) 
    {
        if (!graph->contains_edge_between_vertices(0, i + 1) ||
                graph->contains_edge_between_vertices(i + 1, 0)) 
        {
            std::cout << "Adding a edge to the graph does not work correctly.";
            return 1;
        }
    }

    graph->set_vertex_data(0, 10);

    if(graph->get_vertex_data(0) != 10) 
    {
        std::cout << "Modifying the vertex data does not work correctly.";
        return 1;
    }

    graph->set_edge_weight(0, 1, 10);

    if(graph->get_edge_weight(0, 1) != 10) 
    {
        std::cout << "Modifying the edge weight does not work correctly.";
        return 1;
    }

    graph->remove_edge(0, 1);

    if (graph->contains_edge_between_vertices(0, 1) ||
            !graph->contains_edge_between_vertices(0, 2)) 
    {
        std::cout << "Removing the edge from the graph does not work correctly.";
        return 1;
    }

    graph->set_vertex_data(0, 1);
    graph->remove_vertex(1);

    data = 1;
    int count = 0;
    iterator = graph->get_vertex_iterator();
    while ((*iterator) != nullptr) 
    {
        count++;
        if ((*iterator)->data != data++) 
        {
            std::cout << "Removing the vertex from the graph does not work correctly.";
            return 1;
        }
        iterator++;
    }
    if (count != 9) 
    {
        std::cout << "Removing the vertex from the graph does not work correctly.";
        return 1;
    }

    graph->set_edge_weight(0, 1, 1);
    graph->add_edge(0, 2, 2);
    graph->add_edge(0, 3, 3);
    graph->add_edge(0, 4, 4);
    graph->add_edge(0, 5, 5);

    auto near_vertices_iterator = graph->get_near_vertex_iterator(0);
    count = 0;
    while ((*near_vertices_iterator) != nullptr) 
    {
        count++;
        near_vertices_iterator++;
    }
    if (count != 5) 
    {
        std::cout << "The near vertex iterator does not work correctly.";
        return 1;
    }
    cout << "All cool!";
    return 0;
}
