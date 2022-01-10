#include <iostream>
#include "graph.h"
#include <vector>
#include <algorithm>

struct Edge {
    int weight, fromIndex, toIndex;
    Edge (int fromIndex, int toIndex, int weight) {
        this->weight = weight;
        this->fromIndex = fromIndex;
        this->toIndex = toIndex;
    }
};

struct DataVertex {
    int data = 0;
    int label = 0;
    bool check = true;
    DataVertex() {}
};

bool compare(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

bool equals(const Edge& a, const Edge& b) {
    if (a.fromIndex == b.fromIndex || a.toIndex == b.toIndex || a.toIndex == b.fromIndex || a.fromIndex == b.toIndex) return true;
    else return false;
}

void changeVector(std::vector<std::vector<Edge>>& multiEdges, Edge& item, int min, int max, int &count) {
    multiEdges[min].push_back(item);
    multiEdges[min].insert(multiEdges[min].end(), multiEdges[max].begin(), multiEdges[max].end());
    for (int i = max; i < multiEdges.size() - 1; i++) {
       multiEdges[i] = multiEdges[i+1];
    }
    multiEdges.pop_back();
    count--;
}

bool merge(Edge item, Graph<DataVertex>* graph, std::vector<std::vector<Edge>>& multiEdges, int &count) {
    const int fromIndex = item.fromIndex, toIndex = item.toIndex;
    DataVertex uRepData = graph->getDataVertex(fromIndex);
    DataVertex vRepData = graph->getDataVertex(toIndex);
    if (uRepData.check && vRepData.check) {
        uRepData.check = false;
        vRepData.check = false;
        count++;
        multiEdges.emplace_back().push_back(item);
        graph->setDataVertex(fromIndex, uRepData);
        graph->setDataVertex(toIndex, vRepData);
        return true;
    }
    if (!uRepData.check && vRepData.check) {
        vRepData.check = false;
        for (int i = 0; i < count - 1; i++) {
            for (int j = i; j < count; j++) {
                if (equals(item, multiEdges[i][j])) {
                    multiEdges[i].push_back(item);
                }
            }
        }
        graph->setDataVertex(toIndex, vRepData);
        return true;
    }
    if (uRepData.check && !vRepData.check) {
        uRepData.check = false;
        for (int i = 0; i < count - 1; i++) {
            for (int j = i; j < count; j++) {
                if (equals(item, multiEdges[i][j])) {
                    multiEdges[i].push_back(item);
                }
            }
        }
        graph->setDataVertex(fromIndex, uRepData);
        return true;
    }
    return false;
}

int main() {

    int numberVertex = 6;

    const int countEdge = 10;

    DataVertex data_v;

    auto graph = new Graph<DataVertex>(numberVertex, data_v);

    for (int i = 0; i < numberVertex; i++) {
        data_v.data = i;
        graph->setDataVertex(i, data_v);
    }

    int edges[countEdge][3] {{0, 1, 6}, {0, 2, 1}, {0, 3, 5}, {1, 2, 5}, {2, 3, 5},
                             {1, 4, 3}, {2, 4, 6}, {2, 5, 4}, {4,5,6}, {3,5,2}};

    for (auto & edge : edges) {
        graph->addEdge(graph->getVertex(edge[0]), graph->getVertex(edge[1]), edge[2]);
    }

    std::vector<Edge> allEdges;

    // we get all the values of the edges and their vertices
    for (int i = 0; i < graph->sizeVertexex(); i++) {
        auto* item = graph->getVertex(i);

        Graph<DataVertex>::EdgeIterator iterator(item);

        while (*iterator != nullptr) {
            int to = graph->getIndexVertex((*iterator)->toVertex);
            allEdges.emplace_back(i, to, (*iterator)->getWeight());
            ++iterator;
        }
    }

    std::sort(allEdges.begin(), allEdges.end(), compare);

    int minWeight = 0;
    int count = 0;
    std::vector<Edge> result;
    std::vector<Edge> noResult;
    std::vector<std::vector<Edge>> multiEdges;

    for (auto &item: allEdges) {
        if (merge(item, graph, multiEdges, count)) {
            minWeight += item.weight;
            result.push_back(item);
        } else {
            noResult.push_back(item);
        }
    }

    bool check1 = false;
    bool check2 = false;
    int minPosIndex, maxPosIndex;
    for (auto &item: noResult) {
        if (count == 1) break;
        for (int i = 0; i < count - 1; i++) {
            for (auto &itemCheck: multiEdges[i]) {
                if (equals(item, itemCheck)) {
                    check1 = true;
                    minPosIndex = i;
                    break;
                }
            }
            if (check1) break;
        }
        for (int i = minPosIndex+1; i < count; i++) {
            for (auto &itemCheck: multiEdges[i]) {
                if (equals(item, itemCheck)) {
                    check2 = true;
                    maxPosIndex = i;
                }
            }
            if (check2) break;
        }
        if (check1 && check2) {
            changeVector(multiEdges, item, minPosIndex, maxPosIndex, count);
            minWeight += item.weight;
            result.push_back(item);
        }
    }

    std::cout << "All MST edges [source - destination = weight]\n";
    for (auto &item: result) {
        std::cout << item.fromIndex << " - " << item.toIndex << " = " << item.weight << "\n";
    }
    std::cout << std::endl;
    std::cout << "Minimum spanning tree weight: " << minWeight << std::endl;

    delete graph;
    return 0;
}
