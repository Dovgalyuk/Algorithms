#include <iostream>
#include <unordered_set>
#include <string>
#include "queue.h"
#include <unordered_map>

using namespace std;
using BoardState = std::string;

void print_board(const BoardState& board) {
    for (int i = 0; i < 9; ++i) {
        cout << board[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

bool is_goal(const BoardState& board) {
    return board == "123456780";
}

vector<BoardState> get_neighbors(const BoardState& board) {
    vector<BoardState> neighbors;
    int zero_pos = board.find('0');

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
    unordered_set<BoardState> visited;
    unordered_map<BoardState, BoardState> parent_map;

    queue_insert(queue, start);
    visited.insert(start);
    parent_map[start] = "";

    while (!queue_empty(queue)) {
        BoardState current_board = queue_get(queue);
        queue_remove(queue);

        if (is_goal(current_board)) {
            
            vector<BoardState> path;
            for (BoardState state = current_board; !state.empty(); state = parent_map[state]) {
                path.push_back(state);
            }
            
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                print_board(*it);
            }
            queue_delete(queue);
            return;
        }

        auto neighbors = get_neighbors(current_board);
        for (const BoardState& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent_map[neighbor] = current_board;
                queue_insert(queue, neighbor);
            }
        }
    }

    queue_delete(queue);
}

bool is_solvable(const BoardState& board) {
    int inversions = 0;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == '0') continue;
        for (int j = i + 1; j < 9; ++j) {
            if (board[j] != '0' && board[i] > board[j]) {
                ++inversions;
            }
        }
    }

    return (inversions % 2 == 0);
}

int main() {
    string input;
    cin >> input;

    if (input.length() != 9 || input.find_first_not_of("012345678") != string::npos) {
        return 1;
    }

    if (!is_solvable(input)) {
        return 1;
    }

    bfs(input);
    return 0;
}