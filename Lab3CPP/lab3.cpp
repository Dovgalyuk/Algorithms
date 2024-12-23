#include <iostream>
#include "vector.h"
#include "queue.h"

using namespace std;

struct Point {
    int x;
    int y;
};

/*void printBoard(const Vector<Vector<int>>& board) {
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl; 
}*/

int main() {
    int N, M;
    cin >> N >> M;

    Vector<Vector<int>> board(N);
    for (int i = 0; i < N; i++) {
        board[i].resize(M, 0);
    }

    int colors = 0;
    Queue<Point> q;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    int x, y;
    cin >> x >> y;
    board[x - 1][y - 1] = 1;
    q.insert({x - 1, y - 1});

    //printBoard(board);

    while (!q.empty()) {
        Point curr = q.get();
        q.remove();

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && board[nx][ny] == 0) {
                board[nx][ny] = board[curr.x][curr.y] + 1;
                colors = max(colors, board[nx][ny]);
                q.insert({nx, ny});

                //printBoard(board);
            }
        }
        
    }

    
    cout << colors << endl;

    return 0;
}