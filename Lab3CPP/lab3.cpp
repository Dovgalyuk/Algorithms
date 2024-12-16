#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "queue.h"
#include "list.h"
#include <string>

using namespace std;

//up, right, down, left
int moves[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

//structure for saving a point
struct Point {
    int x, y;
};

//сonverting the Point structure back to the Data type
Data pointToData(Point p, size_t cols) {
    return static_cast<Data>(p.x) * static_cast<Data>(cols) + static_cast<Data>(p.y);
}

//converting the Data type back to a Point structure 
Point dataToPoint(Data d, size_t cols) {
    Point p;
    p.x = d / static_cast<Data>(cols);
    p.y = d % cols;
    return p;
}

//function for finding a path in a labyrinth
void search(vector<vector<char>>& lbr, size_t rows, size_t cols, Point start, Point end, ostream& out) {
    if (start.x < 0 || start.y < 0 || static_cast<size_t>(start.x) >= rows || static_cast<size_t>(start.y) >= cols) {
        cerr << "Invalid starting point" << endl;
        return;
    }

    //creating a queue for processing points
    Queue* queue = queue_create();
    Data start_data = pointToData(start, cols);
    lbr[start.x][start.y] = '.'; //marking the starting point as visited
    queue_insert(queue, start_data);
    
    //array for tracking visited points
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[start.x][start.y] = true; //marking the starting point as visited

    bool path_found = false; 

    while (!queue_empty(queue)) {
        Data current_data = queue_get(queue);
        queue_remove(queue);

        Point current = dataToPoint(current_data, cols);

        //checking if the end point has been reached
        if (current.x == end.x && current.y == end.y) {
            path_found = true; 
            break; 
        }

        //checking around
        for (int i = 0; i < 4; i++) {
            int new_x = current.x + moves[i][0];
            int new_y = current.y + moves[i][1];

            //сhecking the boundaries of the labyrinth and the unvisited points
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && 
                (lbr[new_x][new_y] == '.' || lbr[new_x][new_y] == 'Y') && !visited[new_x][new_y]) {

                visited[new_x][new_y] = true; 
                Data new_data = pointToData({ new_x, new_y }, cols);
                queue_insert(queue, new_data); //adding to the queue
            }
        }
    }
    
    //сhecking for a path
    if (!path_found) {
        out << "IMPOSSIBLE\n"; 
    } else {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (lbr[i][j] == '.') {
                    lbr[i][j] = 'x'; 
                }
            }
        }
        lbr[start.x][start.y] = 'X'; 
        lbr[end.x][end.y] = 'Y';  

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
                lbr[rows][i] = '.'; 
            }
            if (row[i] == 'Y') {
                end = { static_cast<int>(rows), static_cast<int>(i) };
            }
        }
        rows++;
    }

    if (start.x == -1 && start.y == -1) {
        cerr << "Start point not found" << endl;
        return 1;
    }

    if (end.x == -1 && end.y == -1) { 
        cerr << "End point not found" << endl;
        return 1;
    }

    search(lbr, rows, lbr[0].size(), start, end, output_file); 
    return 0;
}
