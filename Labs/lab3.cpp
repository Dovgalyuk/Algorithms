#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CheckCoords(int x, int y, int N, int M);
void CheckLeft(int** board, Queue* coords, int x, int y, int k);
void CheckRight(int** board, Queue* coords, int x, int y, int M, int k);
void CheckTop(int** board, Queue* coords, int x, int y, int k);
void CheckBottom(int** board, Queue* coords, int x, int y, int N, int k);
int SetColor(int** board, Queue* coords, int N, int M);
void PrintBoard(int** board, int N, int M);

int main() {
	Queue* coords = queue_create();

	string inputNameFile = "input.txt";
	ifstream inputFile(inputNameFile);
	if (!inputFile.is_open()) {
		cout << "Error: Couldn't open " << inputNameFile << endl;
	}
	else {
		int N, M, x, y;
		inputFile >> N >> M;
		int** board = new int* [N] {0};
		for (int i = 0; i < N; i++) {
			board[i] = new int[M] {0};
		}

		while (inputFile >> x >> y) {
			if (CheckCoords(x, y, N, M)) {
				x--;
				y--;
				board[x][y] = 1;

				queue_insert(coords, x);
				queue_insert(coords, y);
			}
		}
		inputFile.close();

		
		cout << "Result: " << SetColor(board, coords, N, M) << endl;
		PrintBoard(board, N, M);

		for (int i = 0; i < N; i++) {
			delete[] board[i];
		}
		delete[] board;
		queue_delete(coords);
	}

	return 0;
}

bool CheckCoords(int x, int y, int N, int M) {
	bool flags = true;
	if ((x < 1 || x > M) || (y < 1 || y > N)) {
		flags = false;
		cout << "Checking coordinates: error coordinates" << endl;
		cout << "Coordinates: " << x << " " << y << endl;
	}

	return flags;
}

void CheckLeft(int** board, Queue* coords, int x, int y, int k) {
	x--;
	if (x >= 0 && board[x][y] == 0) {
		board[x][y] = k + 1;
		queue_insert(coords, x);
		queue_insert(coords, y);
	}
}

void CheckRight(int** board, Queue* coords, int x, int y, int M, int k) {
	x++;
	if (x < M && board[x][y] == 0) {
		board[x][y] = k + 1;
		queue_insert(coords, x);
		queue_insert(coords, y);
	}
}

void CheckTop(int** board, Queue* coords, int x, int y, int k) {
	y--;
	if (y >= 0 && board[x][y] == 0) {
		board[x][y] = k + 1;
		queue_insert(coords, x);
		queue_insert(coords, y);
	}
}

void CheckBottom(int** board, Queue* coords, int x, int y, int N, int k) {
	y++;
	if (y < N && board[x][y] == 0) {
		board[x][y] = k + 1;
		queue_insert(coords, x);
		queue_insert(coords, y);
	}
}

int SetColor(int** board, Queue* coords, int N, int M) {
	int k = 0;
	
	while (!queue_empty(coords)) {
		int x = queue_get(coords);
		queue_remove(coords);

		int y = queue_get(coords);
		queue_remove(coords);

		k = board[x][y];

		CheckRight(board, coords, x, y, M, k);
		CheckBottom(board, coords, x, y, N, k);
		CheckLeft(board, coords, x, y, k);
		CheckTop(board, coords, x, y, k);
	}

	return k;
}


void PrintBoard(int** board, int N, int M) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
