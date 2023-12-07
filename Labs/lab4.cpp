#include <iostream>
#include <vector>
#include <climits>

#include "graph.h"


using namespace std;

Graph<int> primMinimumTree(Graph<int>& graph, size_t index) {
    size_t vertexAmount = graph.getVertexAmount();
    Graph<int> minimumTree(vertexAmount);

    vector<bool> inTree(vertexAmount, false);
    inTree[index] = true;
    vector<Graph<int>::Iterator> iterators;
    iterators.push_back(graph.getIterator(index));
    while (iterators.size() != vertexAmount) {
        vector<Graph<int>::Iterator> ways;
        int indexMin = -1;
        int min = INT_MAX;
        for (size_t i = 0; i < iterators.size(); i++) {
            Graph<int>::Iterator iterator = iterators[i];
            while (*iterator) {
                if (!inTree[iterator.getIndex()]) {
                    ways.push_back(iterator);
                    if (graph.getEdge(iterator.getStart(), iterator.getIndex())->getEdgeData() < min) {
                        min = graph.getEdge(iterator.getStart(), iterator.getIndex())->getEdgeData();
                        indexMin = ways.size() - 1;
                    }
                }
                ++iterator;
            }
        }
        if (indexMin != -1) {
            minimumTree.addEdge(ways[indexMin].getStart(), ways[indexMin].getIndex(), min);
            inTree[ways[indexMin].getIndex()] = true;
            iterators.push_back(graph.getIterator(ways[indexMin].getIndex()));
        }
        else {
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
        cout << "Enter vertex start(0-"<<vertexAmount-1<<"), vertex(0-"<<vertexAmount - 1<<") end and data: ";
        cin >> start >> end >> data;
        graph.addEdge(start,end,data);
    }

    //С какой вершины начинать строить дерево?
    size_t vertexRoot;
    cout << "From which top should we build a tree ?\n";
    cin >> vertexRoot;
    // Пример ввода графа
    /*Graph<int> graph(5);*/
   /* graph.addEdge(0, 1, 2);
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
            cout << "Edge: " << iterator.getStart() << " -> " << iterator.getIndex() << " Weight = " << data <<"\n";
            ++iterator;
        }
    }
    cout << "Minimum amount = " << sum;
}