#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

struct Node {
    int x, y, step;
};

Data make_data(int x, int y, int step) {
    return (x << 24) | (y << 16) | step;
}

void extract_data(Data d, int &x, int &y, int &step) {
    x = (d >> 24) & 0xFF;
    y = (d >> 16) & 0xFF;
    step = d & 0xFFFF;
}

int main() {
    const int N = 8;
    string board[N];

    for (int i = 0; i < N; i++)
        cin >> board[i];

    int sx = -1, sy = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'K') {
                sx = i;
                sy = j;
            }
        }
    }

    if (sx == -1 || sy == -1) {
    cerr << "Error: K not found on board\n";
    return 1;
}

    int dist[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = -1;

    Queue* q = queue_create();
    queue_insert(q, make_data(sx, sy, 0));
    dist[sx][sy] = 0;

    int dx[8] = {-2,-2,-1,-1,1,1,2,2};
    int dy[8] = {-1,1,-2,2,-2,2,-1,1};

    while (!queue_empty(q)) {
        int x, y, step;
        extract_data(queue_get(q), x, y, step);
        queue_remove(q);

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (board[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = step + 1;
            queue_insert(q, make_data(nx, ny, step + 1));
        }
    }

    queue_delete(q);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == '#')
                cout << '#';
            else if (dist[i][j] == -1)
                cout << '.';
            else {
                if (dist[i][j] < 10)
                    cout << dist[i][j];
                else
                    cout << (dist[i][j] % 10);
            }
        }
        cout << "\n";
    }

    return 0;
}
