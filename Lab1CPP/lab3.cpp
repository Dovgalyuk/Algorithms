#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

#define N 8
const int dx[N] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[N] = {2, -2, 1, -1, 2, -2, 1, -1};

bool is_valid(int x, int y, const std::string board[N]) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] != '#';
}

void bfs(const std::string board[N], int startX, int startY, int endX, int endY, int dist[N][N], int prevX[N][N], int prevY[N][N]) {
    Queue* queue = queue_create();
    queue_insert(queue, startX);
    queue_insert(queue, startY);
    dist[startX][startY] = 0;

    while (!queue_empty(queue)) {
        int currentX = queue_get(queue);
        queue_remove(queue);
        int currentY = queue_get(queue);
        queue_remove(queue);

        for (int i = 0; i < N; ++i) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];

            if (is_valid(nx, ny, board) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[currentX][currentY] + 1;
                prevX[nx][ny] = currentX;
                prevY[nx][ny] = currentY;
                queue_insert(queue, nx);
                queue_insert(queue, ny);
            }
        }
    }

    queue_delete(queue);
}

void reconstruct_path(int startX, int startY, int endX, int endY, int prevX[N][N], int prevY[N][N], std::string board[N]) {
    int currentX = endX;
    int currentY = endY;
    Vector* pathX = vector_create();
    Vector* pathY = vector_create();

    while (!(currentX == startX && currentY == startY)) {
        vector_resize(pathX, vector_size(pathX) + 1);
        vector_resize(pathY, vector_size(pathY) + 1);
        vector_set(pathX, vector_size(pathX) - 1, currentX);
        vector_set(pathY, vector_size(pathY) - 1, currentY);
        int tempX = currentX;
        currentX = prevX[currentX][currentY];
        currentY = prevY[tempX][currentY];
    }

    vector_resize(pathX, vector_size(pathX) + 1);
    vector_resize(pathY, vector_size(pathY) + 1);
    vector_set(pathX, vector_size(pathX) - 1, startX);
    vector_set(pathY, vector_size(pathY) - 1, startY);

    for (size_t i = vector_size(pathX); i > 0; --i) {
        int x = vector_get(pathX, i - 1);
        int y = vector_get(pathY, i - 1);
        board[x][y] = '0' + (vector_size(pathX) - i);
    }

    vector_delete(pathX);
    vector_delete(pathY);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Fail to open file" << std::endl;
        return -1;
    }

    std::string board[N];
    for (int i = 0; i < N; ++i) {
        std::getline(input, board[i]);
    }

    int startX = -1, startY = -1, endX = -1, endY = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'K') {
                startX = i;
                startY = j;
            } else if (board[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }

    int dist[N][N];
    int prevX[N][N];
    int prevY[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dist[i][j] = -1;
        }
    }

    bfs(board, startX, startY, endX, endY, dist, prevX, prevY);
    reconstruct_path(startX, startY, endX, endY, prevX, prevY, board);

    for (int i = 0; i < N; ++i) {
        std::cout << board[i] << std::endl;
    }

    return 0;
}
