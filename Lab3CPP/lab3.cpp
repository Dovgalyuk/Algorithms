#include <iostream>
#include <fstream>
#include "queue.h"

int solve_bfs(int N, int start, int finish, int* matrix) {
    int* dist = new int[N];
    for (int i = 0; i < N; ++i) dist[i] = -1;

    Queue* q = queue_create();
    dist[start] = 0;
    queue_insert(q, start);

    while (!queue_empty(q)) {
        int u = queue_get(q);
        queue_remove(q);

        if (u == finish) break;

        for (int v = 0; v < N; ++v) {
            if (matrix[u * N + v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue_insert(q, v);
            }
        }
    }

    int result = dist[finish];

    queue_delete(q);
    delete[] dist;
    
    return result;
}

int main(int argc, char* argv[]) {
    std::istream* in = &std::cin;
    std::ifstream infile;
    if (argc > 1) {
        infile.open(argv[1]);
        if (infile.is_open()) in = &infile;
    }

    int N, start, finish;
    if (!(*in >> N >> start >> finish)) return 0;
    start--; finish--;

    int* matrix = new int[N * N];
    for (int i = 0; i < N * N; ++i) *in >> matrix[i];

    int result = solve_bfs(N, start, finish, matrix);

    if (result != -1) std::cout << result << std::endl;
    else std::cout << "IMPOSSIBLE" << std::endl;

    delete[] matrix;
    if (infile.is_open()) infile.close();

    return 0;
}