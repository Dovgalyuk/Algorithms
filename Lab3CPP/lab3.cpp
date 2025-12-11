#include <iostream>
#include <fstream>
#include <vector>
#include "../LibraryCPPClass/queue.h"

using namespace std;

// Для улучшения читаемочти кода
#define X first
#define Y second

// Одна функция для нахождения начала и конца, для улучшния читабельности кода сделал их
const char START = 'Q';
const char END = 'E';

pair<int, int> find_point(const vector<string>& maze, char point) {
    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == point) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}
// Это перевод с pair в int, но используется только в очереди, такчто будет pair to queue
int ptoq(pair<int, int> pos, int cols) {
    return pos.X * cols + pos.Y;
}

int bfs(const vector<string>& maze, pair<int, int> start, pair<int, int> end) {
    if (start.X == -1 || end.X == -1) {
        return 0;
    }
    
    if (start == end) return 1;

    int rows = maze.size();
    int cols = maze[0].size();
    
    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    vector<vector<int>> count(rows, vector<int>(cols, 0));
    vector<vector<bool>> inQueue(rows, vector<bool>(cols, false));
    
    // 8 направлений движения ферзя (x,y)
    const pair<int, int> moveQueen[8] = {
        {-1,-1}, {-1,0}, {-1,1},
        {0,-1},  /* Q */  {0,1},
        {1,-1},  {1,0},  {1,1}
    };
    
    Queue q;
    dist[start.X][start.Y] = 0;
    count[start.X][start.Y] = 1;
    
    q.insert(ptoq(start, cols));
    inQueue[start.X][start.Y] = true;
    
    while (!q.empty()) {
        int currentIndex = q.take();
        
        int y = currentIndex / cols;
        int x = currentIndex % cols;
        inQueue[y][x] = false;
        
        int d = dist[y][x];
        int c = count[y][x];
        
        for (const auto& dir : moveQueen) {
            int dy = dir.X;
            int dx = dir.Y;
            

            for (int step = 1; ; step++) {
                int ny = y + dy * step;
                int nx = x + dx * step;
                
                if (ny < 0 || ny >= rows || nx < 0 || nx >= cols) break;
                if (maze[ny][nx] == '#') break;
                
                int newDistant = d + 1;
                
                if (dist[ny][nx] == -1) {
                    dist[ny][nx] = newDistant;
                    count[ny][nx] = c;
                    
                    if (!inQueue[ny][nx] && !(ny == end.X && nx == end.Y)) {
                        q.insert(ptoq({ny, nx}, cols));
                        inQueue[ny][nx] = true;
                    }
                }
                else if (newDistant == dist[ny][nx]) {
                    count[ny][nx] += c;
                    if (!inQueue[ny][nx]) {
                        q.insert(ptoq({ny, nx}, cols));
                        inQueue[ny][nx] = true;
                    }
                }

            }
        }
    }
    
    return count[end.X][end.Y];
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
    
    vector<string> maze;
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