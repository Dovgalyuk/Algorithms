#include <iostream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

#include "queue.h"

using namespace std;

typedef vector<int> Board;
typedef long long BoardState;

BoardState to_long(const Board& board) {
    BoardState result = 0;
    for (int i = 0; i < 9; ++i) {
        result = result * 10 + board[i];
    }
    return result;
}

Board to_board(BoardState number) {
    Board board(9);
    for (int i = 8; i >= 0; --i) {
        board[i] = number % 10;
        number /= 10;
    }
    return board;
}

vector<BoardState> get_neighbors(const Board& board) {
    vector<BoardState> neighbors;
    int zero_pos = find(board.begin(), board.end(), 0) - board.begin();
    int row = zero_pos / 3;
    int col = zero_pos % 3;

    vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    for (auto& dir : directions) {
        int new_row = row + dir.first;
        int new_col = col + dir.second;

        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            int new_zero_pos = new_row * 3 + new_col;
            Board new_board = board;
            swap(new_board[zero_pos], new_board[new_zero_pos]);
            neighbors.push_back(to_long(new_board));
        }
    }
    return neighbors;
}

void print_board(const Board& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve_puzzle(const Board& start) {
    Board goal_board = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    BoardState goal = to_long(goal_board);
    BoardState start_long = to_long(start);

    if (start_long == goal) {
        print_board(start);
        return;
    }

    Queue* q = queue_create();
    unordered_map<BoardState, BoardState> parent_map;
    parent_map[start_long] = -1;

    queue_insert(q, start_long);

    BoardState found_goal = -1;
    while (!queue_empty(q)) {
        BoardState current_board_long = queue_get(q);
        queue_remove(q);
        Board current_board = to_board(current_board_long);

        for (BoardState neighbor : get_neighbors(current_board)) {
            if (parent_map.find(neighbor) == parent_map.end()) {
                queue_insert(q, neighbor);
                parent_map[neighbor] = current_board_long;

                if (neighbor == goal) {
                    found_goal = neighbor;
                    break;
                }
            }
        }
        if (found_goal != -1) break;
    }

    queue_delete(q);

    if (found_goal != -1) {
        vector<BoardState> solution_path;
        for (BoardState state = found_goal; state != -1; state = parent_map[state]) {
            solution_path.push_back(state);
        }

        reverse(solution_path.begin(), solution_path.end());

        for (const auto& state : solution_path) {
            print_board(to_board(state));
        }
    } else {
        cout << "No solution has been found." << endl;
    }
}


Board read_input(const string& filename) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw runtime_error("Couldn't open the file " + filename);
    }

    string start_str;
    input_file >> start_str;

    if (start_str.length() != 9) {
        throw runtime_error("The input must contain 9 characters.");
    }

    Board start(9);
    for (int i = 0; i < 9; ++i) {
        if (!isdigit(start_str[i])) {
            throw runtime_error("Invalid character in input.");
        }
        start[i] = start_str[i] - '0';
    }

    input_file.close();
    return start;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Error: specify the input data file." << endl;
        return 1;
    }

    string filename = argv[1];
    Board start;
    
    try {
        start = read_input(filename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    try {
        solve_puzzle(start);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}