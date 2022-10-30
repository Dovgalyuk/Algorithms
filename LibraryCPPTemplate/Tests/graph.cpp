#include <iostream>
#include "graph.h"

using std::cin; using std::cout; using std::vector;

int main() {

    int VertexNumber = 10;

    Graph<int>* graph = new Graph<int>(VertexNumber, 1);

    for (size_t i = 0; i < VertexNumber; i++) 
    {
        if (graph->GetVertexData(i) != 1) 
        {
            cout << "\nError --> graph initialization failed\n\n\a";
            return 1;
        }
    }

    for (int i = 0; i < VertexNumber; i++) 
    {
        graph->SetVertexData(i, i);
    }

    for (int i = 0; i < VertexNumber; i++) 
    {
        if (graph->GetVertexData(i) != i) 
        {
            cout << "\t\nError --> SetVertexData\n\n\a";
            return 1;
        }

        cout << graph->GetVertexData(i) << " ";
    }

    cout << "\n";

    graph->AddEdge(graph->GetVertex(0), graph->GetVertex(5), 10);

    if (!graph->AvailabilityLink(graph->GetVertex(0), graph->GetVertex(5))) 
    {
        cout << "\t\nError --> adding an edge\n\n\a";
        return 1;
    }

    graph->AddEdge(graph->GetVertex(0), graph->GetVertex(3), 5);

    if (!graph->AvailabilityLink(graph->GetVertex(0), graph->GetVertex(3)) || graph->GetWeightEdge(graph->GetVertex(0), graph->GetVertex(3)) != 5) 
    {
        cout << "\t\nError --> adding an edge\n\n\a";
        return 1;
    }

    graph->AddEdge(graph->GetVertex(0), graph->GetVertex(9), 15);
    graph->AddEdge(graph->GetVertex(0), graph->GetVertex(2), 35);

    graph->GetEdge(graph->GetVertex(0), graph->GetVertex(9))->weight = 18;

    if (graph->GetWeightEdge(graph->GetVertex(0), graph->GetVertex(9)) != 18) 
    {
        cout << "\t\nError --> the weight of the edge has not been established\n\n\a";
        return 1;
    }

    graph->RemoveEdge(graph->GetVertex(0), graph->GetVertex(9));

    if (graph->AvailabilityLink(graph->GetVertex(0), graph->GetVertex(9))) 
    {
        cout << "\t\nError --> delete a edge\n\n\a";
        return 1;
    }

    Graph<int>::EdgeIterator iterator(graph->GetVertex(0));

    int count = 0;

    while (*iterator != nullptr) 
    {
        count++;
        ++iterator;
    }

    if (count != 3) 
    {
        cout << "\t\nError --> iterator\n\n\a";
        return 1;
    }

    graph->RemoveVertex(2);

    if (graph->SizeVertexVec() != VertexNumber - 1) 
    {
        cout << "\t\nError --> RemoveVertex\n\n\a";
        return 1;
    }

    for (int i = 0; i < VertexNumber - 1; i++) 
    {
        cout << graph->GetVertexData(i) << " ";
    }
    cout << "\n";
    delete graph;
}
