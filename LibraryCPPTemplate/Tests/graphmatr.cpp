
#include <iostream>
#include "graphmatr.h"
using namespace std;


int main()
{

    Graph<int> graph(5);


    graph.addEdge(0, 1, 3);


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





    return 0;
};


