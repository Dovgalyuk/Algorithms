#ifndef H_KRUSKALS_ALGORITHM
#define H_KRUSKALS_ALGORITHM

#include <vector>
#include <algorithm>
#include <iostream>
#include "../../LibraryCPPTemplate/graph.h"

class KruskalsAlgorithm {
    private:
        struct Edge;
        Graph<int> *graph;
        // Минимальное остовное дерево
        Graph<int> *mst;
        // Массив ребер
        std::vector<Edge> edges;

        void getAllEdges();
    public: 
        KruskalsAlgorithm(Graph<int> *graph);
        ~KruskalsAlgorithm();
        void run();
        void printResult();
};

#endif