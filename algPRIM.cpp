//
//  algPRIM.cpp
//  Graph
//
//  Created by Marcos Vicente on 18.12.2017.
//  Copyright © 2017 Marcos Vicente. All rights reserved.
//

#include <stdio.h>
#include "graph.hpp"
#include <iostream>
#include <cstring>

#define INF 999999

void algPrim(graph *Graph)
{
    int no_edge = 0;            // number of edge inicializado em 0
    int V = Graph->sizeGraph();
    
    int selected[V]; // create a array to track selected vertex
    
    memset (selected, false, sizeof (selected)); // inicializa todos os vértices com valor falso

    selected[0] = true; // inicializa o primeiro vértice como verdadeiro
    int x = 0; //  row number
    int y = 0; //  col number
    
    cout << "Edge" << " : " << "Weight" << endl;
    while (no_edge < V - 1) //certifica-se de que o número de arestas da MST será menos que o número de vértices do grafo
    {
        /*
         { 0, 3, 0, 0},
         { 0, 0, 9,10},
         { 0, 0, 0, 7},
         { 5, 0, 0, 0},
         
         Output for MST using Prim's Algorithm
         1 - 2 : 3
         2 - 3 : 9
         3 - 4 : 7
         */
        
        int min = INF;
        for (int i = 0; i < V; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < V;)
                {
                    if (Graph->getWeight(Graph->getVertex(i+1), Graph->getVertex(j+1)) >= min || Graph->getWeight(Graph->getVertex(i+1), Graph->getVertex(j+1)) == 0) //incrementa o segundo ciclo caso o peso seja INF ou 0
                    {
                        j++;
                    }
                    else if (Graph->getWeight(Graph->getVertex(i+1), Graph->getVertex(j+1)) < min)
                    {
                        min = Graph->getWeight(Graph->getVertex(i+1), Graph->getVertex(j+1));
                        x = i+1;
                        y = j+1;
                    }
                }
            }
        }
        selected[y-1] = true;
        cout << x <<  " - " << y << " :  " << min << endl;
        no_edge++;
        
        //esse última parte serve para inicializar/descartar as posições do grafo já visitadas
        Graph->insertWeight(Graph->getVertex(y), Graph->getVertex(x), INF+1);
        Graph->insertWeight(Graph->getVertex(x), Graph->getVertex(y), INF+1);
    }
}
