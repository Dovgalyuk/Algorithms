#include "queue.h"
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

struct PuzzleState {
    string board;
    int zero_pos;
    vector<string> path;

    PuzzleState(string b, int zp, vector<string> p) : board(b), zero_pos(zp), path(p) {}
};

const vector<int> moves = {-3, 3, -1, 1};

void solvePuzzle(const string &start) {
    string goal = "123456780";
    Queue *queue = queue_create();
    unordered_set<string> visited;

    int zero_pos = start.find('0');
    PuzzleState* initial_state = new PuzzleState(start, zero_pos, vector<string>{start});
    queue_insert(queue, (Data)initial_state);
    visited.insert(start);


    while (!queue_empty(queue)) {
        PuzzleState* current = (PuzzleState*)queue_get(queue);
        queue_remove(queue);

        if (current->board == goal) {
            for (const auto &step : current->path) {
                cout << step << "\n";
            }
            delete current;
            queue_delete(queue);
            return;
        }

        int row = current->zero_pos / 3;
        int col = current->zero_pos % 3;

        for (int move : moves) {
            int new_pos = current->zero_pos + move;
            int new_row = new_pos / 3;
            int new_col = new_pos % 3;

            if (new_pos >= 0 && new_pos < 9 && abs(new_row - row) + abs(new_col - col) == 1) {
                string new_board = current->board;
                swap(new_board[current->zero_pos], new_board[new_pos]);

                if (visited.find(new_board) == visited.end()) {
                    vector<string> new_path = current->path;
                    new_path.push_back(new_board);
                    PuzzleState* new_state = new PuzzleState(new_board, new_pos, new_path);
                    queue_insert(queue, (Data)new_state);
                    visited.insert(new_board);
                }
            } else {
                cout << "Invalid move, skipping." << endl;
            }
        }
        delete current;
    }
    queue_delete(queue);
}

int main() {
    string input;
    cin >> input;
    solvePuzzle(input);
    return 0;
}
