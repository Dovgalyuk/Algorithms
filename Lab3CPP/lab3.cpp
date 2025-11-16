#include "queue.h"
#include "vector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int encode(int row, int col, int cols) {
    return row * cols + col;
}

void decode(int code, int cols, int& row, int& col) {
    row = code / cols;
    col = code % cols;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        return 1;
    }

    vector<string> board;
    string line;
    while (getline(fin, line)) {
        board.push_back(line);
    }
    fin.close();

    int rows = (int)board.size();
    int cols = rows > 0 ? (int)board[0].size() : 0;

    int start = -1;
    int end = -1;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] == 'K') start = encode(r, c, cols);
            if (board[r][c] == 'E') end = encode(r, c, cols);
        }
    }
    if (start == -1 || end == -1) {
        return 1;
    }

    const int dr[8] = { -2,-1,1,2,2,1,-1,-2 };
    const int dc[8] = { 1,2,2,1,-1,-2,-2,-1 };

    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    vector<vector<int>> parent(rows, vector<int>(cols, -1));

    int sr, sc;
    decode(start, cols, sr, sc);
    dist[sr][sc] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int cur = queue_get(queue);
        queue_remove(queue);

        if (cur == end) break;

        int r, c;
        decode(cur, cols, r, c);

        for (int i = 0; i < 8; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                board[nr][nc] != '#' && dist[nr][nc] == -1) {

                dist[nr][nc] = dist[r][c] + 1;
                parent[nr][nc] = cur;
                queue_insert(queue, encode(nr, nc, cols));
            }
        }
    }

    queue_delete(queue);

    vector<string> output = board;

    int er, ec;
    decode(end, cols, er, ec);

    if (dist[er][ec] != -1) {
        int cur = end;
        while (cur != -1) {
            int r, c;
            decode(cur, cols, r, c);

            output[r][c] = '0' + (dist[r][c] % 10);

            cur = parent[r][c];
        }
    }

    for (const auto& row : output) {
        cout << row << '\n';
    }

    return 0;
}





















