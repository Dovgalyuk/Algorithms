#include "lab3.h"

void finding_way_matrix(FILE* input, FILE* output) {
    int vertices, start, end;
    if (fscanf(input, "%d %d %d", &vertices, &start, &end) < 1) {
        throw std::invalid_argument("Invalid argument");
    }

    start--;
    end--;

    std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices));

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (fscanf(input, "%d", &matrix[i][j]) < 1) {
                throw std::invalid_argument("Invalid num");
            }
        }
    }

    std::vector<int> distanse(vertices, -1);
    distanse[start] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int v1  = queue_get(queue);
        queue_remove(queue);

        for (int v2 = 0; v2 < vertices; v2++) {
            if (matrix[v1][v2] != 0 && distanse[v2] == -1) {
                distanse[v2] = distanse[v1] + 1;
                queue_insert(queue, v2);
            }
        }
    }

    if (distanse[end] != -1) {
        fprintf(output, "%d", distanse[end]);
    } else {
        fprintf(output, "%s", "IMPOSSIBLE");
    }

    queue_delete(queue);
}
