#include <iostream>
#include <vector>
#include "graph.h"

int main() {

    int size = 6;
    auto graph = new Graph();

    for(int i = 0; i < size; i++){
        graph->AddVertex(i+1);
    }

    for(int i = 0; i < size; i++){
        graph->getVertex(i)->SetData(i+1);
    }
    graph->AddEdge(*graph->getVertex(0), *graph->getVertex(1), 6);// 1 -> 2
    graph->AddEdge(*graph->getVertex(1), *graph->getVertex(0), 6);// 2 -> 1

    graph->AddEdge(*graph->getVertex(0), *graph->getVertex(3), 5);// 1 -> 4
    graph->AddEdge(*graph->getVertex(3), *graph->getVertex(0), 5);// 4 -> 1

    graph->AddEdge(*graph->getVertex(0), *graph->getVertex(2), 1);// 1 -> 3
    graph->AddEdge(*graph->getVertex(2), *graph->getVertex(0), 5);// 3 -> 1

    graph->AddEdge(*graph->getVertex(1), *graph->getVertex(2), 5);// 2 -> 3
    graph->AddEdge(*graph->getVertex(2), *graph->getVertex(1), 5);// 2 -> 3

    graph->AddEdge(*graph->getVertex(1), *graph->getVertex(4), 3);// 2 -> 5
    graph->AddEdge(*graph->getVertex(4), *graph->getVertex(1), 3);// 5 -> 2

    graph->AddEdge(*graph->getVertex(2),*graph->getVertex(4), 6); // 3 -> 5
    graph->AddEdge(*graph->getVertex(4),*graph->getVertex(2), 6); // 5 -> 3

    graph->AddEdge(*graph->getVertex(2),*graph->getVertex(5), 4); // 3 -> 6
    graph->AddEdge(*graph->getVertex(5),*graph->getVertex(2), 4); // 6 -> 3

    graph->AddEdge(*graph->getVertex(2),*graph->getVertex(3), 5); // 3 -> 4
    graph->AddEdge(*graph->getVertex(3),*graph->getVertex(2), 5); // 4 -> 3

    graph->AddEdge(*graph->getVertex(3), *graph->getVertex(5), 2);// 4 -> 6
    graph->AddEdge(*graph->getVertex(5), *graph->getVertex(3), 2);// 6 -> 4

    graph->AddEdge(*graph->getVertex(4), *graph->getVertex(5), 6);// 5 -> 6
    graph->AddEdge(*graph->getVertex(5), *graph->getVertex(4), 6);// 6 -> 5

    //Prima:


    auto prima = new Graph();

    for(int i = 0; i < size; i++){
        prima->AddVertex(i+1);
    }

    for(int i = 0; i < size; i++){
        prima->getVertex(i)->SetData(i+1);
    }

    auto vertex = graph->getVertex(0);
    auto vertexEdges = vertex->getEdges();
    auto minEdge = vertexEdges.first()->getData();

    for(auto item = vertexEdges.first(); item != nullptr; item = item->getNext()){
        if(item->getData()->GetWeight() < minEdge->GetWeight()){
            minEdge = item->getData();
        }
    }

    auto v = minEdge->GetPointV();

    prima->AddEdge(*vertex, *v, minEdge->GetWeight());
    prima->AddEdge(*v,*vertex , minEdge->GetWeight());

    int countEdges = 1;
    std::vector<Graph::Vertex*> usedVertices;
    usedVertices.push_back(vertex);
    vertex = minEdge->GetPointV();
    vertexEdges = vertex->getEdges();
    minEdge = vertexEdges.first()->getData();


    while(countEdges != prima->GetVertices().size() - 1){
        int i = 0;
        for(auto item = vertexEdges.first(); item != nullptr; item = item->getNext()){
            if((item->getData()->GetWeight() < minEdge->GetWeight()) and (item->getData()->GetPointV() != usedVertices[i])){

            }
            i++;
        }
        v = minEdge->GetPointV();
        prima->AddEdge(*vertex, *v, minEdge->GetWeight());
        prima->AddEdge(*v,*vertex , minEdge->GetWeight());
        countEdges++;
        usedVertices.push_back(vertex);
        vertex = minEdge->GetPointV();
        vertexEdges = vertex->getEdges();
        minEdge = vertexEdges.first()->getData();
    }

    if(!prima->IsEdge(*graph->getVertex(0), *graph->getVertex(1))){
        exit(1);
    }

    return 0;
}