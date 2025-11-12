#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

typedef int Data;

vector<pair<int, int>> getNeighbors(int row, int col) {
    vector<pair<int, int>> neighbors;
    
    if (row % 2 == 0) {
        neighbors.push_back({row - 1, col - 1});
        neighbors.push_back({row - 1, col});
        neighbors.push_back({row, col - 1});
        neighbors.push_back({row, col + 1});
        neighbors.push_back({row + 1, col - 1});
        neighbors.push_back({row + 1, col});
    } else {
        neighbors.push_back({row - 1, col});
        neighbors.push_back({row - 1, col + 1});
        neighbors.push_back({row, col - 1});
        neighbors.push_back({row, col + 1});
        neighbors.push_back({row + 1, col});
        neighbors.push_back({row + 1, col + 1});
    }
    
    return neighbors;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream input(argv[1]);
    if (!input) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }
    
    vector<string> maze;
    string line;
    
    while (getline(input, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) {
            maze.push_back(line);
        }
    }
    input.close();
    
    if (maze.empty()) {
        cerr << "Empty maze" << endl;
        return 1;
    }
    
    int rows = static_cast<int>(maze.size());
    int cols = static_cast<int>(maze[0].size());
    
    int startRow = -1, startCol = -1;
    int endRow = -1, endCol = -1;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 'S') {
                startRow = i;
                startCol = j;
            }
            if (maze[i][j] == 'E') {
                endRow = i;
                endCol = j;
            }
        }
    }
    
    if (startRow == -1 || endRow == -1) {
        cerr << "Start or end position not found" << endl;
        return 1;
    }
    
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    Queue q;
    q.insert(startRow * cols + startCol);
    dist[startRow][startCol] = 0;
    
    bool found = false;
    
    while (!q.empty()) {
        int current = q.get();
        q.remove();
        
        int row = current / cols;
        int col = current % cols;
        
        if (row == endRow && col == endCol) {
            found = true;
            break;
        }
        
        vector<pair<int, int>> neighbors = getNeighbors(row, col);
        
        for (auto& neighbor : neighbors) {
            int newRow = neighbor.first;
            int newCol = neighbor.second;
            
            if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
                continue;
            }
            
            if (maze[newRow][newCol] != '#' && dist[newRow][newCol] == -1) {
                dist[newRow][newCol] = dist[row][col] + 1;
                prev[newRow][newCol] = {row, col};
                q.insert(newRow * cols + newCol);
            }
        }
    }
    
    if (!found) {
        cout << "Путь не найден" << endl;
        return 0;
    }
    
    vector<vector<bool>> path(rows, vector<bool>(cols, false));
    int curRow = endRow, curCol = endCol;
    
    while (curRow != startRow || curCol != startCol) {
        path[curRow][curCol] = true;
        pair<int, int> p = prev[curRow][curCol];
        curRow = p.first;
        curCol = p.second;
    }
    path[startRow][startCol] = true;
    
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < i; k++) {
            cout << " ";
        }
        
        cout << " / \\ / \\ / \\" << endl;
        
        for (int k = 0; k < i; k++) {
            cout << " ";
        }
        
        for (int j = 0; j < cols; j++) {
            cout << "| ";
            if (maze[i][j] == 'S' || maze[i][j] == 'E') {
                cout << maze[i][j];
            } else if (path[i][j]) {
                cout << "x";
            } else if (maze[i][j] == '#') {
                cout << "#";
            } else {
                cout << " ";
            }
            cout << " ";
        }
        cout << "|" << endl;
        
        for (int k = 0; k < i + 1; k++) {
            cout << " ";
        }
        cout << "\\ / \\ / \\ /" << endl;
    }
    
    return 0;
}
