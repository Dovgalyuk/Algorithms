//
//  graph.hpp
//  Algorithms 3.2
//
//  Created by Marcos Vicente on 14.12.2017.
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
class vertex{
    vertex *next; //ponteiro no vértice seguinte
    edge *adj; //ponteiro para o vértice "begin" da a aresta (Esta aresta vai servir como conexão entre dois vértices)
    int label; //nome do vértice
    friend class graph;
};

//lista de arestas
class edge{
    edge *next; //ponteiro para a aresta seguinte
    vertex *adj; //ponteiro para o vértice "dest" da aresta
    int weight; //peso da aresta
    friend class graph;
};

class graph{
    vertex *first; //ponteiro no primeiro vértice
    int digraph = 0;
public:
    void createGraph();
    bool emptyGraph();
    int sizeGraph();
    vertex *getVertex(int label);
    void insertEdge(vertex *orig, vertex *dest, int digraph, int weight);
    void insertVertex(int label);
    void adjList();
    void removeEdge(vertex *orig, vertex *dest);
    void free();
    void checkVertex(int flag, vertex *orig, vertex *dest);
    void removeVertex(vertex *insVertex);
};

#endif /* graph_hpp */
