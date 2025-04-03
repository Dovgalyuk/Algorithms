#include <iostream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

#include "queue.h"

using namespace std;

long long to_long(const vector<int>& board) {
    long long result = 0;
    for (int i = 0; i < 9; ++i) {
        result = result * 10 + board[i];
    }
    return result;
}

vector<int> to_board(long long number) {
    vector<int> board(9);
    for (int i = 8; i >= 0; --i) {
        board[i] = number % 10;
        number /= 10;
    }
    return board;
}

vector<long long> get_neighbors(const vector<int>& board) {
    vector<long long> neighbors;
    int zero_pos = std::find(board.begin(), board.end(), 0) - board.begin();
    int row = zero_pos / 3;
    int col = zero_pos % 3;

    vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (auto& dir : directions) {
        int new_row = row + dir.first;
        int new_col = col + dir.second;

        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            int new_zero_pos = new_row * 3 + new_col;
            vector<int> new_board = board;
            swap(new_board[zero_pos], new_board[new_zero_pos]);
            neighbors.push_back(to_long(new_board));
        }
    }
    return neighbors;
}

void print_board(const vector<int>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve_puzzle(vector<int> start) {
    vector<int> goal_board = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    long long goal = to_long(goal_board);

    long long start_long = to_long(start);
    if (start_long == goal) {
        print_board(start);
        return;
    }

    Queue* q = queue_create();
    unordered_set<long long> visited;

    queue_insert(q, start_long);
    visited.insert(start_long);

    unordered_map<long long, long long> parent_map;
    parent_map[start_long] = -1;

    while (!queue_empty(q)) {
        long long current_board_long = queue_get(q);
        queue_remove(q);
        vector<int> current_board = to_board(current_board_long);

        for (long long neighbor : get_neighbors(current_board)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue_insert(q, neighbor);
                parent_map[neighbor] = current_board_long;

                if (neighbor == goal) {
                    vector<long long> solution_path;
                    for (long long state = goal; state != -1; state = parent_map[state]) {
                        solution_path.push_back(state);
                    }

                    for (auto it = solution_path.rbegin(); it != solution_path.rend(); ++it) {
                        print_board(to_board(*it));
                    }
                    return;
                }
            }
        }
    }

    cout << "No solution has been found." << endl;
    queue_delete(q);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: specify the input data file.\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error: couldn't open the file %s.\n", argv[1]);
        return 1;
    }

    char start_str[10];
    if (fscanf(input, "%9s", start_str) != 1) {
        printf("Error: data could not be read from the file.\n");
        fclose(input);
        return 1;
    }
    fclose(input);

    if (strlen(start_str) != 9) {
        cout << "Error: The status must contain 9 characters." << endl;
        return 1;
    }

    vector<int> start(9);
    for (int i = 0; i < 9; ++i) {
        start[i] = start_str[i] - '0';
    }

    solve_puzzle(start);

    return 0;
}
