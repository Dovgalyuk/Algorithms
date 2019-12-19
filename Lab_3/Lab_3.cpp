#include <iostream>
#include <graph.h>
#include <graph.cpp>
#include <algorithm>

//Maximum weight of the graph edge
#define INF 1001
//Maximum number of graph vertices
const size_t MAX_NUMBER_VERTICES = 50;

using namespace std;

int main()
{
    size_t number_vertices;
    cout << "Enter the number of vertices of the graph: ";
    cin >> number_vertices;
    Graph* graph = graph_create(number_vertices);
    for (size_t i = 0; i < number_vertices; i++) {
        add_mark_vertex(graph, i, i);
    }

    size_t number_edges;
    cout << "Enter the number of edges of the graph: ";
    cin >> number_edges;
    cout << "Enter from which vertex the edge starts and ends, and its weight:\n";
    for (size_t i = 0; i < number_edges; i++) {
        size_t from, to, weight_edge;
        cin >> from >> to >> weight_edge;
        add_edge(graph, from, to);
        add_mark_edge(graph, from, to, weight_edge);
    }

    cout << "\nThe adjacency list:\n";
    for (size_t i = 0; i < number_vertices; i++) {
        cout << i;
        for (Iterator it = iterator_begin(graph, i); it != iterator_end(graph, i); ++it)
        {
            Data edge = *it;
            cout << " -> " << edge->to;
        }
        cout << endl;
    }

    size_t Adjacency_matrix[MAX_NUMBER_VERTICES][MAX_NUMBER_VERTICES];

    for (size_t i = 0; i < number_vertices; ++i)
    {
        for (size_t j = 0; j < number_vertices; ++j)
        {
            Adjacency_matrix[i][j] = INF;
        }
    }

    for (size_t i = 0; i < number_vertices; i++) {
        for (Iterator it = iterator_begin(graph, i); it != iterator_end(graph, i); ++it)
        {
            Data edge = *it;
            Adjacency_matrix[i][edge->to] = read_mark_edge(graph, i, edge->to);
        }
 
    }

    cout << "\nAdjacency matrix:\n";
    for (size_t i = 0; i < number_vertices; ++i)
    {
        for (size_t j = 0; j < number_vertices; ++j)
        {
            if (Adjacency_matrix[i][j] == INF) {
                cout.width(4);
                cout << "INF";
                cout << " ";
            }
            else {
                cout.width(4);
                cout << Adjacency_matrix[i][j];
                cout << " ";
            }
        }
        cout << endl;
    }

    for (int k = 0; k < number_vertices; k++)
    {
        for (int i = 0; i < number_vertices; i++)
        {
            for (int j = 0; j < number_vertices; j++)
            {
                if (i != j)
                {
                    Adjacency_matrix[i][j] = min(Adjacency_matrix[i][j], Adjacency_matrix[i][k] + Adjacency_matrix[k][j]);
                }
            }
        }
    }

    cout << "\nShortest path length matrix:\n";
    for (size_t i = 0; i < number_vertices; ++i)
    {
        for (size_t j = 0; j < number_vertices; ++j)
        {
            if (Adjacency_matrix[i][j] == INF) {
                cout.width(4);
                cout << "INF";
                cout << " ";
            }
            else {
                cout.width(4);
                cout << Adjacency_matrix[i][j];
                cout << " ";
            }
        }
        cout << endl;
    }
    system("Pause");
    return 0;
}
