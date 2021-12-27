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

struct dataVertex {
    int data = 0;
    int label = 0;

    dataVertex() {}
};

bool compare(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int get_root(int v, Graph<dataVertex>* graph) {

    dataVertex data_v = graph->getDataVertex(v);

    if (v == data_v.data) {
        return v;
    }
    else {
        data_v.data = get_root(data_v.data, graph);
        graph->setDataVertex(v, data_v);
        return graph->getDataVertex(v).data;
    }
}

bool merge(int a, int b, Graph<dataVertex>* graph) {
    int ra = get_root(a, graph), rb = get_root(b, graph);

    if (ra == rb) {
        return false;
    }
    else {

        dataVertex ra_data = graph->getDataVertex(ra);
        dataVertex rb_data = graph->getDataVertex(rb);

        if (ra_data.label < rb_data.label) {
            ra_data.data = rb_data.data;
            graph->setDataVertex(ra, ra_data);
        }
        else if (rb_data.label < ra_data.label) {
            rb_data.data = ra_data.data;
            graph->setDataVertex(rb, rb_data);
        }
        else {
            ra_data.data = rb_data.data;
            graph->setDataVertex(ra, ra_data);

            rb_data.label = rb_data.label + 1;
            graph->setDataVertex(rb, rb_data);
        }

        return true;
    }
}

int main() {

    int numberVertex = 5;

    int countEdge = 7;

    dataVertex data_v;

    Graph<dataVertex> *graph = new Graph<dataVertex>(numberVertex, data_v);

    for (int i = 0; i < numberVertex; i++) {
        data_v.data = i;
        graph->setDataVertex(i, data_v);
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

        Graph<dataVertex>::EdgeIterator iterator(item);

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