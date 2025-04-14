#include <iostream>
#include <vector>
#include <fstream>
#include "queue.h"

using namespace std;

struct Point {
    int row, col;
    bool operator!=(const Point& other) const {
        return row != other.row || col != other.col;
    }
};

typedef vector<vector<char>> Labyrinth;

int pointToData(Point p, size_t cols) {
    return p.row * cols + p.col;
}

Point dataToPoint(int d, size_t cols) {
    return { static_cast<int>(d / cols), static_cast<int>(d % cols) };
}

int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void printPath(Labyrinth& lbr, Point start, Point end, const vector<vector<Point>>& parents, ostream& out) {
    Point p = end;
    while (p.row != -1) {
        if (p != start && p != end) {
            lbr[p.row][p.col] = 'x';
        }
        p = parents[p.row][p.col];
    }
    lbr[start.row][start.col] = 'X';
    lbr[end.row][end.col] = 'Y';

    for (const auto& row : lbr) {
        out << string(row.begin(), row.end()) << endl;
    }
}

void search(Labyrinth& lbr, Point start, Point end, ostream& out) {
    Queue* queue = queue_create();
    queue_insert(queue, pointToData(start, lbr[0].size()));
    vector<vector<bool>> visited(lbr.size(), vector<bool>(lbr[0].size(), false));
    visited[start.row][start.col] = true;
    vector<vector<Point>> parents(lbr.size(), vector<Point>(lbr[0].size(), { -1, -1 }));

    bool found = false;
    while (!queue_empty(queue)) {
        int current_data = queue_get(queue);
        queue_remove(queue);
        Point current = dataToPoint(current_data, lbr[0].size());

        if (current.row == end.row && current.col == end.col) {
            found = true;
            break;
        }

        for (auto& move : moves) {
            int new_row = current.row + move[0];
            int new_col = current.col + move[1];
            if (new_row >= 0 && static_cast<size_t>(new_row) < lbr.size() &&
                new_col >= 0 && static_cast<size_t>(new_col) < lbr[0].size() &&
                (lbr[new_row][new_col] == '.' || lbr[new_row][new_col] == 'Y') &&
                !visited[new_row][new_col]) {
                visited[new_row][new_col] = true;
                parents[new_row][new_col] = current;
                queue_insert(queue, pointToData({ new_row, new_col }, lbr[0].size()));
            }
        }
    }

    if (found) {
        printPath(lbr, start, end, parents, out);
    } else {
        out << "IMPOSSIBLE\n";
    }

    queue_delete(queue);
}

void readLabyrinth(istream& in, Labyrinth& lbr, Point& start, Point& end) {
    string line;
    while (getline(in, line)) {
        if (line.empty()) break;
        vector<char> row(line.begin(), line.end());
        lbr.push_back(row);
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i] == 'X') start = { static_cast<int>(lbr.size() - 1), static_cast<int>(i) };
            if (row[i] == 'Y') end = { static_cast<int>(lbr.size() - 1), static_cast<int>(i) };
        }
    }
}

int main(int argc, char* argv[]) {
    Labyrinth lbr;
    Point start = { -1, -1 };
    Point end = { -1, -1 };

    if (argc > 1) {
        ifstream inputFile(argv[1]);
        if (inputFile) {
            readLabyrinth(inputFile, lbr, start, end);
        } else {
            cerr << "Couldn't open the file " << argv[1] << endl;
        }
    }

    if (lbr.empty()) {
        cout << "Enter the maze:" << endl;
        readLabyrinth(cin, lbr, start, end);
    }

    search(lbr, start, end, cout);
    return 0;
}
