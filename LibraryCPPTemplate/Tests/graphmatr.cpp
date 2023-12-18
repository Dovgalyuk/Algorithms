#include "vector.h"
#include <iostream>
#include "graphmatr.h"
using namespace std;


int main()
{

    Graph<int> graph(5);


    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 1);

    if (!graph.EdgeExists(0, 1)) {
        cout << "edgnoexist";
        return 0;
    }



    graph.setEdgeMark(0, 1, 5);
    if (graph.getEdgeWeight(0, 1) != 5) {
        cout << "weighterror";
        return 0;
    }





    graph.setVertexMark(0, 7);
    if (graph.getVertexMark(0) != 7) {
        cout << "weighterror";
        return 0;
    }


    graph.removeEdge(0, 1);
    if (graph.EdgeExists(0, 1)) {
        cout << "edgeexusts error";
        return 0;
    }
    
   
   
    graph.removeVertex(2);
    if (graph.getVertices()->size() != 4) {
        cout << "Vertex was not removed."; 
        return 0;
    }

    Vector<long unsigned int> expectedAdjacentVertices;
    expectedAdjacentVertices.set(0, 1);
    expectedAdjacentVertices.set(1, 2);
    Vector<long unsigned int> actualAdjacentVertices = graph.getAdjacentVertices(0);

    if (size(actualAdjacentVertices)!=2 || actualAdjacentVertices.get(0)!=expectedAdjacentVertices.get(0)|| actualAdjacentVertices.get(1) != expectedAdjacentVertices.get(1)) {
        cout << "iterator bad ";
        return 0;
    }
 


    return 0;
};


