#include <iostream>
#include <vector>
#include <cstring>
#include "queue.h"
#include "list.h"
#include <string>

using namespace std;

int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

struct Point {
    int row, col;
};

Data pointToData(Point p, size_t cols) {
    return static_cast<Data>(p.row) * static_cast<Data>(cols) + static_cast<Data>(p.col);
}

Point dataToPoint(Data d, size_t cols) {
    Point p;
    p.row = d / static_cast<Data>(cols);
    p.col = d % cols;
    return p;
}

void search(vector<vector<char>>& lbr, size_t rows, size_t cols, Point start, Point end, ostream& out) {
    Queue* queue = queue_create();
    Data start_data = pointToData(start, cols);
    lbr[start.row][start.col] = '.'; 
    queue_insert(queue, start_data); 

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[start.row][start.col] = true; 

    vector<vector<Point>> parents(rows, vector<Point>(cols, { -1, -1 }));

    bool path_found = false;

    while (!queue_empty(queue)) {
        Data current_data = queue_get(queue);
        queue_remove(queue);

        Point current = dataToPoint(current_data, cols);

        if (current.row == end.row && current.col == end.col) {
            path_found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int new_row = current.row + moves[i][0];
            int new_col = current.col + moves[i][1];

            if (new_row >= 0 && static_cast<size_t>(new_row) < rows &&
                new_col >= 0 && static_cast<size_t>(new_col) < cols &&
                (lbr[new_row][new_col] == '.' || lbr[new_row][new_col] == 'Y') && 
                !visited[new_row][new_col]) {

                visited[new_row][new_col] = true;
                parents[new_row][new_col] = current;
                Data new_data = pointToData({ new_row, new_col }, cols);
                queue_insert(queue, new_data); 
            }
        }
    }


    if (!path_found) {
        out << "IMPOSSIBLE\n";
    } else {
        Point p = end;
        while (p.row != -1 && p.col != -1) {
            if (lbr[p.row][p.col] == '.') {
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

    queue_delete(queue);
}

int main() {
    vector<vector<char>> lbr;
    Point start = { -1, -1 };
    Point end = { -1, -1 };
    size_t rows = 0;

    cout << "Enter the maze: " << endl;

    string line;
    while (getline(cin, line) && !line.empty()) {
        vector<char> row(line.begin(), line.end());
        lbr.push_back(row);

        for (size_t i = 0; i < row.size(); i++) {
            if (row[i] == 'X') {
                start = { static_cast<int>(rows), static_cast<int>(i) };
                lbr[rows][i] = '.'; 
            }
            if (row[i] == 'Y') {
                end = { static_cast<int>(rows), static_cast<int>(i) };
            }
        }
        rows++;
    }

    if (start.row == -1 && start.col == -1) {
        cerr << "Start point not found" << endl;
        return 1;
    }

    if (end.row == -1 && end.col == -1) {
        cerr << "End point not found" << endl;
        return 1;
    }

    search(lbr, rows, lbr[0].size(), start, end, cout);

    return 0;
}
