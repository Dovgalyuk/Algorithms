//
//  graph.hpp
//  Graph
//
//  Created by Marcos Vicente on 18.12.2017.
//  Copyright © 2017 Marcos Vicente. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>

using namespace std;

//foi criada uma espécie de lista de vértices, onde cada um por sua vez tem uma lista de arestas
//a variável adj indica o que elemento que está conectado a seguir
class edge;

//lista de vértices
class vertex;

//lista de arestas
class edge;

class graph{
    vertex *first; //ponteiro no primeiro vértice
public:
    int countEdges;
    void createGraph();
    bool emptyGraph();
    int sizeGraph();
    void free();
    void adjList();
    
    vertex *getVertex(int label);
    bool checkVertex(int label);
    void insertVertex(int label);
    void removeVertex(vertex *insVertex);
    
    bool checkEdge(vertex *orig, vertex *dest);
    void insertEdge(vertex *orig, vertex *dest, int weight);
    void removeEdge(vertex *orig, vertex *dest);
    
    //para algoritmo de Prim
    //edge *getEdge(vertex *orig, vertex *dest);
    bool insertWeight (vertex *orig, vertex *dest, int weight);
    //int getEdgeWeight (edge *Edge);
    int getEdgeWeightFromAdjList(vertex *vertAux);
    bool checkBeginVertexEdge(vertex *vertAux);
    int checkDestVertexEdge(vertex *vertAux);
};

void algPrim (graph *Graph);

#endif /* graph_hpp */

