#include <iostream>
#include <string>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph graph(3, "V"); 

    if (graph.vertex_count() != 3)
    {
        std::cout << "Invalid initial vertex count\n";
        return 1;
    }

    graph.set_vertex(0, "A");
    graph.set_vertex(1, "B");
    graph.set_vertex(2, "C");

    MyGraph graph_copy = graph;

    for (size_t i = 0; i < graph.vertex_count(); ++i) 
    {
        if (graph.get_vertex(i) != graph_copy.get_vertex(i)) 
        {
            std::cout << "Invalid vertex copy for vertex " << i << "\n";
            return 1;
        }
    }

    graph.set_edge(0, 1, 10);
    graph.set_edge(1, 2, 20);
    graph.set_edge(0, 2, 30);

    if (!graph.has_edge(0, 1) || !graph.has_edge(1, 2) || !graph.has_edge(0, 2)) 
    {
        std::cout << "Invalid add edge\n";
        return 1;
    }

    graph.set_edge(0, 1, 15);
    try
    {
        if (graph.get_edge(0, 1) != 15) 
        {
            std::cout << "Invalid edge val\n";
            return 1;
        }
    } 
    catch(const std::out_of_range& e)
    {
        std::cout << "Invalid get edge: " << e.what() << "\n";
        return 1;
    }

    size_t count_neig = 0;
    bool has_n1 = false;
    bool has_n2 = false;

    for (auto it = graph.begin_neig(0); it != graph.end_neig(0); ++it) 
    {
        size_t neigh = *it;
        try
        {
            std::cout << graph.get_vertex(neigh) << "(" << graph.get_edge(0, neigh) << ") ";
            if(neigh == 1) has_n1 = true;
            if(neigh == 2) has_n2 = true;
            count_neig++;
        }
        catch(const std::out_of_range& e)
        {
            std::cout << graph.get_vertex(neigh) << "Error ";
            return 1;
        }
    }
    std::cout << "\n";

    if(count_neig != 2 || !has_n1 || !has_n2)
    {
        std::cout << "Invalid neighbors\n";
        return 1;
    }

    graph.rem_edge(0, 2);
    if (graph.has_edge(0, 2)) 
    {
        std::cout << "Invalid edge remove\n";
        return 1;
    }

    size_t new_v = graph.add_vertex("D");
    graph.set_edge(new_v, 0, 50);

    if (graph.vertex_count() != 4) 
    {
        std::cout << "Invalid add vertex\n";
        return 1;
    }

    graph.rem_vertex(1); 

    std::cout << "Vertices after removal: ";
    for (size_t i = 0; i < graph.vertex_count(); ++i)
        std::cout << graph.get_vertex(i) << " ";
    std::cout << "\n";

    std::cout << "Neighbors of vertex 0 after removal: ";
    for (auto it = graph.begin_neig(0); it != graph.end_neig(0); ++it) 
    {
        size_t neigh = *it;
        try
        {
            std::cout << graph.get_vertex(neigh) << "(" << graph.get_edge(0, neigh) << ") ";
        }
        catch(const std::out_of_range& e)
        {
            std::cout << graph.get_vertex(neigh) << "Error ";
        }
    }
    std::cout << "\n";
    return 0;
}
