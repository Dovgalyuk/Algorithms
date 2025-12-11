#include <iostream>
#include <string>
#include "../graph.h"

using namespace std;

int main()
{
	Graph<string, int> g(3);


    g.SetVertexLabel(0, "A");
    g.SetVertexLabel(1, "B");
    g.SetVertexLabel(2, "C");

    cout << "Initial vertex labels:\n";
    for (size_t i = 0; i < g.VertexCount(); ++i)
    {
        cout << i << ": " << g.GetVertexLabel(i) << "\n";
    }


    g.AddEdge(0, 1, 5);  // A -> B
    g.AddEdge(1, 2, 7);  // B -> C
    g.AddEdge(0, 2, 10); // A -> C


    cout << "\nEdges (HasEdge and label):\n";
    for (size_t i = 0; i < g.VertexCount(); ++i)
    {
        for (size_t j = 0; j < g.VertexCount(); ++j)
        {
            cout << g.GetVertexLabel(i) << " -> " << g.GetVertexLabel(j) << " : ";
            if (g.HasEdge(i, j))
                cout << "exists, label = " << g.GetEdgeLabel(i, j) << "\n";
            else
                cout << "no edge\n";
        }
    }

    cout << "\nNeighbors of vertex B:\n";
    size_t idxB = 1;
    auto itB = g.Neighbors(idxB);
    while (itB.HasNext())
    {
        size_t v = itB.Next();
        cout << "  " << g.GetVertexLabel(idxB)
            << " -> " << g.GetVertexLabel(v)
            << " (label = " << g.GetEdgeLabel(idxB, v) << ")\n";
    }

    cout << "\nNeighbors of vertex A:\n";
    size_t idxA = 0;
    auto itA = g.Neighbors(idxA);
    while (itA.HasNext())
    {
        size_t v = itA.Next();
        cout << "  " << g.GetVertexLabel(idxA)
            << " -> " << g.GetVertexLabel(v)
            << " (label = " << g.GetEdgeLabel(idxA, v) << ")\n";
    }

    cout << "\nAdd vertex D:\n";
    size_t idxD = g.AddVertex("D");
    cout << "New vertex index: " << idxD << ", label = " << g.GetVertexLabel(idxD) << "\n";
    cout << "Vertex count now: " << g.VertexCount() << "\n";

    g.AddEdge(idxD, idxA, 3); // D -> A
    g.AddEdge(idxA, idxD, 4); // A -> D

    cout << "\nNeighbors of vertex D:\n";
    auto itD = g.Neighbors(idxD);
    while (itD.HasNext())
    {
        size_t v = itD.Next();
        cout << "  " << g.GetVertexLabel(idxD)
            << " -> " << g.GetVertexLabel(v)
            << " (label = " << g.GetEdgeLabel(idxD, v) << ")\n";
    }


    cout << "\nRemove vertex with index 1 (was B):\n";
    g.RemoveVertex(1);

    cout << "Vertex count after remove: " << g.VertexCount() << "\n";
    cout << "Current vertex labels:\n";
    for (size_t i = 0; i < g.VertexCount(); ++i)
    {
        cout << i << ": " << g.GetVertexLabel(i) << "\n";
    }

    cout << "\nEdges after removing vertex index 1:\n";
    for (size_t i = 0; i < g.VertexCount(); ++i)
    {
        for (size_t j = 0; j < g.VertexCount(); ++j)
        {
            cout << g.GetVertexLabel(i) << " -> " << g.GetVertexLabel(j) << " : ";
            if (g.HasEdge(i, j))
                cout << "exists, label = " << g.GetEdgeLabel(i, j) << "\n";
            else
                cout << "no edge\n";
        }
    }

}