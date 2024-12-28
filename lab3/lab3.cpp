#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

struct Cell {
    int x, y, intensity;
};

bool is_valid(int x, int y, int n, int m, const Vector* board) {
    unsigned long long size = (unsigned long long)x * m + y;
    return x >= 0 && x < n && y >= 0 && y < m && vector_get(board, size) == 0;
}

int color_board(int n, int m, const Vector* initial_cells) {
    Vector* board = vector_create();
    unsigned long long index1 = (unsigned long long)n * m;
    vector_resize(board, index1);

    for (size_t i = 0; i < vector_size(board); ++i) {
        vector_set(board, i, 0);
    }

    for (size_t i = 0; i < vector_size(initial_cells); i += 3) {
        int x = vector_get(initial_cells, i);
        int y = vector_get(initial_cells, i + 1);
        int intensity = vector_get(initial_cells, i + 2);
        unsigned long long index = (unsigned long long)x * m + y;
        vector_set(board, index, intensity);
    }

    Queue* q = queue_create();
    for (size_t i = 0; i < vector_size(initial_cells); i += 3) {
        int x = vector_get(initial_cells, i);
        int y = vector_get(initial_cells, i + 1);
        int intensity = vector_get(initial_cells, i + 2);
        queue_insert(q, x);
        queue_insert(q, y);
        queue_insert(q, intensity);
    }

    int max_intensity = 1;
    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    while (!queue_empty(q)) {
        int x = queue_get(q);
        queue_remove(q);
        int y = queue_get(q);
        queue_remove(q);
        int intensity = queue_get(q);
        queue_remove(q);

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (is_valid(nx, ny, n, m, board)) {
                unsigned long long index2 = (unsigned long long)nx * m + ny;
                vector_set(board, index2, intensity + 1);
                max_intensity = std::max(max_intensity, intensity + 1);
                queue_insert(q, nx);
                queue_insert(q, ny);
                queue_insert(q, intensity + 1);
            }
        }
    }

    queue_delete(q);
    vector_delete(board);
    return max_intensity;
}

int main(int argc, char** argv) {
    int n, m;
    if (argc > 1) {
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Cannot open file: " << argv[1] << '\n';
            return 1;
        }
        input >> n >> m;
    }
    else {
        std::cout << "argc <= 1\nn=3; m=3\n";
        n = 3;
        m = 3;
    }

    Vector* initial_cells = vector_create();
    int x, y;
    if (argc > 1) {
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Failed to open input file." << std::endl;
            return 1;
        }
        while (input >> x >> y) {
            vector_resize(initial_cells, vector_size(initial_cells) + 3);
            vector_set(initial_cells, vector_size(initial_cells) - 3, x - 1);
            vector_set(initial_cells, vector_size(initial_cells) - 2, y - 1);
            vector_set(initial_cells, vector_size(initial_cells) - 1, 1);
        }
    }
    else {
        std::cout << "x=1;y=1\n";
        x = 1;
        y = 1;
        vector_resize(initial_cells, vector_size(initial_cells) + 3);
        vector_set(initial_cells, vector_size(initial_cells) - 3, x - 1);
        vector_set(initial_cells, vector_size(initial_cells) - 2, y - 1);
        vector_set(initial_cells, vector_size(initial_cells) - 1, 1);
    }

    int result = color_board(n, m, initial_cells);
    std::cout << "colors count: " << result << std::endl;

    vector_delete(initial_cells);
    return 0;
}