#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

void readMaze(ifstream& input, char**& maze, int& rows, int& cols, int& startX, int& startY) {
    string line;
    rows = 0;
    cols = 0;
    startX = -1;  // Инициализируем как -1 (не найдено)
    startY = -1;
    
    while (getline(input, line)) {
        rows++;
        int lineLength = line.length();
        if (lineLength > cols) cols = lineLength;
    }
    
    input.clear();
    input.seekg(0);
    
    maze = new char*[rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new char[cols];
    }
    
    for (int i = 0; i < rows; i++) {
        getline(input, line);
        int lineLength = line.length();
        for (int j = 0; j < cols; j++) {
            if (j < lineLength) {
                maze[i][j] = line[j];
                if (line[j] == 'X' && startX == -1) {  // Находим первую стартовую позицию
                    startX = j;
                    startY = i;
                }
            } else {
                maze[i][j] = ' ';
            }
        }
    }
}

void freeMaze(char** maze, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] maze[i];
    }
    delete[] maze;
}

int bfs(char** maze, int rows, int cols, int startX, int startY) {
    // Если стартовая позиция не найдена, возвращаем 0
    if (startX == -1 || startY == -1) {
        return 0;
    }
    
    Queue* queue = queue_create();
    int count = 1;
    queue_insert(queue, startX);
    queue_insert(queue, startY);
    maze[startY][startX] = 'x';
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    
    while (!queue_empty(queue)) {
        int x = queue_get(queue);
        queue_remove(queue);
        int y = queue_get(queue);
        queue_remove(queue);
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && ny >= 0 && ny < rows && nx < cols && maze[ny][nx] == '.') {
                count++;
                maze[ny][nx] = 'x';
                queue_insert(queue, nx);
                queue_insert(queue, ny);
            }
        }
    }
    
    queue_delete(queue);
    maze[startY][startX] = 'X';
    
    return count;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }
    
    char** maze = nullptr;
    int rows, cols, startX, startY;
    
    readMaze(input, maze, rows, cols, startX, startY);
    input.close();
    
    int count = bfs(maze, rows, cols, startX, startY);
    
    cout << count << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
    
    freeMaze(maze, rows);
    return 0;
}