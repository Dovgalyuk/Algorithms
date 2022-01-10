//
// Created by onisken on 07.01.2022.
//

#include <iostream>
#include "graph.h"
#include <vector>

int main(){
    std::cout << "Input count of vertexes:";
    int countVertexes;
    std::cin >> countVertexes;

    auto graph = new Graph<int, int>(countVertexes, 1);

    for (int i = 0; i < countVertexes; ++i) {
        int tempData;
        std::cout << "[" << i << "] =";
        std::cin >> tempData;
        graph->setDataVertex(i, tempData);
    }

    for (int i = 0; i < countVertexes; i++) {
        std::cout << "Vertex:" << graph->getDataVertex(i) << " (index: " << graph->getIndexVertex(graph->getVertex(i)) << ")" << std::endl;
        std::cout << "How much edges?" << std::endl;
        int tempCountEdges;
        std::cin >> tempCountEdges;
        for (int j = 0; j < tempCountEdges; ++j) {
            std::cout  << j + 1 << " edge. Input index of second Vertex:";
            int indexToVertex;
            std::cin >> indexToVertex;
            std::cout << "Input weight:";
            int tempWeight;
            std::cin >> tempWeight;
            graph->addEdge(graph->getVertex(i), graph->getVertex(indexToVertex), tempWeight);
        }
    }

    int shortPath[countVertexes][countVertexes];

    // 'edge = -1' - path is not exist
    for (int i = 0; i < countVertexes; ++i) {
        for (int j = 0; j < countVertexes; ++j) {
            if (i == j) {
                shortPath[i][j] = 0;
            } else {
                if (graph->checkEdge(graph->getVertex(i), graph->getVertex(j)))
                    shortPath[i][j] = graph->getWeightEdge(graph->getVertex(i), graph->getVertex(j));
                else
                    shortPath[i][j] = -1;
            }
        }
    }

    for(int i = 0; i < countVertexes; i++ ) {
        for(int j = 0; j < countVertexes; j++ ) {
            std::cout << shortPath[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for(int k = 0; k < countVertexes; k++) {
        for(int i = 0; i < countVertexes; i++) {
            for(int j = 0; j < countVertexes; j++) {
                if(i != j && shortPath[i][k] != -1 && shortPath[k][j] != -1) {
                    if(shortPath[i][j] == -1) {
                        shortPath[i][j] = shortPath[i][k] + shortPath[k][j];
                    } else {
                        shortPath[i][j] = std::min(shortPath[i][j], shortPath[i][k] + shortPath[k][j]);
                    }
                }
            }
        }
    }

    std::cout << "shortest path:" << std::endl;

    for(int i = 0; i < countVertexes; i++) {
        for(int j = 0; j < countVertexes; j++) {
            std::cout << shortPath[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*
6
0 10 20 -1 -1 -1
-1 0 10 -1 -1 -1
-1 -1 0 4 7 6
-1 -1 -1 0 -1 3
-1 -1 -1 -1 0 -1
-1 -1 -1 -1 3 0
====================
0 10 20 24 27 26
-1 0 10 14 17 16
-1 -1 0 4 7 6
-1 -1 -1 0 6 3
-1 -1 -1 -1 0 -1
-1 -1 -1 -1 3 0
*/
