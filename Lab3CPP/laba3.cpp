#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"
using namespace std;

void bfs(int start, Vector* adjacency_matrix, int n, Vector* visited, Vector* component) {
    Queue* queue = queue_create();
    
    vector_set(visited, start, 1);
    vector_set(component, start, 1);
    queue_insert(queue, start);
    
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);
        
        for (int j = 0; j < n; j++) {
            int is_adjacent = vector_get(adjacency_matrix, current * n + j);
            if (is_adjacent && !vector_get(visited, j)) {
                vector_set(visited, j, 1);
                vector_set(component, j, 1);
                queue_insert(queue, j);
            }
        }
    }
    
    queue_delete(queue);
}

void task(std::ifstream& in) {
    int n;
    in >> n;

    Vector* adjacency_matrix = vector_create();
    vector_resize(adjacency_matrix, n * n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int value;
            in >> value;
            vector_set(adjacency_matrix, i * n + j, value);
        }
    }
    
    Vector* visited = vector_create();
    vector_resize(visited, n);
   
    int component_count = 0;

    Vector* temp_visited = vector_create();
    vector_resize(temp_visited, n);  
    for (int i = 0; i < n; i++) {
        if (!vector_get(temp_visited, i)) {
            Vector* temp_component = vector_create();
            vector_resize(temp_component, n);
            bfs(i, adjacency_matrix, n, temp_visited, temp_component);
            vector_delete(temp_component);
            component_count++;
        }
    }
    cout << component_count << endl;
    vector_delete(temp_visited);

    for (int i = 0; i < n; i++) {
        if (!vector_get(visited, i)) {

            Vector* component = vector_create();
            vector_resize(component, n);

            bfs(i, adjacency_matrix, n, visited, component);

            bool first = true;
            for (int j = 0; j < n; j++) {
                if (vector_get(component, j)) {
                    if (!first) cout << " ";
                    cout << (j + 1);
                    first = false;
                }
            }
            cout << endl;
            vector_delete(component);          
        }
    }
    vector_delete(adjacency_matrix);
    vector_delete(visited);
}

int main(int argc, char **argv) {
    std::ifstream in(argv[1]);
    task(in);
    in.close();
}