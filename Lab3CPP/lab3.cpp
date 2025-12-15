#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

int bfs(int n, int start, int finish, int** graph) {
    if (start == finish) return 0;
    
    Queue* q = queue_create();
    int* distances = new int[n];
    
    for (int i = 0; i < n; i++) 
        distances[i] = -1;  
    
    distances[start - 1] = 0;
    queue_insert(q, start);
    
    bool found = false;
    

    while (!queue_empty(q) && !found) {
        int current = queue_get(q);
        queue_remove(q);
        
        for (int i = 0; i < n; i++) {
            if (graph[current - 1][i] == 1 && distances[i] == -1) {
                distances[i] = distances[current - 1] + 1;
                
                if (i + 1 == finish) {
                    found = true;
                    break;
                }
                
                queue_insert(q, i + 1);
            }
        }
    }
    
    int result = distances[finish - 1 ];
    queue_delete(q);
    delete[] distances;
    
    return result;
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    
    ifstream input(argv[1]);
    
    if (!input.is_open()) return 1;
    
    int n, start, finish;
    input >> n >> start >> finish;
    
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++)
            input >> graph[i][j];
    }
    
    int result = bfs(n, start, finish, graph);
    
    if (result == -1)
        cout << "IMPOSSIBLE" << endl;
    else 
        cout << result << endl;
    
    
    for (int i = 0; i < n; i++) 
         delete[] graph[i];
    
    delete[] graph;
    
    input.close();
    return 0;
}