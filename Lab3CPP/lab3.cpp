#include <iostream>
#include <unordered_set>
#include <string>
#include "queue.h"
#include <unordered_map>
#include <vector>

using namespace std;
using BoardState = std::vector<int>;

void print_board(const BoardState& board) {
    for (int i = 0; i < 9; ++i) {
        cout << board[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

bool is_goal(const BoardState& board) {
    return board == BoardState{1, 2, 3, 4, 5, 6, 7, 8, 0};
}

vector<BoardState> get_neighbors(const BoardState& board) {
    vector<BoardState> neighbors;
    int zero_pos = find(board.begin(), board.end(), 0) - board.begin();

    auto swap_positions = [](BoardState board, int i, int j) {
        swap(board[i], board[j]);
        return board;
    };

    int moves[] = {-3, 3, -1, 1};
    for (int move : moves) {
        int new_pos = zero_pos + move;

        if (new_pos >= 0 && new_pos < 9 &&
            ((move == -3 || move == 3) || (zero_pos / 3 == new_pos / 3))) {

            BoardState new_board = swap_positions(board, zero_pos, new_pos);
            neighbors.push_back(new_board);
        }
    }

    return neighbors;
}

void bfs(const BoardState& start) {
    Queue* queue = queue_create();
    unordered_set<string> visited;
    unordered_map<string, BoardState> parent_map;

    auto board_to_string = [](const BoardState& board) {
        string str;
        for (int num : board) {
            str += to_string(num);
        }
        return str;
    };

    string start_str = board_to_string(start);
    int start_index = 0;

    queue_insert(queue, start_index);
    visited.insert(start_str);
    parent_map[start_str] = BoardState();

    while (!queue_empty(queue)) {
        int current_index = queue_get(queue);
        queue_remove(queue);

        BoardState current_board = start;

        if (is_goal(current_board)) {
            vector<BoardState> path;
            string current_board_str = board_to_string(current_board);
            for (string state = current_board_str; !state.empty(); state = board_to_string(parent_map[state])) {
                BoardState board_state;
                for (char c : state) {
                    board_state.push_back(c - '0');
                }
                path.push_back(board_state);
            }

            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                print_board(*it);
            }
            queue_delete(queue);
            return;
        }

        auto neighbors = get_neighbors(current_board);
        for (const BoardState& neighbor : neighbors) {
            string neighbor_str = board_to_string(neighbor);
            if (visited.find(neighbor_str) == visited.end()) {
                visited.insert(neighbor_str);
                parent_map[neighbor_str] = current_board;
                int neighbor_index = 0;
                queue_insert(queue, neighbor_index);
            }
        }
    }

    queue_delete(queue);
}


bool is_solvable(const BoardState& board) {
    int inversions = 0;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 0) continue;
        for (int j = i + 1; j < 9; ++j) {
            if (board[j] != 0 && board[i] > board[j]) {
                ++inversions;
            }
        }
    }

    return (inversions % 2 == 0);
}

int main() {
    BoardState input(9);
    for (int i = 0; i < 9; ++i) {
        cin >> input[i];
    }

    if (!is_solvable(input)) {
        return 1;
    }

    bfs(input);
    return 0;
}
