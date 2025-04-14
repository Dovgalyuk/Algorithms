#include <iostream>
#include <vector>
#include <fstream>
#include "queue.h"

using namespace std;

struct Point {
    int row, col;
};

typedef vector<vector<char>> Labyrinth;

int pointToData(Point p, size_t cols) {
    return p.row * cols + p.col;
}

Point dataToPoint(int d, size_t cols) {
    return { static_cast<int>(d / cols), static_cast<int>(d % cols) };
}

int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void reachableCells(Labyrinth& lbr, Point start, ostream& out) {
    Queue* queue = queue_create();
    queue_insert(queue, pointToData(start, lbr[0].size()));

    vector<vector<bool>> visited(lbr.size(), vector<bool>(lbr[0].size(), false));
    visited[start.row][start.col] = true;

    int count = 1;
    lbr[start.row][start.col] = 'x';

    while (!queue_empty(queue)) {
        int current_data = queue_get(queue);
        queue_remove(queue);
        Point current = dataToPoint(current_data, lbr[0].size());

        for (auto& move : moves) {
            int new_row = current.row + move[0];
            int new_col = current.col + move[1];

            if (new_row >= 0 && static_cast<size_t>(new_row) < lbr.size() &&
                new_col >= 0 && static_cast<size_t>(new_col) < lbr[0].size() &&
                lbr[new_row][new_col] == '.' &&
                !visited[new_row][new_col]) {

                visited[new_row][new_col] = true;
                lbr[new_row][new_col] = 'x';
                ++count;
                queue_insert(queue, pointToData({ new_row, new_col }, lbr[0].size()));
            }
        }
    }

    queue_delete(queue);

    // После обхода — вывод результата
    out << count << '\n';
    for (const auto& row : lbr) {
        out << string(row.begin(), row.end()) << '\n';
    }
}

void readLabyrinthFromStream(istream& in, Labyrinth& lbr, Point& start) {
    string line;
    while (getline(in, line)) {
        if (line.empty()) break;

        vector<char> row(line.begin(), line.end());
        for (size_t i = 0; i < row.size(); ++i) {
            if (row[i] == 'X') {
                start = { static_cast<int>(lbr.size()), static_cast<int>(i) };
                row[i] = '.'; // Превращаем в проходимую клетку
            }
        }
        lbr.push_back(row);
    }
}

int main(int argc, char* argv[]) {
    Labyrinth lbr;
    Point start = { -1, -1 };

    if (argc > 1) {
        ifstream inputFile(argv[1]);
        if (inputFile) {
            readLabyrinthFromStream(inputFile, lbr, start);
        } else {
            cerr << "Couldn't open the file " << argv[1] << endl;
            return 1;
        }
    } else {
        cout << "Enter the maze:" << endl;
        readLabyrinthFromStream(cin, lbr, start);
    }

    if (start.row == -1 || start.col == -1) {
        cerr << "Start point (X) not found." << endl;
        return 1;
    }

    reachableCells(lbr, start, cout);
    return 0;
}
