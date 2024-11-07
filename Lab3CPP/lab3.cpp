#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "queue.h"
#include <string>

using namespace std;

int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

struct Point {
    int x, y;
};

Data pointToData(Point p, size_t cols) {
    return static_cast<Data>(p.x) * static_cast<Data>(cols) + static_cast<Data>(p.y);
}

Point dataToPoint(Data d, size_t cols) {
    Point p;
    p.x = d / static_cast<Data>(cols);
    p.y = d % cols;
    return p;
}

void search(vector<vector<char>>& lbr, size_t rows, size_t cols, Point start, ostream& out) {
    if (start.x < 0 || start.y < 0 || static_cast<size_t>(start.x) >= rows || static_cast<size_t>(start.y) >= cols) {
        cerr << "Error: invalid starting point" << endl;
        return; 
    }

    Queue* queue = queue_create();
    Data start_data = pointToData(start, cols);
    queue_insert(queue, start_data);

    int count = 0;

    while (!queue_empty(queue)) {
        Data current_data = queue_get(queue);
        queue_remove(queue);

        Point current = dataToPoint(current_data, cols);

        if (lbr[current.x][current.y] == '.') {
            lbr[current.x][current.y] = 'x';
            count++;

            for (int i = 0; i < 4; i++) {
                int new_x = current.x + moves[i][0];
                int new_y = current.y + moves[i][1];

                if (new_x >= 0 && static_cast<size_t>(new_x) < rows && new_y >= 0 && static_cast<size_t>(new_y) < cols &&
                    (lbr[new_x][new_y] == '.' || lbr[new_x][new_y] == 'X')) {
                    Data new_data = pointToData({ new_x, new_y }, cols);
                    queue_insert(queue, new_data);
                }
            }
        }
    }

    out << count << endl; 
    for (size_t i = 0; i < rows; i++) {
        out << string(lbr[i].begin(), lbr[i].end()) << endl; 
    }

    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    vector<vector<char>> lbr;
    Point start = { -1, -1 };
    size_t rows = 0;

    ifstream input_file(argv[1]);
    ofstream output_file(argv[2]);

    if (!input_file) {
        cerr << "Error: could not open input file " << argv[1] << endl;
        return 1;
    }

    string line;
    while (getline(input_file, line)) {
        vector<char> row(line.begin(), line.end());
        lbr.push_back(row);

        for (size_t i = 0; i < row.size(); i++) {
            if (row[i] == 'X') {
                start = { static_cast<int>(rows), static_cast<int>(i) };
                lbr[rows][i] = '.';
            }
        }
        rows++;
    }

    if (start.x == -1 && start.y == -1) {
        cerr << "Error: start point not found" << endl;
        return 1;
    }

    search(lbr, rows, lbr[0].size(), start, output_file);

    return 0;
}

