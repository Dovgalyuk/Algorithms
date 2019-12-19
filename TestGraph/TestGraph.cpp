#include <iostream>
#include <graph.h>

using namespace std;

int main() {
    Graph* graph = graph_create(5);
    for (int i = 0; i < 5; i++)
    {
        add_mark_vertex(graph, i, i);
    }
    for (int i = 0; i < 5; i++)
    {
        if (read_mark_vertex(graph, i) != i)
        {
            cout << "Wrong mark on " << i << " vertex" << endl;
        }
    }

    add_vertex(graph);
    add_mark_vertex(graph, 5, 5);
    add_vertex(graph);
    add_mark_vertex(graph, 6, 6);
    add_vertex(graph);
    add_mark_vertex(graph, 7, 7);

    for (int i = 0; i < 8; i++)
    {
        if (read_mark_vertex(graph, i) != i)
        {
            cout << "Wrong mark on " << i << " vertex" << endl;
        }
    }

    delete_vertex(graph, 7);
    for (int i = 0; i < 7; i++)
    {
        if (read_mark_vertex(graph, i) != i)
        {
            cout << "Wrong mark on " << i << " vertex" << endl;
        }
    }

    delete_vertex(graph, 3);
    for (int i = 0; i < 6; i++)
    {
            cout << read_mark_vertex(graph, i) << " ";
    }
    cout << endl;

    add_mark_vertex(graph, 0, 10);
    for (int i = 0; i < 6; i++)
    {
        cout << read_mark_vertex(graph, i) << " ";
    }
    cout << endl;

    add_edge(graph, 0, 2);
    add_edge(graph, 1, 4);
    if (!check_edge(graph, 0, 2) || !check_edge(graph, 1, 4))
    {
        cout << "Wrong edge checking result(no edges)" << endl;
    }

    delete_edge(graph, 0, 2);
    if (check_edge(graph, 0, 2))
    {
        cout << "Wrong delete edge result" << endl;
    }

    add_mark_edge(graph, 1, 4, 10);
    if (read_mark_edge(graph, 1, 4) != 10)
    {
        cout << "Wrong add or read mark edge result" << endl;
    }

    delete_vertex(graph, 4);
    if (check_edge(graph, 1, 4))
    {
        cout << "Wrong delete edge result" << endl;
    }

    graph_delete(graph);

    system("Pause");
    return 0;
}