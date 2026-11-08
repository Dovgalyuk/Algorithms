#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

struct Cell {
    char type;
    int row, column;
};

struct Maze {
    vector<string> lines;
    vector<Cell> cells;
    vector<vector<int>> ids;
    vector<vector<int>> adjacent;
    vector<int> offset;
    int start = -1;
    int finish = -1;
};

struct Search {
    Queue* queue;
    vector<int> distance;
    vector<int> previous;
};

bool create_cells(Maze& maze) {
    int start_count = 0, finish_count = 0, max_width = 0;
    if (maze.lines.empty() ||
        maze.lines.size() > static_cast<size_t>(numeric_limits<int>::max()))
        return false;

    maze.ids.resize(maze.lines.size());
    for (size_t r = 0; r < maze.lines.size(); ++r) {
        if (maze.lines[r].empty() ||
            maze.lines[r].size() > static_cast<size_t>(numeric_limits<int>::max() / 2))
            return false;
        max_width = max(max_width, static_cast<int>(maze.lines[r].size()));
        for (size_t c = 0; c < maze.lines[r].size(); ++c) {
            char type = maze.lines[r][c];
            if ((type != '.' && type != '#' && type != 'S' && type != 'E') ||
                maze.cells.size() >= static_cast<size_t>(numeric_limits<int>::max()))
                return false;
            int id = static_cast<int>(maze.cells.size());
            if (type == 'S') { maze.start = id; ++start_count; }
            if (type == 'E') { maze.finish = id; ++finish_count; }
            maze.ids[r].push_back(id);
            maze.cells.push_back({type, static_cast<int>(r), static_cast<int>(c)});
        }
    }
    maze.offset.resize(maze.lines.size());
    for (size_t r = 0; r < maze.lines.size(); ++r) {
        maze.offset[r] = max_width - static_cast<int>(maze.lines[r].size());
        if (r > 0 && (maze.offset[r] - maze.offset[r - 1]) % 2 == 0)
            ++maze.offset[r];
    }
    return start_count == 1 && finish_count == 1;
}

bool read_maze(istream& input, Maze& maze) {
    string line;
    while (getline(input, line)) {
        size_t end = line.find_last_not_of(" \t\r");
        line.erase(end == string::npos ? 0 : end + 1);
        size_t start = line.find_first_not_of(" \t");
        if (start != string::npos) line.erase(0, start);
        maze.lines.push_back(line);
    }
    while (!maze.lines.empty() && maze.lines.back().empty())
        maze.lines.pop_back();
    return create_cells(maze);
}

void add_neighbor(Maze& maze, int from, int row, int column) {
    if (row < 0 || row >= static_cast<int>(maze.ids.size()) ||
        column < 0 || column >= static_cast<int>(maze.ids[row].size()))
        return;
    int next = maze.ids[row][column];
    if (maze.cells[next].type != '#')
        maze.adjacent[from].push_back(next);
}

void build_graph(Maze& maze) {
    maze.adjacent.resize(maze.cells.size());
    for (size_t i = 0; i < maze.cells.size(); ++i) {
        if (maze.cells[i].type == '#') continue;
        int row = maze.cells[i].row, column = maze.cells[i].column;
        int id = static_cast<int>(i);
        add_neighbor(maze, id, row, column - 1);
        add_neighbor(maze, id, row, column + 1);
        for (int next_row : {row - 1, row + 1}) {
            if (next_row < 0 || next_row >= static_cast<int>(maze.ids.size())) continue;
            int left = (2 * column + maze.offset[row] - maze.offset[next_row] - 1) / 2;
            add_neighbor(maze, id, next_row, left);
            add_neighbor(maze, id, next_row, left + 1);
        }
    }
}

void check_meeting(int cell, const Search& search, const Search& other,
                   int& meeting, long long& best_distance) {
    if (other.distance[cell] == -1) return;
    long long total = static_cast<long long>(search.distance[cell]) + other.distance[cell];
    if (total < best_distance) {
        best_distance = total;
        meeting = cell;
    }
}

void expand_layer(const Maze& maze, Search& search, const Search& other,
                  int& meeting, long long& best_distance) {
    int level = search.distance[queue_get(search.queue)];
    while (!queue_empty(search.queue) &&
           search.distance[queue_get(search.queue)] == level) {
        int current = queue_get(search.queue);
        queue_remove(search.queue);
        check_meeting(current, search, other, meeting, best_distance);
        for (int next : maze.adjacent[current]) {
            if (search.distance[next] != -1) continue;
            search.distance[next] = search.distance[current] + 1;
            search.previous[next] = current;
            queue_insert(search.queue, next);
            check_meeting(next, search, other, meeting, best_distance);
        }
    }
}

bool find_path(Maze& maze) {
    Search forward = {queue_create(), vector<int>(maze.cells.size(), -1),
                      vector<int>(maze.cells.size(), -1)};
    Search backward = {queue_create(), vector<int>(maze.cells.size(), -1),
                       vector<int>(maze.cells.size(), -1)};
    queue_insert(forward.queue, maze.start);
    queue_insert(backward.queue, maze.finish);
    forward.distance[maze.start] = backward.distance[maze.finish] = 0;
    int meeting = -1;
    long long best_distance = numeric_limits<long long>::max();

    while (!queue_empty(forward.queue) && !queue_empty(backward.queue) && meeting == -1) {
        expand_layer(maze, forward, backward, meeting, best_distance);
        expand_layer(maze, backward, forward, meeting, best_distance);
    }
    queue_delete(forward.queue);
    queue_delete(backward.queue);
    if (meeting == -1) return false;

    for (int cell = meeting; cell != maze.start; cell = forward.previous[cell])
        if (cell != maze.finish) maze.cells[cell].type = 'x';
    for (int cell = meeting; cell != maze.finish; cell = backward.previous[cell])
        if (cell != maze.start) maze.cells[cell].type = 'x';
    return true;
}

void print_border(const Maze& maze, size_t row, bool top) {
    cout << string(2 * static_cast<size_t>(maze.offset[row]) + 2, ' ');
    for (size_t c = 0; c < maze.lines[row].size(); ++c)
        cout << (top ? " / \\" : " \\ /");
    cout << '\n';
}

void print_maze(const Maze& maze) {
    print_border(maze, 0, true);
    for (size_t r = 0; r < maze.lines.size(); ++r) {
        cout << string(2 * static_cast<size_t>(maze.offset[r]) + 2, ' ');
        for (int id : maze.ids[r]) cout << "| " << maze.cells[id].type << ' ';
        cout << "|\n";
        if (r + 1 < maze.lines.size() && maze.offset[r + 1] < maze.offset[r])
            print_border(maze, r + 1, true);
        else
            print_border(maze, r, false);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2) return 1;
    ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
        if (!file) {
            cerr << "Cannot open input file\n";
            return 1;
        }
    }
    istream& input = argc == 2 ? file : cin;
    Maze maze;
    if (!read_maze(input, maze)) {
        cout << "No path\n";
        return 0;
    }
    build_graph(maze);
    if (find_path(maze))
        print_maze(maze);
    else
        cout << "No path\n";
    return 0;
}
