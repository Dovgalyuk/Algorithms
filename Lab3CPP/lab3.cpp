#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

int bfs(int n, int start, int finish, int** graph) {
    if (start == finish) return 0;
    
    Queue* q = queue_create();
    bool* visited = new bool[n];
    int* distances = new int[n];
    
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        distances[i] = -1;
    }
    
    visited[start - 1] = true;
    distances[start - 1] = 0;
    queue_insert(q, start);
    
    while (!queue_empty(q)) {
        int current = queue_get(q);
        queue_remove(q);
        
        for (int i = 0; i < n; i++) {
            if (graph[current - 1][i] == 1 && !visited[i]) {
                visited[i] = true;
                distances[i] = distances[current - 1] + 1;
                queue_insert(q, i+1);
                
                if (i+1 == finish) {
                    int result = distances[i];
                    queue_delete(q);
                    delete[] visited;
                    delete[] distances;
                    return result;
                }
            }
        }
    }
    
    queue_delete(q);
    delete[] visited;
    delete[] distances;
    return -1;
}

int main(int argc, char** argv) {
    if (argc < 2)
        return 1;
    
    ifstream input(argv[1]);
    
    if (!input.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    
    int n, start, finish;
    input >> n >> start >> finish;
    
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++)
            input >> graph[i][j];

    }
    
    int result = bfs(n, start, finish, graph);
    
    if (result == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << result << endl;
    }
    
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    
    input.close();
    return 0;
}