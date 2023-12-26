#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#include "graph.h"

using namespace std;

Graph<int, int> primMinimumTree(Graph<int, int>& graph, size_t index) {
    size_t vertexAmount = graph.getVertexAmount();
    Graph<int, int> minimumTree(vertexAmount);

    vector<bool> inTree(vertexAmount, false);
    inTree[index] = true;
    vector<vector<int>> adjacencyMatrix(vertexAmount, vector<int>(vertexAmount, INT_MAX));
    for (size_t i = 0; i < vertexAmount; i++) {
        Graph<int, int>::Iterator iterator= graph.getIterator(i);
        while (*iterator) {
            adjacencyMatrix[i][iterator.getIndex()] = graph.getEdge(i, iterator.getIndex())->getEdgeData();
            ++iterator;
        }
    }
     while (std::find(inTree.begin(), inTree.end(), false) != inTree.end()) {
        bool isChange = false;
        int minimum = INT_MAX;
        size_t start;
        size_t end;
        for (size_t i = 0; i < vertexAmount; i++) {
            if (inTree[i] == true) {
                for (size_t j = 0; j < vertexAmount; j++) {
                    if (adjacencyMatrix[i][j] < minimum && inTree[j]==false) {
                        minimum = adjacencyMatrix[i][j];
                        start = i;
                        end = j;
                        isChange = true;
                    }
                }
            }
        }
        if (isChange) {
            minimumTree.addEdge(start, end, minimum);
            inTree[end] = true;
        }
        else {
            break;
        }
    }
    return minimumTree;
}



int main() {
    //Ввод кол-ва вершин
    //size_t vertexAmount;
    //cout << "Enter vertex amount: ";
    //cin >> vertexAmount;

    //Graph<int, int> graph(vertexAmount);

    ////Ввод ребер
    //size_t edgeAmount;
    //cout << "Enter edge amount: ";
    //cin >> edgeAmount;
    //for (size_t i = 0; i < edgeAmount; i++) {
    //    size_t start, end;
    //    int data;
    //    cout << "Enter vertex start(0-" << vertexAmount - 1 << "), vertex(0-" << vertexAmount - 1 << ") end and data: ";
    //    cin >> start >> end >> data;
    //    graph.addEdge(start, end, data);
    //}

    ////С какой вершины начинать строить дерево?
    //size_t vertexRoot;
    //cout << "From which top should we build a tree ?\n";
    //cin >> vertexRoot;
    // Пример ввода графа
    Graph<int, int> graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 8);


    /*Graph<int> answer = primMinimumTree(graph, 0);*/
    Graph<int, int> answer = primMinimumTree(graph, 0);
    // Вывод минимального остовного дерева
    std::cout << "Minimum Spanning Tree:\n";
    int sum = 0;
    for (size_t i = 0; i < answer.getVertexAmount(); ++i) {
        Graph<int, int>::Iterator iterator = answer.getIterator(i);
        while (*iterator) {
            int data = answer.getEdge(iterator.getStart(), iterator.getIndex())->getEdgeData();
            sum += data;
            cout << "Edge: " << iterator.getStart() << " -> " << iterator.getIndex() << " Weight = " << data << "\n";
            ++iterator;
        }
    }
    cout << "Minimum amount = " << sum;
}