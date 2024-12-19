#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "../LibraryCPP/queue.h"
#include "../LibraryCPP/list.h"
#include <string>

using namespace std;

//right, down, left, up
int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

//structure for saving a point
struct Point {
    int row, col;
};

//convert Point structure to Data type
Data pointToData(Point p, size_t cols) {
    return static_cast<Data>(p.row) * static_cast<Data>(cols) + static_cast<Data>(p.col);
}

//convert Data type back to Point structure
Point dataToPoint(Data d, size_t cols) {
    Point p;
    p.row = d / static_cast<Data>(cols);
    p.col = d % cols;
    return p;
}

//function to find a path in the labyrinth
void search(vector<vector<char>>& lbr, size_t rows, size_t cols, Point start, Point end, ostream& out) {
    Queue* queue = queue_create();
    Data start_data = pointToData(start, cols);
    lbr[start.row][start.col] = '.'; //mark the starting point as visited
    queue_insert(queue, start_data); //add the starting point to the queue

    //array for tracking visited points
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[start.row][start.col] = true; // Mark the starting point as visited

    //array to restore the path
    vector<vector<Point>> parents(rows, vector<Point>(cols, { -1, -1 }));

    bool path_found = false;

    while (!queue_empty(queue)) {
        Data current_data = queue_get(queue);
        queue_remove(queue);

        Point current = dataToPoint(current_data, cols);

        //checking if the end point has been reached
        if (current.row == end.row && current.col == end.col) {
            path_found = true;
            break;
        }

        //checking neighboring nodes
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + moves[i][0];
            int new_col = current.col + moves[i][1];

            //checking the boundaries of the labyrinth and visited points
            if (new_row >= 0 && static_cast<size_t>(new_row) < rows &&
                new_col >= 0 && static_cast<size_t>(new_col) < cols &&
                (lbr[new_row][new_col] == '.' || lbr[new_row][new_col] == 'Y') && 
                !visited[new_row][new_col]) {

                visited[new_row][new_col] = true;
                parents[new_row][new_col] = current;
                Data new_data = pointToData({ new_row, new_col }, cols);
                queue_insert(queue, new_data); //add the new point to the queue
            }
        }
    }

    // Checking for a path
    if (!path_found) {
        out << "IMPOSSIBLE\n";
    } else {
        Point p = end;
        while (p.row != -1 && p.col != -1) {
            if (lbr[p.row][p.col] == '.') {
                lbr[p.row][p.col] = 'x'; //mark the path
            }
            p = parents[p.row][p.col];
        }

        lbr[start.row][start.col] = 'X'; //restore start point
        lbr[end.row][end.col] = 'Y'; //restore end point

        //output labyrinth
        for (const auto& row : lbr) {
            out << string(row.begin(), row.end()) << endl;
        }
    }

    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    ofstream output_file(argv[2]);

    if (!input_file) {
        cerr << "Couldn't open input file " << argv[1] << endl;
        return 1;
    }

    if (!output_file) {
        cerr << "Couldn't open output file " << argv[2] << endl;
        return 1;
    }

    vector<vector<char>> lbr;
    Point start = { -1, -1 };
    Point end = { -1, -1 };
    size_t rows = 0;

    string line;
    while (getline(input_file, line)) {
        vector<char> row(line.begin(), line.end());
        lbr.push_back(row);

        for (size_t i = 0; i < row.size(); i++) {
            if (row[i] == 'X') {
                start = { static_cast<int>(rows), static_cast<int>(i) };
                lbr[rows][i] = '.'; //mark the starting point as visitable
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

    search(lbr, rows, lbr[0].size(), start, end, output_file);

    input_file.close();
    output_file.close();

    return 0;
}
