#include <iostream>
#include <vector>
#include "queue.h" 
using namespace std;

const int INF = 1000000000;

vector<int> bfs(vector<vector<int>>& graph, int start) {
    vector<int> dist(graph.size(), INF);
    Queue* que = queue_create();

    dist[start] = 0;
    queue_insert(que, start);

    while (!queue_empty(que)) {
        int CurrentV = queue_get(que);
        queue_remove(que);
        for (size_t to = 0; to < graph.size(); ++to) {
            if (graph[CurrentV][to] && dist[to] == INF) {
                dist[to] = dist[CurrentV] + 1;
                queue_insert(que, static_cast<int>(to));
            }
        }
    }
    queue_delete(que);
    return dist;
}

int main() {
    int MatrixSize;
    cout << "Enter the matrix size: ";
    cin >> MatrixSize;

    vector<vector<int>> graph(MatrixSize, vector<int>(MatrixSize));

    cout << "Enter matrix elements:" << endl;
    for (int Row = 0; Row < MatrixSize; ++Row){
        for (int Column = 0; Column < MatrixSize; ++Column){
            cin >> graph[Row][Column];
        }
    }
    cout << endl;
    vector<int> dist = bfs(graph, 0);

    for (int d : dist) {
        if (d != INF)
            cout << d << "\n";
        else
            cout << "X ";
    }
    return 0;
}

