#include <iostream>
#include "graph.h"

typedef Graph<int> MyGraph;

int main() {
    MyGraph graph(5);
    if (graph.vertexCount() != 5) 
    {
        std::cout << "Graph count error\n" << std::endl;
        return 1;
    }
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 20);
    graph.addEdge(2, 3, 30);
    graph.addEdge(3, 4, 40);
    graph.addEdge(4, 0, 50);

    if (graph.getEdgeData(2, 3) != 30) 
    {
        std::cout << "addEdge error\n";
        return 1;
    }

    graph.removeEdge(4, 0);
    
    if (graph.hasEdge(4, 0)) 
    {
        std::cout << "removeEdge error\n";
        return 1;
    }
    
    graph.setEdgeData(0, 1, 123);
    
    if (graph.getEdgeData(0, 1) != 123) 
    {
        std::cout << "setEdgeData error\n";
        return 1;
    }

    return 0;
}
