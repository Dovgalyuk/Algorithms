#include "queue.h"
#include <fstream>
#include <iostream>

using namespace std;

int encodePoint(int x, int y, int m) { return x * (m + 2) + y; }

void decodePoint(int code, int M, int &x, int &y) {
  x = code / (M + 2);
  y = code % (M + 2);
}

void createBoard(ifstream &inputFile, int &n, int &m, int **&board,
                 Queue *&queue) {
  inputFile >> n >> m;

  board = new int *[n + 2];
  for (int i = 0; i < n + 2; i++) {
    board[i] = new int[m + 2];
    for (int j = 0; j < m + 2; j++) {
      board[i][j] = 0;
    }
  }

  queue = queue_create();

  int x, y;
  while (inputFile >> x >> y) {
    board[x][y] = 1;
    int encoded = encodePoint(x, y, m);
    queue_insert(queue, encoded);
  }
}

int task(ifstream &inputFile) {
  int n, m;
  int **board = nullptr;
  Queue *queue = nullptr;

  createBoard(inputFile, n, m, board, queue);

  int max_color = 1;

  int dx[] = {-1, 1, 0, 0};
  int dy[] = {0, 0, -1, 1};

  while (!queue_empty(queue)) {
    int encoded = queue_get(queue);
    queue_remove(queue);

    int current_x, current_y;
    decodePoint(encoded, m, current_x, current_y);
    int current_color = board[current_x][current_y];

    if (current_color > max_color) {
      max_color = current_color;
    }

    for (int i = 0; i < 4; i++) {
      int nx = current_x + dx[i];
      int ny = current_y + dy[i];

      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && board[nx][ny] == 0) {
        board[nx][ny] = current_color + 1;
        int new_encoded = encodePoint(nx, ny, m);
        queue_insert(queue, new_encoded);
      }
    }
  }

  for (int i = 0; i < n + 2; i++) {
    delete[] board[i];
  }
  delete[] board;
  queue_delete(queue);
  return max_color;
}

int main(int argc, char *argv[]) {
  ifstream inputFile(argv[1]);
  int result = task(inputFile);
  cout << result << endl;
  inputFile.close();
  return 0;
}
