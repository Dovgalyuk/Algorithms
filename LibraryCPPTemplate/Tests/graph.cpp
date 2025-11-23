#include <iostream>
#include "graph.h"

typedef Graph<int, int> MyGraph;

int main()
{
    MyGraph* g = new MyGraph(3);

    if (!g)
    {
        std::cout << "Graph creation error\n";
        return 1;
    }

    if (g->get_vertex_count() != 3)
    {
        std::cout << "graph_vertex_count error\n";
        delete g;
        return 1;
    }

    g->set_vertex_label(0, 10);
    g->set_vertex_label(1, 20);
    g->set_vertex_label(2, 30);

    if (g->get_vertex_label(0) != 10 ||
        g->get_vertex_label(1) != 20 ||
        g->get_vertex_label(2) != 30)
    {
        std::cout << "graph_vertex_label error\n";
        delete g;
        return 1;
    }

    *g = *g;

    g->add_edge(0, 1, 5);
    g->add_edge(0, 2, 7);
    g->add_edge(1, 2, 3);

    if (!g->has_edge(0, 1) || !g->has_edge(0, 2) || !g->has_edge(1, 2))
    {
        std::cout << "graph_add_edge / has_edge error\n";
        delete g;
        return 1;
    }

    {
        MyGraph::NeighborIterator it = g->neighbors(0);

        bool seen1 = false;
        bool seen2 = false;

        while (it.valid())
        {
            size_t v = it.vertex_id();
            if (v == 1) seen1 = true;
            if (v == 2) seen2 = true;
            it.next();
        }

        if (!seen1 || !seen2)
        {
            std::cout << "graph_neighbor_iterator error\n";
            delete g;
            return 1;
        }
    }

    g->remove_edge(0, 1);
    if (g->has_edge(0, 1))
    {
        std::cout << "graph_remove_edge error\n";
        delete g;
        return 1;
    }

    MyGraph copy(*g);
    if (copy.get_vertex_count() != g->get_vertex_count() ||
        !copy.has_edge(0, 2) || !copy.has_edge(1, 2))
    {
        std::cout << "graph_copy_ctor error\n";
        delete g;
        return 1;
    }

    MyGraph other(0);
    other = copy;
    if (other.get_vertex_count() != copy.get_vertex_count() ||
        !other.has_edge(0, 2) || !other.has_edge(1, 2))
    {
        std::cout << "graph_assignment error\n";
        delete g;
        return 1;
    }

    g->remove_vertex(2);
    if (g->has_edge(0, 2) || g->has_edge(1, 2))
    {
        std::cout << "graph_remove_vertex error\n";
        delete g;
        return 1;
    }

    std::cout << "Graph tests passed\n";

    delete g;
    return 0;
}
