#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;

static inline int pack(int x, int y) {
    return (x << 8) | y;
}

static inline void unpack(int d, int &x, int &y) {
    x = (d >> 8) & 0xFF;
    y = d & 0xFF;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "No input file\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open file\n";
        return 1;
    }

    const int N = 8;
    vector<string> board(N);
    for (int i = 0; i < N; ++i) fin >> board[i];

    int sx = -1, sy = -1, ex = -1, ey = -1;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'K') { sx = i; sy = j; }
            if (board[i][j] == 'E') { ex = i; ey = j; }
        }

    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int,int>>> parent(N, vector<pair<int,int>>(N, {-1,-1}));

    Queue* q = queue_create();

    dist[sx][sy] = 0;
    queue_insert(q, pack(sx, sy));

    int dx[8] = {-2,-2,-1,-1,1,1,2,2};
    int dy[8] = {-1,1,-2,2,-2,2,-1,1};

    // --- BFS ---
    while (!queue_empty(q)) {
        int d = queue_get(q);
        queue_remove(q);

        int x, y;
        unpack(d, x, y);

        if (x == ex && y == ey) break;

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (board[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1;
            parent[nx][ny] = {x, y};
            queue_insert(q, pack(nx, ny));
        }
    }

    queue_delete(q);

    // --- восстановление пути ---
    vector<vector<char>> out(N, vector<char>(N));

    // копируем доску
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            out[i][j] = board[i][j];

    // если путь найден
    if (dist[ex][ey] != -1) {
        int x = ex, y = ey;
        int step = dist[x][y];

        while (!(x == sx && y == sy)) {
            out[x][y] = (step < 10 ? '0' + step : '0' + (step % 10));
            auto p = parent[x][y];
            x = p.first; 
            y = p.second;
            step--;
        }

        out[sx][sy] = '0';
    }

    // --- вывод ---
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << out[i][j];
        cout << "\n";
    }
}
