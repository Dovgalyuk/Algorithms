#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

struct Point
{
    int row;
    int col;
};

typedef vector<string> HexGrid;
typedef vector<int> Row;
typedef vector<Row> Matrix;
typedef vector<Point> PointRow;
typedef vector<PointRow> PointMatrix;

Data encodePoint(int r, int c)
{
    return r * 1000 + c;
}

Point decodePoint(Data val)
{
    Point p;
    p.row = val / 1000;
    p.col = val % 1000;
    return p;
}

void addNeighbor(PointRow& neighbors, int nr, int nc, const HexGrid& grid)
{
    int rowCount = (int)grid.size();
    if (nr >= 0 && nr < rowCount) {
        if (nc >= 0 && nc < (int)grid[nr].size()) {
            Point p;
            p.row = nr;
            p.col = nc;
            neighbors.push_back(p);
        }
    }
}

PointRow getNeighbors(int r, int c, int R, const HexGrid& grid)
{
    PointRow neighbors;

    addNeighbor(neighbors, r, c - 1, grid);
    addNeighbor(neighbors, r, c + 1, grid);

    if (r < R - 1) {
        addNeighbor(neighbors, r - 1, c - 1, grid);
        addNeighbor(neighbors, r - 1, c, grid);
        addNeighbor(neighbors, r + 1, c, grid);
        addNeighbor(neighbors, r + 1, c + 1, grid);
    }
    else if (r == R - 1) {
        addNeighbor(neighbors, r - 1, c - 1, grid);
        addNeighbor(neighbors, r - 1, c, grid);
        addNeighbor(neighbors, r + 1, c - 1, grid);
        addNeighbor(neighbors, r + 1, c, grid);
    }
    else {
        addNeighbor(neighbors, r - 1, c, grid);
        addNeighbor(neighbors, r - 1, c + 1, grid);
        addNeighbor(neighbors, r + 1, c - 1, grid);
        addNeighbor(neighbors, r + 1, c, grid);
    }

    return neighbors;
}

void printHexMaze(const HexGrid& grid, int R)
{
    int rowCount = (int)grid.size();

    for (int r = 0; r < rowCount; r++) {
        int count = (int)grid[r].size();

        if (r < R) {
            int spaces = (R - 1 - r) * 2 + 1;
            for (int s = 0; s < spaces; s++) {
                cout << " ";
            }
            for (int c = 0; c < count; c++) {
                cout << "/ \\ ";
            }
            cout << endl;
        }

        int cellSpaces = 0;
        if (r < R) {
            cellSpaces = (R - 1 - r) * 2;
        }
        else {
            cellSpaces = (r - (R - 1)) * 2;
        }

        for (int s = 0; s < cellSpaces; s++) {
            cout << " ";
        }
        cout << "| ";
        for (int c = 0; c < count; c++) {
            cout << grid[r][c] << " | ";
        }
        cout << endl;

        if (r >= R - 1) {
            int spaces = (r - (R - 1)) * 2 + 1;
            for (int s = 0; s < spaces; s++) {
                cout << " ";
            }
            for (int c = 0; c < count; c++) {
                cout << "\\ / ";
            }
            cout << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    HexGrid grid;
    string line;
    while (getline(input, line)) {
        string clean = "";
        for (char ch : line) {
            if (ch != '\r' && ch != ' ') {
                clean += ch;
            }
        }
        if (!clean.empty()) {
            grid.push_back(clean);
        }
    }
    input.close();

    if (grid.empty()) {
        return 0;
    }

    int rowCount = (int)grid.size();
    int R = (rowCount + 1) / 2;

    Point start = { -1, -1 };
    Point end = { -1, -1 };

    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < (int)grid[r].size(); c++) {
            if (grid[r][c] == 'S') {
                start.row = r;
                start.col = c;
            }
            if (grid[r][c] == 'E') {
                end.row = r;
                end.col = c;
            }
        }
    }

    if (start.row == -1 || end.row == -1) {
        printHexMaze(grid, R);
        return 0;
    }

    Matrix dist(rowCount);
    PointMatrix parent(rowCount);
    for (int r = 0; r < rowCount; r++) {
        dist[r].assign(grid[r].size(), -1);
        parent[r].assign(grid[r].size(), { -1, -1 });
    }

    Queue* queue = queue_create();
    dist[start.row][start.col] = 0;
    queue_insert(queue, encodePoint(start.row, start.col));

    bool found = false;
    while (!queue_empty(queue)) {
        Point curr = decodePoint(queue_get(queue));
        queue_remove(queue);

        if (curr.row == end.row && curr.col == end.col) {
            found = true;
            break;
        }

        PointRow neighbors = getNeighbors(curr.row, curr.col, R, grid);
        for (Point next : neighbors) {
            if (grid[next.row][next.col] != '#' && dist[next.row][next.col] == -1) {
                dist[next.row][next.col] = dist[curr.row][curr.col] + 1;
                parent[next.row][next.col] = curr;
                queue_insert(queue, encodePoint(next.row, next.col));
            }
        }
    }
    queue_delete(queue);

    if (found) {
        Point curr = parent[end.row][end.col];
        while (!(curr.row == start.row && curr.col == start.col)) {
            grid[curr.row][curr.col] = 'x';
            curr = parent[curr.row][curr.col];
        }
    }

    printHexMaze(grid, R);
    return 0;
}