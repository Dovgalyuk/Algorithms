#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

const int MAXN = 200;

int rows = 0, cols = 0;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int parent[MAXN][MAXN];

const int dr[8] = {-1, -1,  0,  1,  1,  1,  0, -1};
const int dc[8] = { 0,  1,  1,  0,  1, -1, -1, -1};

void bfs(int sr, int sc) {
    Queue* q = queue_create();
    dist[sr][sc] = 0;
    parent[sr][sc] = -1;
    queue_insert(q, sr * cols + sc);

    while (!queue_empty(q)) {
        int pos = queue_get(q);
        queue_remove(q);
        int r = pos / cols;
        int c = pos % cols;

        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            while (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] != '#') {
                if (dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[nr][nc] = pos;
                    queue_insert(q, nr * cols + nc);
                }
                nr += dr[d];
                nc += dc[d];
            }
        }
    }
    queue_delete(q);
}

void restore_path(int sr, int sc, int er, int ec) {
    int cur = er * cols + ec;
    int start = sr * cols + sc;
    while (cur != start) {
        int r = cur / cols;
        int c = cur % cols;
        grid[r][c] = '0' + dist[r][c] % 10;
        cur = parent[r][c];
    }
    grid[sr][sc] = '0';
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    ifstream f(argv[1]);
    if (!f.is_open()) return 1;

    string line;
    while (getline(f, line) && !line.empty()) {
        int len = (int)line.size();
        for (int j = 0; j < len; j++)
            grid[rows][j] = line[j];
        grid[rows][len] = '\0';
        rows++;
    }
    f.close();

    cols = 0;
    while (grid[0][cols]) cols++;

    int sr = 0, sc = 0, er = 0, ec = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'Q') { sr = i; sc = j; }
            if (grid[i][j] == 'E') { er = i; ec = j; }
            dist[i][j] = -1;
            parent[i][j] = -1;
        }
    }

    bfs(sr, sc);
    if (dist[er][ec] != -1)
        restore_path(sr, sc, er, ec);

    for (int i = 0; i < rows; i++)
        cout << grid[i] << "\n";

    return 0;
}
