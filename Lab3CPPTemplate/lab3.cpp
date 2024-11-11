#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "queue.h"

// Field size N x M
#define N 8
#define M 8

using namespace std;

// Structure to represent the knight's position with the number of steps to be taken 
// and with a reference to previous positions to retrace the path traveled by the knight
struct Position {
    int x, y, step;

    Position *prev;
};

// All possible directions of the knight's movement
const vector<pair<int, int>> knight_moves = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

int* read_grid(const char* file, vector<vector<char>>& grid);
void init_board(const vector<vector<char>>& grid, vector<vector<int>>& board);
void print_grid(const vector<vector<char>>& grid);
bool is_valid(int x, int y, const vector<vector<char>>& grid);
void retrace_path(vector<vector<char>>& grid, Position* current);
void find_shortest_path(vector<vector<char>>& grid, int start_x, int start_y, int end_x, int end_y);

int main(int argc, char** argv) {
    vector<vector<char>> grid(N, vector<char>('.'));

    int* coors = read_grid(argv[1], grid);
    int start_x = coors[0], start_y = coors[1],
        end_x = coors[2], end_y = coors[3];

    find_shortest_path(grid, start_x, start_y, end_x, end_y);
    
    delete[] coors;
    
    return 0;
}

int* read_grid(const char* file, vector<vector<char>>& grid) {
    ifstream in(file);
    int* coors = new int[4];

    if (in.is_open()) {
        char ch = '\n';

        // symbolic reading
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                in.get(ch);

                if (ch == 'K') {
                    coors[0] = j;
                    coors[1] = i;
                }
                else if (ch == 'E') {
                    coors[2] = j;
                    coors[3] = i;
                }

                grid[i][j] = ch;
            }
            // reading the '\n' symbol
            in.get(ch);
        }
    }
    else {
        throw invalid_argument("Failed to read file");
    }

    in.close();

    return coors;
}

void init_board(const vector<vector<char>>& grid, vector<vector<int>>& board) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '#') {
                board[i][j] = -1; // barriers
            }
            else {
                board[i][j] = 0; // free cells
            }
        }
    }
}

void print_grid(const vector<vector<char>>& grid) {
    for (auto& row : grid) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

bool is_valid(int x, int y, const vector<vector<char>>& grid) {
    return (x >= 0 && x < N && y >= 0 && y < M && grid[y][x] != '#');
}

void retrace_path(vector<vector<char>>& grid, Position* current) {
    Position* position = current;

    // Drawing the shortest path on the original grid
    while (position != nullptr) {
        grid[position->y][position->x] = (char)(position->step + '0');
        position = position->prev;
    }

    print_grid(grid);
}

void find_shortest_path(vector<vector<char>>& grid, int start_x, int start_y, int end_x, int end_y) {
    vector<vector<int>> board(M, vector<int>(N, 0));
    vector<Position*> positions;
    bool is_found = false;

    init_board(grid, board);

    Queue<Position*> q;
    Position* current = new Position({ start_x, start_y, 0, nullptr });
    q.insert(current);
    positions.push_back(current);

    board[start_y][start_x] = 0;

    while (!q.empty() && !is_found) {
        current = q.get();
        q.remove();

        // If we have reached the target position
        if (current->x == end_x && current->y == end_y) {
            is_found = true;
            break;
        }

        // Check all possible knight moves
        for (const auto& move : knight_moves) {
            int new_x = current->x + move.first;
            int new_y = current->y + move.second;

            if (is_valid(new_x, new_y, grid) && board[new_y][new_x] == 0) {
                board[new_y][new_x] = current->step + 1; // Numbering the cell
                Position* new_position = new Position({ new_x, new_y, current->step + 1, current });
                q.insert(new_position);
                positions.push_back(new_position); // Save the pointer to the new position to delete this structure later 
            }
        }
    }

    if (is_found) retrace_path(grid, current);
    else cout << "No path found!" << endl; // If the path is not found

    // Free the memory for all found positions
    for (Position* pos : positions) {
        delete pos;
    }

    // Clear the queue
    while (!q.empty()) {
        q.remove();
    }
}