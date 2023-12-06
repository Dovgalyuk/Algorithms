#include "vector.h"
#include <iostream>
#include "graphmatr.h"
using namespace std;


int main()
{

    Graph<int> graph(5);


    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2,4);
    graph.addEdge(2, 4, 5);

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
    
   
   const Vector<int>* verticesBefore = graph.getVertices();
    graph.removeVertex(0);
  
   const Vector<int>* verticesAfter = graph.getVertices();
    if (size(verticesBefore) == size(verticesAfter)) {
        cout << "Vertex was not removed.";
        return 0;
    }
    


    return 0;
};


