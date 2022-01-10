#include "graph.h"
#include <vector>
#include <algorithm>
#include <climits>

struct Edges {
    int F, S, W;
};
int main() {
    const int vertexCount = 5;
    std::vector <Edges> edges;
    Graph<int>* graph = new Graph<int>(vertexCount);
    Graph<int>* MST = new Graph<int>(vertexCount);

    //set default labels for each vertex
    for (int i = 0; i < vertexCount; i++) {
        graph->getVertex(i)->setData(i);
    }

    edges.push_back({ 0,1,100 });
    edges.push_back({ 1,0,100 });
    edges.push_back({ 0,3,50 });
    edges.push_back({ 3,0,50 });
    edges.push_back({ 4,0,20 });
    edges.push_back({ 0,4,20 });
    edges.push_back({ 4,2,20 });
    edges.push_back({ 2,4,20 });
    edges.push_back({ 2,3,5 });
    edges.push_back({ 2,3,5 });
    edges.push_back({ 1,4,15 });
    edges.push_back({ 4,1,15 });

    //fill the tree
    for (int i = 0; i < edges.size(); i++) {
        graph->addEdgeFromTo(edges[i].F, edges[i].S);
        graph->addWeightToEdge(edges[i].F, edges[i].S, edges[i].W);
    }

    //sorting by weight
    std::sort(edges.begin(), edges.end(), [](Edges a, Edges b) { return (a.W < b.W); });

    //sorted vec output
    for (int i = 0; i < edges.size(); i++) {
        std::cout << edges[i].F << "<->" << edges[i].S << " Weight:" << edges[i].W << "\n";
    }

    //kruscal's algorithm
    int i = 0;
    while (i < edges.size())
    {
        //for redability
        int FirstVertex = edges[i].F;
        int SecondVertex = edges[i].S;
        int Weight = edges[i].W;

        int firstLabel = graph->getVertex(FirstVertex)->getData();
        int secondLabel = graph->getVertex(SecondVertex)->getData();
        
        if (firstLabel != secondLabel) //if vertices from different sets
        {
            MST->addEdgeFromTo(FirstVertex, SecondVertex);
            MST->addWeightToEdge(FirstVertex, SecondVertex, Weight);
            for (int i = 0; i < vertexCount; i++)
            {
                if (graph->getVertex(i)->getData() == secondLabel) //merge sets (second set into first) 
                {
                    graph->getVertex(i)->setData(firstLabel);
                }
                   
            }
        }
        i++;
    }

    std::cout << "MST: \n";

    for (int i = 0; i < vertexCount; i++) {
        Graph<int>::EdgesIterator iterator(MST->getVertex(i));
        while (*iterator != nullptr) {
            std::cout << i << "<->" << MST->getIndexOf((*iterator)->getDest()) << " ";
            std::cout << MST->getVertex(i)->getEdge((*iterator)->getDest())->getWeight() << "\n";
            ++iterator;
        }
    }
    delete graph;
    delete MST;
    return 0;
}