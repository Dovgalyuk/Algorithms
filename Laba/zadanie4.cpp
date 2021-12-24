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

int parent[100];
int rank[100];

void init_dsu() {
    for (int i = 0; i < 100; i++) {
        parent[i] = i;
        rank[i] = 1;
    }
}

int get_root(int v) {
    if (parent[v] == v) {
        return v;
    } else {
        return parent[v] = get_root(parent[v]);
    }
}

bool merge(int a, int b) {
    int ra = get_root(a), rb = get_root(b);

    if (ra == rb) {
        return false;
    } else {
        if (rank[ra] < rank[rb]) {
            parent[ra] = rb;
        } else if (rank[rb] < rank[ra]) {
            parent[rb] = ra;
        } else {
            parent[ra] = rb;
            rank[rb]++;
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

    int edges[countEdge][3] {{0, 4, 1}, {0, 1, 3}, {1, 2, 5}, {1, 4, 4}, {4, 3, 7}, {4, 2, 6}, {2, 3, 2}};


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

    init_dsu();

    for (auto &item: allEdges) {
        if (merge(item.fromIndex, item.toIndex)) {
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