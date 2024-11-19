#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

void bfs(int** graph, int num_vertices, int start, const string &filename) {
    int* distances = new int[num_vertices];
    for (size_t i = 0; i < num_vertices; i++) distances[i] = -1;
    distances[start] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (size_t i = 0; i < num_vertices; i++) {
            if (graph[current][i] == 1 && distances[i] == -1) {
                distances[i] = distances[current] + 1;
                queue_insert(queue, (Data)i);
            }
        }
    }

    ofstream output(filename);
    for (size_t i = 0; i < num_vertices; i++) output << distances[i] << endl;
    output.close();
}

int main(int argc, char* argv[]){
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    
    int num_vertices;
    input >> num_vertices;

    int** graph = new int*[num_vertices];
    for (size_t i = 0; i < num_vertices; i++) {
        graph[i] = new int[num_vertices];
        for (size_t j = 0; j < num_vertices; j++) input >> graph[i][j];
    }

    bfs(graph, num_vertices, 0, argv[2]);

    for (size_t i = 0; i < num_vertices; i++) delete[] graph[i];
    delete[] graph;

    input.close();

    return 0;
}