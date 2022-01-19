#include "d_graph.h"
#include <iostream>

typedef Data<int> LabelData;

int main() {
    size_t maxVerticesNumber = 10;
    auto *graph = new D_Graph<LabelData>(maxVerticesNumber, LabelData(10 , 0));
    
    for (size_t i = 0; i < maxVerticesNumber; i++ ) {
        if (graph->getVertex(i)->getData().data != 10) {
            std::cout << "initialization error\n";
            return 1;
        }
        std::cout << graph->getVertex(i)->getData().data << " ";
    }
    std::cout << std::endl;

    graph->getVertex(0)->getData().data = 9;
    if (graph->getVertex(0)->getData().data != 9) {
            std::cout << "set data error\n";
            return 1;
        }



    graph->getVertex(1)->addEdgeTo(graph->getVertex(5));
    if (graph->edgeExist(graph->getVertex(1), graph->getVertex(5))) {
        std::cout<< "edge added successfully\n";
    }
    else {
        std::cout << "edge error";
        return 1;
    }

    if (graph->edgeExist(graph->getVertex(1), graph->getVertex(4))) {
        std::cout << "edge error";
        return 1;
    }

    graph->getVertex(1)->addEdgeTo(graph->getVertex(4));
    graph->getVertex(1)->addEdgeTo(graph->getVertex(3));
    graph->getVertex(1)->addEdgeTo(graph->getVertex(2));
    
    graph->getVertex(1)->removeEdgeTo(graph->getVertex(2));
    if (graph->edgeExist(graph->getVertex(1), graph->getVertex(2))) {
        std::cout << "deletion error";
        return 1;
    }
    
    graph->getVertex(1)->getData().label = 1;
    if (graph->getVertex(1)->getData().label != 1) {
        std::cout << "label error\n";
        return 1;
    }
    
    D_Graph<LabelData>::EdgesIterator iterator(graph->getVertex(1));
    
    while (*iterator != nullptr) {
        std::cout << (*iterator)->getDest()->getData().data << "\n";
        ++iterator;        
    }

    for (size_t i = 0; i < maxVerticesNumber; i++) {
        graph->getVertex(i)->setData(i);
        std::cout << graph->getVertex(i)->getData().data << " ";
    }
    std::cout << std::endl;

    graph->removeVertex(3);
    for (size_t i = 0; i < maxVerticesNumber-1; i++) {
        std::cout << graph->getVertex(i)->getData().data << " ";
    }
    std::cout << std::endl;

    iterator.refresh(graph->getVertex(1));
    while (*iterator != nullptr) {
        std::cout << (*iterator)->getDest()->getData().data << "\n";
        ++iterator;
    }

    delete graph;
    return 0;
}