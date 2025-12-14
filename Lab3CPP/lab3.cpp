#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

using namespace std;

typedef vector<string> Maze;

struct Point
{
    int x, y;
    Point(): x(0), y(0){}
    Point(int x_, int y_): x(x_), y(y_){}
    bool operator==(const Point &other) const{
        return this->x == other.x && this->y == other.y;
    }
};

// Одна функция для нахождения начала и конца, для улучшния читабельности кода сделал их
const char START = 'Q';
const char END = 'E';

Point find_point(const Maze& maze, char point) {
    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == point) {
                return {static_cast<int>(i), static_cast<int>(j)};
            }
        }
    }
    return {-1, -1};
}
// Это перевод с Point в int, но используется только в очереди, так что будет Point to queue
int ptoq(Point pos, int cols) {
    return pos.x * cols + pos.y;
}

int bfs(const Maze& maze, Point start, Point end) {
    if (start.x == -1 || end.x == -1) {
        return 0;
    }
    // сделал для теста, чтобы показать, что выполняется условие на которое вы показали. Для удобства взял string

    int rows = maze.size();
    int cols = maze[0].size();
    
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    vector<vector<int>> count(rows, vector<int>(cols, 0));
    vector<vector<bool>> inQueue(rows, vector<bool>(cols, false));
    
    // 8 направлений движения ферзя (x,y)
    const Point moveQueen[8] = {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},  /* Q */ {0,1},
        {1,-1},  {1,0},  {1,1}
    };
    
    Queue q;
    dist[start.x][start.y] = 0;
    count[start.x][start.y] = 1;
    
    q.insert(ptoq(start, cols));
    inQueue[start.x][start.y] = true;
    
    while (!q.empty()) {
        int currentIndex = q.take();
        
        int y = currentIndex / cols;
        int x = currentIndex % cols;
        inQueue[y][x] = false;

        int d = dist[y][x];
        int c = count[y][x];
        
        for (const auto& dir : moveQueen) {
            int dy = dir.x;
            int dx = dir.y;
            

            for (int step = 1; ; step++) {
                int ny = y + dy * step;
                int nx = x + dx * step;
                
                if (ny < 0 || ny >= rows || nx < 0 || nx >= cols) break;
                if (maze[ny][nx] == '#') break;
                
                int newDistant = d + 1;
                
                if (dist[ny][nx] == -1) {
                    dist[ny][nx] = newDistant;
                    count[ny][nx] = c;
                    
                    if (!(ny == end.x && nx == end.y)) {
                        q.insert(ptoq({ny, nx}, cols));
                        inQueue[ny][nx] = true;
                    }
                }
                else if (newDistant == dist[ny][nx]) {
                    count[ny][nx] += c;
                }

            }
        }
    }
    return count[end.x][end.y];
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <maze_file>" << endl;
        return 1;
    }
    
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }
    
    Maze maze;
    string line;
    while (getline(file, line)) {
        maze.push_back(line);
    }
    file.close();
    
    auto start = find_point(maze, START);
    auto end = find_point(maze, END);
    
    cout << bfs(maze, start, end) << endl;
    
    return 0;
}