#include <iostream>
#include <vector>
#include "queue.h" 
using namespace std;

const int INF = 1000000000;

vector<int> bfs(vector<vector<int>>& graph, int start) {
    vector<int> dist(graph.size(), INF);
    Queue* q = queue_create();

    dist[start] = 0;
    queue_insert(q, start);

    while (!queue_empty(q)) {
        int v = queue_get(q);
        queue_remove(q);
        for (size_t to = 0; to < graph.size(); ++to) {
            if (graph[v][to] && dist[to] == INF) {
                dist[to] = dist[v] + 1;
                queue_insert(q, static_cast<int>(to));
            }
        }
    }
    return dist;
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {1, 0, 0, 1},
        {0, 1, 0, 0}}; 

    int start = 0; 

    vector<int> dist = bfs(graph, start);

    for (int d : dist) {
        if (d != INF)
            cout << d << "\n";
        else
            cout << "X ";
    }
    return 0;
}

