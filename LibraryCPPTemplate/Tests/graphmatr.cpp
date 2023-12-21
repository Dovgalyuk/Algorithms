#include "vector.h"
#include <iostream>
#include "graphmatr.h"
using namespace std;


int main()
{

    Graph<int,int> graph(5);


    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 1);

    AdjacentVertexIterator iterator = graph.getAdjacentVertices(0);


    while (iterator.hasNext()) {
        long unsigned int vertex = iterator.next();
        if (graph.EdgeExists(vertex, 0)) {
            cout << "iterator bad";
            return 0;
        }
    }

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
    try {
        graph.EdgeExists(2, 4);
        cout << "Vertex 2 was not removed";
        return 0;
    }
    catch (const std::out_of_range& oor) {

    }


    return 0;

};

