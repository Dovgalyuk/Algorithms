#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#include "graph.h"

using namespace std;

vector< Graph<int>::Iterator> sorted(vector< Graph<int>::Iterator> ways, Graph<int>& graph) {
    size_t size = ways.size();
    for (size_t i = 0; i + 1 < size; ++i) {
        for (size_t j = 0; j + 1 < size - i; ++j) {
            if (graph.getEdge(ways[j+1].getStart(), ways[j+1].getIndex())->getEdgeData() < graph.getEdge(ways[j].getStart(), ways[j].getIndex())->getEdgeData()) {
                swap(ways[j], ways[j + 1]);
            }
        }
    }
    return ways;
}

Graph<int> primMinimumTree(Graph<int>& graph, size_t index) {
    size_t vertexAmount = graph.getVertexAmount();
    Graph<int> minimumTree(vertexAmount);

    vector<bool> inTree(vertexAmount, false);
    inTree[index] = true;
    vector<Graph<int>::Iterator> ways;
    for (size_t i = 0; i < vertexAmount; i++) {
        Graph<int>::Iterator iterator = graph.getIterator(i);
        while (*iterator) {
            ways.push_back(iterator);
            ++iterator;
        }
    }
    ways = sorted(ways, graph);
    while (std::find(inTree.begin(), inTree.end(), false) != inTree.end()) {
        bool isChange = false;
        for (size_t i = 0; i < ways.size(); i++) {
            if (inTree[ways[i].getStart()] == true && inTree[ways[i].getIndex()] == false) {
                minimumTree.addEdge(ways[i].getStart(), ways[i].getIndex(), graph.getEdge(ways[i].getStart(), ways[i].getIndex())->getEdgeData());
                inTree[ways[i].getIndex()] = true;
                isChange = true;
                break;
            }
        }
        if (isChange == false) {
            break;
        }
    }
    return minimumTree;
}



int main() {
    //Ввод кол-ва вершин
    size_t vertexAmount;
    cout << "Enter vertex amount: ";
    cin >> vertexAmount;

    Graph<int> graph(vertexAmount);

    //Ввод ребер
    size_t edgeAmount;
    cout << "Enter edge amount: ";
    cin >> edgeAmount;
    for (size_t i = 0; i < edgeAmount; i++) {
        size_t start, end;
        int data;
        cout << "Enter vertex start(0-" << vertexAmount - 1 << "), vertex(0-" << vertexAmount - 1 << ") end and data: ";
        cin >> start >> end >> data;
        graph.addEdge(start, end, data);
    }

    //С какой вершины начинать строить дерево?
    size_t vertexRoot;
    cout << "From which top should we build a tree ?\n";
    cin >> vertexRoot;
    // Пример ввода графа
    /*Graph<int> graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 8);*/


    /*Graph<int> answer = primMinimumTree(graph, 0);*/
    Graph<int> answer = primMinimumTree(graph, vertexRoot);
    // Вывод минимального остовного дерева
    std::cout << "Minimum Spanning Tree:\n";
    int sum = 0;
    for (size_t i = 0; i < answer.getVertexAmount(); ++i) {
        Graph<int>::Iterator iterator = answer.getIterator(i);
        while (*iterator) {
            int data = answer.getEdge(iterator.getStart(), iterator.getIndex())->getEdgeData();
            sum += data;
            cout << "Edge: " << iterator.getStart() << " -> " << iterator.getIndex() << " Weight = " << data << "\n";
            ++iterator;
        }
    }
    cout << "Minimum amount = " << sum;
}