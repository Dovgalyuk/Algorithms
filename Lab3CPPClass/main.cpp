#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "queue.h"

using namespace std;

struct Maze {
    vector<string> grid;
    int rows = 0;
    int cols = 0;
    int start = -1;
    int finish = -1;
};

struct SearchFront {
    Queue queue;
    vector<int> dist;
    vector<int> parent;
    int current_depth = 0;
    int queue_size = 0;
};

struct Direction {
    constexpr Direction(int row_step, int col_step) : d_row(row_step), d_col(col_step) {}

    int d_row;
    int d_col;
};

bool ReadMaze(istream& input, Maze& maze) {
    string line;
    while (getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        if (maze.cols == 0) {
            maze.cols = static_cast<int>(line.size());
        } else if (static_cast<int>(line.size()) != maze.cols) {
            return false;
        }
        maze.grid.push_back(std::move(line));
    }

    maze.rows = static_cast<int>(maze.grid.size());
    return maze.rows > 0 && maze.cols > 0;
}

bool FindEndpoints(Maze& maze) {
    for (int row = 0; row < maze.rows; ++row) {
        const string& line = maze.grid[static_cast<size_t>(row)];
        for (int col = 0; col < maze.cols; ++col) {
            const char cell = line[static_cast<size_t>(col)];
            if (cell == 'X') {
                maze.start = row * maze.cols + col;
            } else if (cell == 'Y') {
                maze.finish = row * maze.cols + col;
            }
        }
    }
    return maze.start != -1 && maze.finish != -1;
}

bool IsWalkable(const Maze& maze, int row, int col) {
    if (row < 0 || row >= maze.rows || col < 0 || col >= maze.cols) {
        return false;
    }
    return maze.grid[static_cast<size_t>(row)][static_cast<size_t>(col)] != '#';
}

void InitFront(SearchFront& front, int total_cells, int origin) {
    const size_t cell_count = static_cast<size_t>(total_cells);
    front.dist.assign(cell_count, -1);
    front.parent.assign(cell_count, -1);
    front.dist[static_cast<size_t>(origin)] = 0;
    front.queue.insert(origin);
    front.queue_size = 1;
    front.current_depth = 0;
}

int ExpandLevel(const Maze& maze, SearchFront& active, const SearchFront& other) {
    static constexpr Direction kDirections[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const int target_depth = active.current_depth;

    while (!active.queue.empty() && active.dist[static_cast<size_t>(active.queue.get())] == target_depth) {
        const int current = active.queue.get();
        active.queue.remove();
        --active.queue_size;

        const int row = current / maze.cols;
        const int col = current % maze.cols;

        for (const Direction& dir : kDirections) {
            const int next_row = row + dir.d_row;
            const int next_col = col + dir.d_col;
            if (!IsWalkable(maze, next_row, next_col)) {
                continue;
            }

            const int next_cell = next_row * maze.cols + next_col;
            const size_t next_idx = static_cast<size_t>(next_cell);
            if (active.dist[next_idx] != -1) {
                continue;
            }

            active.dist[next_idx] = target_depth + 1;
            active.parent[next_idx] = current;
            if (other.dist[next_idx] != -1) {
                return next_cell;
            }
            active.queue.insert(next_cell);
            ++active.queue_size;
        }
    }

    ++active.current_depth;
    return -1;
}

void MarkPath(Maze& maze, const vector<int>& parent, int meet) {
    int current = meet;
    while (current != -1) {
        if (current != maze.start && current != maze.finish) {
            const size_t row = static_cast<size_t>(current / maze.cols);
            const size_t col = static_cast<size_t>(current % maze.cols);
            maze.grid[row][col] = 'x';
        }
        current = parent[static_cast<size_t>(current)];
    }
}

bool FindShortestPath(Maze& maze) {
    const int total_cells = maze.rows * maze.cols;

    SearchFront from_start;
    InitFront(from_start, total_cells, maze.start);

    SearchFront from_finish;
    InitFront(from_finish, total_cells, maze.finish);

    while (!from_start.queue.empty() && !from_finish.queue.empty()) {
        const bool expand_start = from_start.queue_size <= from_finish.queue_size;
        const int meet = expand_start ? ExpandLevel(maze, from_start, from_finish) : ExpandLevel(maze, from_finish, from_start);
        if (meet != -1) {
            MarkPath(maze, from_start.parent, meet);
            MarkPath(maze, from_finish.parent, meet);
            return true;
        }
    }

    return false;
}

void PrintMaze(const Maze& maze) {
    for (const string& line : maze.grid) {
        cout << line << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return EXIT_FAILURE;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Unable to open input file: " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    Maze maze;
    if (!ReadMaze(input, maze) || !FindEndpoints(maze)) {
        cout << "IMPOSSIBLE\n";
        return EXIT_SUCCESS;
    }

    if (FindShortestPath(maze)) {
        PrintMaze(maze);
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return EXIT_SUCCESS;
}