#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

using namespace std;
typedef int Coord;

vector<string> read_input_file(const string& filename) {
    ifstream in(filename);
    if (!in.is_open())
        throw runtime_error("Cannot open file: " + filename);

    vector<string> lines;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty())
            lines.push_back(line);
    }
    return lines;
}

void print_hex_maze(const vector<string>& grid) {
    Coord rows = static_cast<Coord>(grid.size());
    Coord cols = static_cast<Coord>(grid[0].size());

    for (Coord r = 0; r < rows; ++r) {
        string shift(r * 3, ' ');

        if (r == 0) {
            cout << shift;
            for (Coord c = 0; c < cols; ++c) cout << " / \\";
            cout << "\n";
        }

        cout << shift;
        for (Coord c = 0; c < cols; ++c) {
            cout << "|" << grid[r][c] << "|";
            if (c != cols - 1) cout << " ";
        }
        cout << "\n";

        cout << shift;
        for (Coord c = 0; c < cols; ++c) {
            cout << " \\ /";
            if (c != cols - 1) cout << " ";
        }

        if (r != rows - 1) cout << " \\";
        cout << "\n";
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    vector<string> grid;
    try {
        grid = read_input_file(argv[1]);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    if (grid.empty()) {
        cerr << "Input file is empty" << endl;
        return 1;
    }

    size_t rows = grid.size();
    size_t cols = grid[0].size();

    for (const auto& row : grid) {
        if (row.size() != cols) {
            cerr << "All lines must have equal length" << endl;
            return 1;
        }
    }

    Coord sr = -1, sc = -1, er = -1, ec = -1;
    for (Coord r = 0; r < static_cast<Coord>(rows); r++) {
        for (Coord c = 0; c < static_cast<Coord>(cols); c++) {
            if (grid[r][c] == 'S') { sr = r; sc = c; }
            if (grid[r][c] == 'E') { er = r; ec = c; }
        }
    }

    if (sr == -1 || er == -1) {
        cerr << "Start (S) or End (E) not found" << endl;
        return 1;
    }

    size_t total = rows * cols;

    Vector prev;
    prev.resize(total);
    for (size_t i = 0; i < total; i++)
        prev.set(static_cast<Coord>(i), -1);

    Queue q;
    Coord start = sr * static_cast<Coord>(cols) + sc;
    prev.set(start, start);
    q.insert(start);

    auto add = [&](Coord r, Coord c, Coord dr, Coord dc, Coord cur) {
        Coord nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= static_cast<Coord>(rows) ||
            nc < 0 || nc >= static_cast<Coord>(cols)) return;
        if (grid[nr][nc] == '#') return;

        Coord id = nr * static_cast<int>(cols) + nc;
        if (prev.get(id) != -1) return;

        prev.set(id, cur);
        q.insert(id);
        };

    bool found = false;

    while (!q.empty()) {
        Coord cur = q.get();
        q.remove();

        Coord r = cur / static_cast<Coord>(cols);
        Coord c = cur % static_cast<Coord>(cols);

        if (r == er && c == ec) {
            found = true;
            break;
        }
        /*This is necessary for correct operation with a hexagonal grid. 
        In such a grid, even and odd rows have different neighboring positions due to the checkerboard pattern of the cells.
        Without this check, the algorithm will search for a path in a square grid, which will produce an incorrect result for the given maze format.*/
        if ((r % 2) == 0) {
            add(r, c, -1, 0, cur);
            add(r, c, -1, 1, cur);
            add(r, c, 0, -1, cur);
            add(r, c, 0, 1, cur);
            add(r, c, 1, 0, cur);
            add(r, c, 1, 1, cur);
        }
        else {
            add(r, c, -1, -1, cur);
            add(r, c, -1, 0, cur);
            add(r, c, 0, -1, cur);
            add(r, c, 0, 1, cur);
            add(r, c, 1, -1, cur);
            add(r, c, 1, 0, cur);
        }
    }

    if (!found) {
        cout << "No path" << endl;
        return 0;
    }

    Coord cur = er * static_cast<Coord>(cols) + ec;
    while (true) {
        Coord p = prev.get(cur);
        if (p == cur) break;

        if (cur != start && cur != (er * static_cast<Coord>(cols) + ec)) {
            Coord r = cur / static_cast<Coord>(cols);
            Coord c = cur % static_cast<Coord>(cols);
            grid[r][c] = 'x';
        }

        cur = p;
    }

    print_hex_maze(grid);

    return 0;
}