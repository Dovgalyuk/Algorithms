#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"  
#include "vector.h" 

using namespace std;

const int N = 8; 

const int moves[8][2] = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};

void solveKnightPath(vector<string>& board) {
    Queue* q = queue_create(); 
    Vector* steps = vector_create(); 

    for (int i = 0; i < N * N; i++) {
        vector_resize(steps, i + 1);
        vector_set(steps, i, -1); 
    }

    int startIdx = -1, endIdx = -1;

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (board[r][c] == 'K') {
                startIdx = r * N + c;
                vector_set(steps, startIdx, 0); 
                queue_insert(q, startIdx);
            } else if (board[r][c] == 'E') {
                endIdx = r * N + c;
            }
        }
    }

    while (!queue_empty(q)) {
        int idx = queue_get(q);
        queue_remove(q);

        int r = idx / N;
        int c = idx % N;
        int step = vector_get(steps, idx);

        if (idx == endIdx) {
            break; 
        }

        for (auto& move : moves) {
            int nr = r + move[0];
            int nc = c + move[1];
            int newIdx = nr * N + nc;

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] != '#' &&
                vector_get(steps, newIdx) == -1) {
                vector_set(steps, newIdx, step + 1);
                queue_insert(q, newIdx);
            }
        }
    }

    int r = endIdx / N, c = endIdx % N;
    int pathLen = vector_get(steps, endIdx);
    while (pathLen > 0) {
        board[r][c] = static_cast<char>('0' + pathLen); 
        for (auto& move : moves) {
            int nr = r - move[0];
            int nc = c - move[1];
            int prevIdx = nr * N + nc;

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                vector_get(steps, prevIdx) == pathLen - 1) {
                r = nr;
                c = nc;
                break;
            }
        }
        pathLen--;
    }

    board[startIdx / N][startIdx % N] = static_cast<char>('0'); 

    queue_delete(q);
    vector_delete(steps);
}

int main(int argc, char* argv[]) {
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        getline(*input, board[i]);
    }

    solveKnightPath(board);

    for (const auto& row : board) {
        cout << row << endl;
    }

    return 0;
}
