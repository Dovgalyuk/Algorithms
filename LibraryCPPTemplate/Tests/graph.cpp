#include <iostream>
#include "graph.h"

int main()
{
    Graph<int, int> mygraph(4);

    if (mygraph.get_vertex_count() != 4)
    {
        std::cout << "graph_vertex_count error\n";
        return 1;
    }

    mygraph.set_vertex_label(0, 25);
    mygraph.set_vertex_label(1, 50);
    mygraph.set_vertex_label(2, 75);
    mygraph.set_vertex_label(3, 100);

    if (mygraph.get_vertex_label(0) != 25 ||
        mygraph.get_vertex_label(1) != 50 ||
        mygraph.get_vertex_label(2) != 75 ||
        mygraph.get_vertex_label(3) != 100)
    {
        std::cout << "graph_vertex_label error\n";
        return 1;
    }

    mygraph.add_edge(0, 1, 8);
    mygraph.add_edge(0, 2, 12);
    mygraph.add_edge(1, 2, 6);
    mygraph.add_edge(2, 3, 9);
    mygraph.add_edge(3, 0, 15);

    if (!mygraph.has_edge(0, 1) || !mygraph.has_edge(0, 2) ||
        !mygraph.has_edge(1, 2) || !mygraph.has_edge(2, 3) ||
        !mygraph.has_edge(3, 0))
    {
        std::cout << "graph_add_edge error\n";
        return 1;
    }

    if (mygraph.get_edge_label(0, 1) != 8 ||
        mygraph.get_edge_label(2, 3) != 9 ||
        mygraph.get_edge_label(3, 0) != 15)
    {
        std::cout << "graph_edge_label error\n";
        return 1;
    }

    {
        Graph<int, int>::NeighborIterator it = mygraph.neighbors(0);
        int count1 = 0;
        int count2 = 0;

        while (it.valid())
        {
            size_t v = it.vertex_id();
            if (v == 1) count1++;
            if (v == 2) count2++;
            it.next();
        }

        if (count1 != 1 || count2 != 1)
        {
            std::cout << "graph_neighbor_iterator error\n";
            return 1;
        }
    }

    mygraph.remove_edge(0, 2);
    if (mygraph.has_edge(0, 2))
    {
        std::cout << "graph_remove_edge error\n";
        return 1;
    }

    Graph<int, int> copygraph(mygraph);
    if (copygraph.get_vertex_count() != mygraph.get_vertex_count() ||
        !copygraph.has_edge(0, 1) || !copygraph.has_edge(1, 2))
    {
        std::cout << "graph_copy_ctor error\n";
        return 1;
    }

    Graph<int, int> othergraph(1);
    othergraph = copygraph;
    if (othergraph.get_vertex_count() != copygraph.get_vertex_count() ||
        !othergraph.has_edge(0, 1) || !othergraph.has_edge(2, 3))
    {
        std::cout << "graph_assignment error\n";
        return 1;
    }

    mygraph.remove_vertex(2);
    if (mygraph.has_edge(0, 2) || mygraph.has_edge(1, 2))
    {
        std::cout << "graph_remove_vertex error\n";
        return 1;
    }

    size_t newid = mygraph.add_vertex(200);
    if (newid != 4 || mygraph.get_vertex_count() != 5)
    {
        std::cout << "graph_add_vertex error\n";
        return 1;
    }

    if (mygraph.get_vertex_label(newid) != 200)
    {
        std::cout << "graph_new_vertex_label error\n";
        return 1;
    }

    mygraph.add_edge(newid, 0, 30);
    mygraph.add_edge(1, newid, 40);

    if (!mygraph.has_edge(newid, 0) || mygraph.get_edge_label(newid, 0) != 30 ||
        !mygraph.has_edge(1, newid) || mygraph.get_edge_label(1, newid) != 40)
    {
        std::cout << "graph_edges_to_new_vertex error\n";
        return 1;
    }

    Vector<int> all_labels = mygraph.get_all_vertex_labels();
    if (all_labels.size() != 5)
    {
        std::cout << "graph_get_all_labels error\n";
        return 1;
    }

    mygraph.set_edge_label(0, 1, 20);
    if (mygraph.get_edge_label(0, 1) != 20)
    {
        std::cout << "graph_set_edge_label error\n";
        return 1;
    }

    std::cout << "Graph tests passed\n";
    return 0;
}