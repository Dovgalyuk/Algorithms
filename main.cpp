//
//  main.cpp
//  Graph
//
//  Created by Marcos Vicente on 18.12.2017.
//  Copyright © 2017 Marcos Vicente. All rights reserved.
//

#include <iostream>
#include "graph.hpp"

using namespace std;

/*
 { 0, 3, 0, 0},
 { 0, 0, 9,10},
 { 0, 0, 0, 7},
 { 5, 0, 0, 0},
 */

int main() {
    graph G;
    
    //Создать граф
    G.createGraph();
    
    //Добавить вершину
    G.insertVertex(1);
    G.insertVertex(2);
    G.insertVertex(3);
    G.insertVertex(4);
    
    //Добавить ребро
    G.insertEdge(G.getVertex(1), G.getVertex(2), 3);
    G.insertEdge(G.getVertex(2), G.getVertex(3), 9);
    G.insertEdge(G.getVertex(2), G.getVertex(4), 10);
    G.insertEdge(G.getVertex(3), G.getVertex(4), 7);
    G.insertEdge(G.getVertex(4), G.getVertex(1), 5);

    //Проверить существует ли нет ребро между вершинами. OBS: não usar depois de remover um vértice
    G.checkEdge(G.getVertex(2), G.getVertex(3));
    
    //Задать/считать пометку для ребра
    cout << "Пометку для ребра: " << G.countEdges << endl ;
    
    //Задать/считать пометку для вершины
    cout << "Пометку для вершины: " << G.sizeGraph() << endl;
    
    cout << "\n------Список смежности------" << endl;
    G.adjList();
    
    cout << "------Алгоритм Прима------" << endl;
    algPrim(&G);
    
    //Удалить ребро
    G.removeEdge(G.getVertex(2), G.getVertex(3));
    //para verificar se a remoção deu certo
    G.checkEdge(G.getVertex(2), G.getVertex(3));
    
    //Удалить вершину
    G.removeVertex(G.getVertex(1));
    //para verificar se a remoção deu certo
    G.checkVertex(1);
    
    return 0;
}

