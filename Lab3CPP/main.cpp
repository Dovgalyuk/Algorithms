#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

using namespace std;

// Чтение лабиринта из файла
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

// Вывод лабиринта в шестиугольных ячейках с корректными нижними границами
void print_hex_maze(const vector<string>& grid) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    for (int r = 0; r < rows; ++r) {
        string shift(r * 3, ' ');

        // Верхняя граница только для первой строки
        if (r == 0) {
            cout << shift;
            for (int c = 0; c < cols; ++c) cout << " / \\";
            cout << "\n";
        }

        // Содержимое ячеек
        cout << shift;
        for (int c = 0; c < cols; ++c) {
            cout << "|" << grid[r][c] << "|";
            if (c != cols - 1) cout << " ";
        }
        cout << "\n";

        // Нижняя граница каждой строки
        cout << shift;
        for (int c = 0; c < cols; ++c) {
            cout << " \\ /";
            if (c != cols - 1) cout << " ";
        }

        // Промежуточные строки (кроме последней) завершаем дополнительным backslash
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

    int sr = -1, sc = -1, er = -1, ec = -1;
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') { sr = static_cast<int>(r); sc = static_cast<int>(c); }
            if (grid[r][c] == 'E') { er = static_cast<int>(r); ec = static_cast<int>(c); }
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
        prev.set(static_cast<int>(i), -1);

    auto inside = [&](int r, int c) { return r >= 0 && r < static_cast<int>(rows) && c >= 0 && c < static_cast<int>(cols); };
    auto free_cell = [&](int r, int c) { return grid[r][c] != '#'; };

    Queue q;
    int start = sr * static_cast<int>(cols) + sc;
    prev.set(start, start);
    q.insert(start);

    auto add = [&](int r, int c, int dr, int dc, int cur) {
        int nr = r + dr, nc = c + dc;
        if (!inside(nr, nc)) return;
        if (!free_cell(nr, nc)) return;

        int id = nr * static_cast<int>(cols) + nc;
        if (prev.get(id) != -1) return;

        prev.set(id, cur);
        q.insert(id);
        };

    bool found = false;

    while (!q.empty()) {
        int cur = q.get();
        q.remove();

        int r = cur / static_cast<int>(cols);
        int c = cur % static_cast<int>(cols);

        if (r == er && c == ec) {
            found = true;
            break;
        }

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

    // Восстановление пути и пометка 'x'
    int cur = er * static_cast<int>(cols) + ec;
    while (true) {
        int p = prev.get(cur);
        if (p == cur) break;

        if (cur != start && cur != (er * static_cast<int>(cols) + ec)) {
            int r = cur / static_cast<int>(cols);
            int c = cur % static_cast<int>(cols);
            grid[r][c] = 'x';
        }

        cur = p;
    }

    // Вывод лабиринта в шестиугольных ячейках
    print_hex_maze(grid);

    return 0;
}