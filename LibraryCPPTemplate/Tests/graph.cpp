//
// Created by Zaitunat on 07.11.2026.
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "graph.h"
using namespace std;

typedef Graph<string, int> MyGraph;
int main()
{
    MyGraph graph(4);
    if (graph.vertexCount() != 4)
    {
        cout << "Invalid constructor";
        return 1;
    }
    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");
    graph.setVertexLabel(3, "D");
    if (graph.getVertexLabel(0) != "A" || graph.getVertexLabel(3) != "D")
    {
        cout << "Invalid vertex label";
        return 1;
    }

    for (size_t i = 0; i < graph.vertexCount(); i++)
    {
        if (graph.findVertex(graph.getVertexLabel(i)) != i)
        {
            cout << "Invalid findVertex " << i;
            return 1;
        }
    }
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 0, 20);
    graph.addEdge(1, 2, 30);
    graph.addEdge(2, 3, 40);
    if (!graph.hasEdge(0, 1) || !graph.hasEdge(1, 0) || !graph.hasEdge(1, 2) || !graph.hasEdge(2, 3))
    {
        cout << "Invalid edge creation";
        return 1;
    }
    if (graph.hasEdge(0, 2) || graph.hasEdge(3, 2))
    {
        cout << "Invalid edge direction";
        return 1;
    }
    if (graph.getEdgeLabel(0, 1) != 10 || graph.getEdgeLabel(1, 0) != 20 ||
        graph.getEdgeLabel(1, 2) != 30 || graph.getEdgeLabel(2, 3) != 40)
    {
        cout << "Invalid edge label";
        return 1;
    }

    graph.setEdgeLabel(0, 1, 100);
    if (graph.getEdgeLabel(0, 1) != 100)
    {
        cout << "Invalid edge label update";
        return 1;
    }
    graph.addEdge(0, 1, 200);
    if (graph.getEdgeLabel(0, 1) != 200)
    {
        cout << "Invalid addEdge for existing edge";
        return 1;
    }
    graph.removeEdge(1, 0);
    if (graph.hasEdge(1, 0) || !graph.hasEdge(0, 1))
    {
        cout << "Invalid removeEdge";
        return 1;
    }
    graph.removeEdge(1, 0);
    graph.addEdge(1, 0, 20);
    MyGraph &same = graph;
    graph = same;
    if (graph.vertexCount() != 4 || !graph.hasEdge(0, 1) || graph.getEdgeLabel(0, 1) != 200)
    {
        cout << "Invalid self-assignment";
        return 1;
    }
    MyGraph copy(graph);
    if (copy.vertexCount() != graph.vertexCount())
    {
        cout << "Invalid copy constructor";
        return 1;
    }
    for (size_t i = 0; i < graph.vertexCount(); i++)
    {
        if (copy.getVertexLabel(i) != graph.getVertexLabel(i))
        {
            cout << "Invalid copy vertex " << i;
            return 1;
        }
        for (size_t j = 0; j < graph.vertexCount(); j++)
        {
            if (copy.hasEdge(i, j) != graph.hasEdge(i, j))
            {
                cout << "Invalid copy edge " << i << " " << j;
                return 1;
            }
            if (graph.hasEdge(i, j) && copy.getEdgeLabel(i, j) != graph.getEdgeLabel(i, j))
            {
                cout << "Invalid copy edge label";
                return 1;
            }
        }
    }
    copy.setEdgeLabel(0, 1, 999);
    if (graph.getEdgeLabel(0, 1) != 200)
    {
        cout << "Copy is not independent";
        return 1;
    }
    MyGraph other;
    other = graph;
    other.removeEdge(0, 1);
    if (!graph.hasEdge(0, 1))
    {
        cout << "Invalid assignment operator";
        return 1;
    }
    size_t index = graph.addVertex("E");
    if (index != 4 || graph.vertexCount() != 5 || graph.getVertexLabel(4) != "E")
    {
        cout << "Invalid addVertex";
        return 1;
    }

    graph.addEdge(4, 3, 50);
    if (!graph.hasEdge(4, 3) || graph.getEdgeLabel(4, 3) != 50)
    {
        cout << "Invalid edge from new vertex";
        return 1;
    }
    graph.removeVertex(1);
    if (graph.vertexCount() != 4)
    {
        cout << "Invalid removeVertex size";
        return 1;
    }

    Vector<string> labels = graph.getVertexLabels();
    if (labels.size() != 4 || labels.get(0) != "A" || labels.get(1) != "C" ||
        labels.get(2) != "D" || labels.get(3) != "E")
    {
        cout << "Invalid labels after removeVertex";
        return 1;
    }
    if (!graph.hasEdge(1, 2) || graph.getEdgeLabel(1, 2) != 40 ||
        !graph.hasEdge(3, 2) || graph.getEdgeLabel(3, 2) != 50)
    {
        cout << "Invalid edges after removeVertex";
        return 1;
    }
    if (graph.hasEdge(0, 1) || graph.hasEdge(1, 0))
    {
        cout << "Edges of removed vertex are still there";
        return 1;
    }
    MyGraph neighbors_graph(4);
    neighbors_graph.addEdge(1, 0, 10);
    neighbors_graph.addEdge(1, 2, 30);
    neighbors_graph.addEdge(2, 3, 20);
    size_t count = 0;
    size_t sum_vertices = 0;
    int sum_labels = 0;
    for (MyGraph::NeighborIterator it = neighbors_graph.neighbors(1); it.valid(); it.next())
    {
        count++;
        sum_vertices += it.vertex();
        sum_labels += it.label();
    }
    if (count != 2 || sum_vertices != 2 || sum_labels != 40)
    {
        cout << "Invalid iteration";
        return 1;
    }

    count = 0;
    for (MyGraph::NeighborIterator it = neighbors_graph.neighbors(0); it.valid(); it.next())
        count++;
    if (count != 0)
    {
        cout << "Vertex without neighbors";
        return 1;
    }

    try
    {
        graph.getVertexLabel(100);
        cout << "Invalid vertex index";
        return 1;
    }
    catch (const out_of_range &) {}

    try
    {
        graph.hasEdge(0, 100);
        cout << "Invalid vertex index in hasEdge";
        return 1;
    }
    catch (const out_of_range &) {}

    try
    {
        graph.getEdgeLabel(0, 2);
        cout << "No exception for missing edge";
        return 1;
    }
    catch (const invalid_argument &) {}

    try
    {
        graph.findVertex("Z");
        cout << "No exception for missing vertex";
        return 1;
    }
    catch (const invalid_argument &) {}

    istringstream input("3\nA B C\n2\nA B 10\nB C 20\n");
    MyGraph input_graph;
    input_graph.read(input);
    if (input.fail() || input_graph.vertexCount() != 3 ||
        input_graph.getVertexLabel(0) != "A" || input_graph.getVertexLabel(1) != "B" ||
        input_graph.getVertexLabel(2) != "C" ||
        !input_graph.hasEdge(0, 1) || !input_graph.hasEdge(1, 2) ||
        input_graph.getEdgeLabel(0, 1) != 10 || input_graph.getEdgeLabel(1, 2) != 20)
    {
        cout << "Invalid graph input";
        return 1;
    }

    istringstream duplicate_input("2\nA A\n0\n");
    MyGraph duplicate_graph;
    duplicate_graph.read(duplicate_input);
    if (!duplicate_input.fail())
    {
        cout << "Duplicate names must be an error";
        return 1;
    }
    istringstream unknown_input("2\nA B\n1\nA Z 5\n");
    MyGraph unchanged_graph(2);
    unchanged_graph.read(unknown_input);
    if (!unknown_input.fail() || unchanged_graph.vertexCount() != 2)
    {
        cout << "Unknown vertex in input";
        return 1;
    }
    Graph<int, int> grid(2, 3);
    if (grid.vertexCount() != 6)
    {
        cout << "Invalid grid size";
        return 1;
    }
    if (!grid.hasEdge(0, 1) || !grid.hasEdge(1, 0) || !grid.hasEdge(0, 3) || !grid.hasEdge(3, 0))
    {
        cout << "Invalid grid edges";
        return 1;
    }
    if (grid.hasEdge(0, 4) || grid.hasEdge(2, 3))
    {
        cout << "Extra grid edges";
        return 1;
    }
    const size_t n = 1000;
    MyGraph performance_graph(n);
    for (size_t i = 0; i + 1 < n; i++)
        performance_graph.addEdge(i, i + 1, static_cast<int>(i + 1));
    MyGraph performance_copy = performance_graph;
    for (size_t i = 0; i + 1 < n; i++)
    {
        if (performance_copy.getEdgeLabel(i, i + 1) != static_cast<int>(i + 1))
        {
            cout << "Invalid performance copy " << i;
            return 1;
        }
    }

    long long sum = 0;
    for (size_t i = 0; i + 1 < n; i++)
        sum += performance_graph.getEdgeLabel(i, i + 1);
    if (sum != 499500)
    {
        cout << "Invalid sum " << sum;
        return 1;
    }

    cout << "Graph tests passed\n";
    return 0;
}