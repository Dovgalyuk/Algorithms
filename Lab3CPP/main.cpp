#include <iostream>
#include <vector>
#include "queue.h"

using namespace std;

struct Point {
    int row, col;
};

int pointToData(Point p, size_t cols) {
    return p.row * cols + p.col;
}

Point dataToPoint(int d, size_t cols) {
    return { static_cast<int>(d / cols), static_cast<int>(d % cols) };
}

int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void search(vector<vector<char>>& lbr, Point start, Point end, ostream& out) {
    Queue* queue = queue_create();
    queue_insert(queue, pointToData(start, lbr[0].size()));
    vector<vector<bool>> visited(lbr.size(), vector<bool>(lbr[0].size(), false));
    visited[start.row][start.col] = true;
    vector<vector<Point>> parents(lbr.size(), vector<Point>(lbr[0].size(), { -1, -1 }));

    while (!queue_empty(queue)) {
        int current_data = queue_get(queue);
        queue_remove(queue);
        Point current = dataToPoint(current_data, lbr[0].size());

        if (current.row == end.row && current.col == end.col) {
            Point p = end;
            while (p.row != -1) {
                lbr[p.row][p.col] = 'x';
                p = parents[p.row][p.col];
            }
            lbr[start.row][start.col] = 'X';
            lbr[end.row][end.col] = 'Y';
            for (const auto& row : lbr) out << string(row.begin(), row.end()) << endl;
            queue_delete(queue);
            return;
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
    out << "IMPOSSIBLE\n";
    queue_delete(queue);
}

int main() {
    vector<vector<char>> lbr;
    Point start = { -1, -1 }; 
    Point end = { -1, -1 }; 
    string line;

    while (getline(cin, line) && !line.empty()) {
        vector<char> row(line.begin(), line.end());
        lbr.push_back(row);
        for (size_t i = 0; i < row.size(); i++) {
            if (row[i] == 'X') start = { static_cast<int>(lbr.size() - 1), static_cast<int>(i) };
            if (row[i] == 'Y') end = { static_cast<int>(lbr.size() - 1), static_cast<int>(i) };
        }
    }

    if (start.row == -1 || end.row == -1) {
        cout << "Start or end point not found!" << endl;
        return 1; 
    }

    search(lbr, start, end, cout);
    return 0;
}
