#include <iostream>
#include "graph.h"
#include <vector>
#include <algorithm>

struct Edge {
    int weight;
    int fromIndex, toIndex;

    Edge (int fromIndex_, int toIndex_, int weight_) {
        weight = weight_;
        fromIndex = fromIndex_;
        toIndex = toIndex_;
    }

};

bool compare(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int get_root(int v, Graph<int>* graph) {
    if (v == graph->getDataVertex(v)) {
        return v;
    }
    else {
        graph->setDataVertex(v, get_root(graph->getDataVertex(v), graph));
        return graph->getDataVertex(v);

        // return get_root(graph->getDataVertex(v), graph);
        
    }
}

bool merge(int a, int b, Graph<int>* graph) {
    int ra = get_root(a, graph), rb = get_root(b, graph);

    if (ra == rb) {
        return false;
    }
    else {
        if (graph->getLabelVertex(ra) < graph->getLabelVertex(rb)) {
            graph->setDataVertex(ra, rb);
        }
        else if (graph->getDataVertex(rb) < graph->getDataVertex(ra)) {
            graph->setDataVertex(rb, ra);
        }
        else {
            graph->setDataVertex(ra, rb);
            graph->setLabelVertex(rb, (graph->getLabelVertex(rb) + 1));
        }

        return true;
    }
}

int main() {

    int numberVertex = 5;

    int countEdge = 7;

    Graph<int> *graph = new Graph<int>(numberVertex, 0);

    for (int i = 0; i < numberVertex; i++) {
        graph->setDataVertex(i, i);
    }

    int edges[countEdge][3] {{0, 4, 1}, {0, 1, 3}, {1, 2, 5}, {1, 4, 4}, {4, 3, 7}, {4, 2, 6}, {2, 3, 2}}; // 5 7

    // int edges[countEdge][3] {{0, 1, 3}, {0, 3, 5}, {1, 2, 1}, {2, 3, 8}}; // 4 4


    for (int i = 0; i < countEdge; i++) {
        graph->addEdge(graph->getVertex(edges[i][0]), graph->getVertex(edges[i][1]), edges[i][2]);
    }

    std::vector<Edge> allEdges;

    // получить все значения ребер и их вершины
    for (int i = 0; i < graph->sizeVertexex(); i++) {
        auto* item = graph->getVertex(i);

        Graph<int>::EdgeIterator iterator(item);

        while (*iterator != nullptr) {
            int to = graph->getIndexVertex((*iterator)->toVertex);
            allEdges.push_back(Edge(i, to, (*iterator)->getWeight()));
            ++iterator;
        }
    }

    std::sort(allEdges.begin(), allEdges.end(), compare);

    int mst_weight = 0;

    std::vector<Edge> result;

    for (auto &item: allEdges) {
        if (merge(item.fromIndex, item.toIndex, graph)) {
            mst_weight += item.weight;
            result.push_back(item);
        }
    }

    std::cout << "All MST edges [source - destination = weight]\n";

    for (auto &item: result) {
        std::cout << item.fromIndex << " - " << item.toIndex << " = " << item.weight << "\n";
    }

    std::cout << std::endl;
    
    std::cout << "Minimum spanning tree weight: " << mst_weight << std::endl;

    delete graph;

    return 0;

}

/* 
Вершины
0 1 2 3 4 или a b c d e

0 ----  4
|     / | \
|   /   |  \
| /     |   \
1 ---- 2 ---- 3

Ребра
0 4 = 1
0 1 = 3
1 2 = 5
1 4 = 4
4 3 = 7
4 2 = 6
2 3 = 2

*/ 