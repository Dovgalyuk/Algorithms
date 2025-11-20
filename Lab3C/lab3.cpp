#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include "queue.h"

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class MazeSolver {
private:
    std::vector<std::string> maze;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<bool>> visited;
    int rows, cols;
    Point start;
    std::vector<Point> targets;

public:
    bool readMaze(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        std::vector<std::string> lines;
        
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        
        if (lines.empty()) return false;
        
        rows = lines.size();
        cols = lines[0].size();
        
        maze.resize(rows);
        distance.resize(rows, std::vector<int>(cols, INT_MAX));
        visited.resize(rows, std::vector<bool>(cols, false));
        
        for (int i = 0; i < rows; ++i) {
            maze[i] = lines[i];
            
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 'X') {
                    start = Point(i, j);
                } else if (maze[i][j] >= '0' && maze[i][j] <= '9') {
                    targets.push_back(Point(i, j));
                }
            }
        }
        
        return true;
    }

    char findNearestTarget() {
        if (targets.empty()) return '?';
        
        Queue* queue = queue_create();
        distance[start.x][start.y] = 0;
        visited[start.x][start.y] = true;
        
        int start_index = start.x * cols + start.y;
        queue_insert(queue, start_index);
        
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        
        char result = '?';
        int min_distance = INT_MAX;
        
        while (!queue_empty(queue)) {
            int current_index = queue_get(queue);
            queue_remove(queue);
            
            int row = current_index / cols;
            int col = current_index % cols;
            char cell = maze[row][col];
            int current_distance = distance[row][col];
            
            if (cell >= '0' && cell <= '9') {
                if (current_distance < min_distance) {
                    min_distance = current_distance;
                    result = cell;
                }
                continue;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nx = row + dx[i];
                int ny = col + dy[i];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                    maze[nx][ny] != '#' && !visited[nx][ny]) {
                    
                    visited[nx][ny] = true;
                    distance[nx][ny] = current_distance + 1;
                    int neighbor_index = nx * cols + ny;
                    queue_insert(queue, neighbor_index);
                }
            }
        }
        
        queue_delete(queue);
        return result;
    }
};

int main(int argc, char* argv[]) {
    std::string filename = "input.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    MazeSolver solver;
    if (!solver.readMaze(filename)) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return 1;
    }
    
    char nearest = solver.findNearestTarget();
    if (nearest != '?') {
        std::cout << nearest << std::endl;
    } else {
        std::cout << "No target found" << std::endl;
    }
    
    return 0;
}
