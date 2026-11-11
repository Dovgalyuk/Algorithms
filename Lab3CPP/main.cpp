#include <iostream>
#include <fstream>
#include "helper.h"
#include "vector.h"
#include "queue.h"

void bfs(const Vector* arr, Vector* parent, int start, int end);
bool solve(Vector* arr, int start, int end);

int main() {
    std::ifstream input("input.txt");

    if (!input.is_open()) return 1;

    Vector* arr = vector_create();

    int start = -1, end = -1;

    if (!reader(input, arr, &start, &end)) {
        vector_delete(arr);
        return 1;
    }

    bool found = solve(arr, start, end);

    if (found) writer(std::cout, arr);

    vector_delete(arr);

    return found ? 0 : 1;
}

void bfs(const Vector* arr, Vector* parent, const int start, const int end) {
    Queue* q = queue_create();

    queue_insert(q,start);
    vector_set(parent, start, start);

    while (!queue_empty(q)) {
        int pos = queue_get(q);
        queue_remove(q);

        if (pos == end) break;

        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                if (i * i + j * j != 5) continue;

                int row = pos / 8 + i;
                int col = pos % 8 + j;

                if (row < 0 || row >= 8 || col < 0 || col >= 8) continue;

                int next = row * 8 + col;

                if (vector_get(arr, next) == '#') continue;

                if (vector_get(parent, next) != -1) continue;

                vector_set(parent, next, pos);
                queue_insert(q, next);
            }
        }
    }
    queue_delete(q);
}

bool solve(Vector* arr, int start, int end) {
    Vector* parent = vector_create();

    for (int i = 0; i < 64; i++) vector_set(parent, i, -1);

    bfs(arr, parent, start, end);

    bool found = vector_get(parent, end) != -1;

    if (found) {
        int steps = 0;
        int pos = end;

        for (; pos != start; pos = vector_get(parent, pos)) steps++;

        pos = end;

        while (pos != start) {
            vector_set(arr, pos, -steps);
            steps--;

            pos = vector_get(parent, pos);
        }
        vector_set(arr, start, 0);
    }

    vector_delete(parent);

    return found;
}