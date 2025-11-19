#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"
using namespace std;

void bfs(int start, Vector* adjacency_matrix, int n, Vector* visited, int component_id, Vector* component_ids) {
    Queue* queue = queue_create();
    
    vector_set(visited, start, 1);
    vector_set(component_ids, start, component_id);
    queue_insert(queue, start);
    
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);
        
        for (int j = 0; j < n; j++) {
            int is_adjacent = vector_get(adjacency_matrix, current * n + j);
            if (is_adjacent && !vector_get(visited, j)) {
                vector_set(visited, j, 1);
                vector_set(component_ids, j, component_id);
                queue_insert(queue, j);
            }
        }
    }    
    queue_delete(queue);
}

void task(ifstream& in) {
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

    Vector* component_ids = vector_create();
    vector_resize(component_ids, n);
   
    int component_count = 0;
 
    for (int i = 0; i < n; i++) {
        if (!vector_get(visited, i)) {
            bfs(i, adjacency_matrix, n, visited, component_count + 1, component_ids);
            component_count++;
        }
    }
    cout << component_count << endl;

    for (int comp_id = 1; comp_id <= component_count; comp_id++) {
        bool first = true;
        for (int j = 0; j < n; j++) {
            if (vector_get(component_ids, j) == comp_id) {
                if (!first) cout << " ";
                cout << (j + 1);
                first = false;
            }
        }
        cout << endl;          
    }
    vector_delete(adjacency_matrix);
    vector_delete(visited);
    vector_delete(component_ids);
}

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    task(in);
    in.close();
}