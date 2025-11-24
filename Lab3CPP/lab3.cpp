#include "queue.h"
#include <fstream>
#include <iostream>

using namespace std;

int encodePoint(int x, int y, int m) { return x * m + y; }

void decodePoint(int code, int m, int &x, int &y) {
  x = code / m;
  y = code % m;
}

void createBoard(ifstream &inputFile, int &n, int &m, int **&board,
                 Queue *&queue) {
  inputFile >> n >> m;

  board = new int *[n];
  for (int i = 0; i < n; i++) {
    board[i] = new int[m]();
  }

  queue = queue_create();

  int x, y;
  while (inputFile >> x >> y) {
    x--;
    y--;
    board[x][y] = 1;
    queue_insert(queue, encodePoint(x, y, m));
  }
}

int task(ifstream &inputFile) {
  int n, m;
  int **board = nullptr;
  Queue *queue = nullptr;
  createBoard(inputFile, n, m, board, queue);
  const int dx[4] = {-1, 1, 0, 0};
  const int dy[4] = {0, 0, -1, 1};
  int max_color = 1;
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
      if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0) {
        board[nx][ny] = current_color + 1;
        queue_insert(queue, encodePoint(nx, ny, m));
      }
    }
  }
  for (int i = 0; i < n; i++) {
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
  return 0;
}
