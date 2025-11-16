#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "queue.h"
#include <algorithm> 

using namespace std;

struct Position {
    int row;
    int col;
    
    Position(int r = 0, int c = 0) : row(r), col(c) {}
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

class PositionEncoder {
public:
    static int encode(const Position& pos, int width) {
        return pos.row * width + pos.col;
    }
    
    static Position decode(int encoded, int width) {
        return Position(encoded / width, encoded % width);
    }
};

class INeighborStrategy {
public:
    virtual ~INeighborStrategy() = default;
    virtual vector<Position> getNeighbors(const Position& pos, 
                                          int height, 
                                          int width) const = 0;
};

class HexagonalNeighborStrategy : public INeighborStrategy {
public:
    vector<Position> getNeighbors(const Position& pos, 
                                  int height, 
                                  int width) const override {
        vector<Position> neighbors;
        int row = pos.row;
        int col = pos.col;
        
        if (col > 0) {
            neighbors.push_back(Position(row, col - 1));
        }
        if (col < width - 1) {
            neighbors.push_back(Position(row, col + 1));
        }
        
        if (row % 2 == 0) {
            if (row > 0) {
                neighbors.push_back(Position(row - 1, col));
            }
            if (row < height - 1) {
                neighbors.push_back(Position(row + 1, col));
            }
        } else {
            if (row > 0) {
                neighbors.push_back(Position(row - 1, col));
            }
            if (row < height - 1) {
                neighbors.push_back(Position(row + 1, col));
            }
        }
        
        return neighbors;
    }
};

class HexagonalMaze {
private:
    vector<string> grid_;
    int height_;
    int width_;
    Position start_;
    Position end_;
    
public:
    HexagonalMaze(const vector<string>& grid) 
        : grid_(grid), 
          height_(static_cast<int>(grid.size())), 
          width_(grid.empty() ? 0 : static_cast<int>(grid[0].size())) {
        findStartAndEnd();
    }
    
    int getHeight() const { return height_; }
    int getWidth() const { return width_; }
    const Position& getStart() const { return start_; }
    const Position& getEnd() const { return end_; }
    
    bool isWalkable(const Position& pos) const {
        if (!isInBounds(pos)) {
            return false;
        }
        char cell = grid_[pos.row][pos.col];
        return cell != '#';
    }
    
    bool isInBounds(const Position& pos) const {
        return pos.row >= 0 && pos.row < height_ && 
               pos.col >= 0 && pos.col < width_;
    }
    
    char getCell(const Position& pos) const {
        return grid_[pos.row][pos.col];
    }
    
private:
    void findStartAndEnd() {
        bool foundStart = false;
        bool foundEnd = false;
        
        for (int row = 0; row < height_; ++row) {
            for (int col = 0; col < width_; ++col) {
                if (grid_[row][col] == 'S') {
                    start_ = Position(row, col);
                    foundStart = true;
                } else if (grid_[row][col] == 'E') {
                    end_ = Position(row, col);
                    foundEnd = true;
                }
            }
        }
        
        if (!foundStart || !foundEnd) {
            throw runtime_error("Maze must contain both S and E");
        }
    }
};

struct PathFindingResult {
    bool pathFound;
    vector<Position> path;
    
    PathFindingResult() : pathFound(false) {}
};

class HexagonalPathFinder {
private:
    const HexagonalMaze& maze_;
    unique_ptr<INeighborStrategy> neighborStrategy_;
    
public:
    HexagonalPathFinder(const HexagonalMaze& maze, 
                        unique_ptr<INeighborStrategy> strategy)
        : maze_(maze), neighborStrategy_(move(strategy)) {}
    
    PathFindingResult findShortestPath() {
        PathFindingResult result;
        
        int height = maze_.getHeight();
        int width = maze_.getWidth();
        Position start = maze_.getStart();
        Position end = maze_.getEnd();
        
        vector<vector<int>> distance(height, vector<int>(width, -1));
        
        vector<vector<Position>> parent(
            height, vector<Position>(width, Position(-1, -1))
        );
        
        Queue queue;
        queue.insert(PositionEncoder::encode(start, width));
        distance[start.row][start.col] = 0;
        
        while (!queue.empty()) {
            int encoded = queue.get();
            queue.remove();
            
            Position current = PositionEncoder::decode(encoded, width);
            
            if (current == end) {
                result.pathFound = true;
                result.path = reconstructPath(parent, start, end);
                return result;
            }
            
            vector<Position> neighbors = 
                neighborStrategy_->getNeighbors(current, height, width);
            
            for (const Position& neighbor : neighbors) {
                if (maze_.isWalkable(neighbor) && 
                    distance[neighbor.row][neighbor.col] == -1) {
                    
                    distance[neighbor.row][neighbor.col] = 
                        distance[current.row][current.col] + 1;
                    parent[neighbor.row][neighbor.col] = current;
                    queue.insert(PositionEncoder::encode(neighbor, width));
                }
            }
        }
        
        return result;
    }
    
private:
    vector<Position> reconstructPath(
        const vector<vector<Position>>& parent,
        const Position& start,
        const Position& end) {
        
        vector<Position> path;
        Position current = end;
        
        while (!(current == start)) {
            path.push_back(current);
            current = parent[current.row][current.col];
        }
        path.push_back(start);
        
        reverse(path.begin(), path.end());
        return path;
    }
};

class MazeOutputFormatter {
private:
    const HexagonalMaze& maze_;
    
public:
    explicit MazeOutputFormatter(const HexagonalMaze& maze) : maze_(maze) {}
    
    void printMazeWithPath(const vector<Position>& path) const {
        int height = maze_.getHeight();
        int width = maze_.getWidth();
        
        vector<vector<bool>> isOnPath(height, vector<bool>(width, false));
        
        int pathSize = static_cast<int>(path.size());
        for (int i = 1; i < pathSize - 1; ++i) {
            isOnPath[path[i].row][path[i].col] = true;
        }
        
        for (int row = 0; row < height; ++row) {
            if (row == 0) {
                cout << " ";
                for (int col = 0; col < width; ++col) {
                    cout << "/ \\ ";
                }
                cout << "\n";
            }
            
            int contentIndent = (row == 0) ? 0 : row * 2;
            for (int i = 0; i < contentIndent; ++i) {
                cout << " ";
            }
            
            cout << "|";
            for (int col = 0; col < width; ++col) {
                char cell = maze_.getCell(Position(row, col));
                
                if (cell == 'S' || cell == 'E') {
                    cout << " " << cell << " |";
                } else if (isOnPath[row][col]) {
                    cout << " x |";
                } else if (cell == '#') {
                    cout << " # |";
                } else {
                    cout << "   |";
                }
            }
            cout << "\n";
            
            int borderIndent = row * 2 + 1;
            for (int i = 0; i < borderIndent; ++i) {
                cout << " ";
            }
            
            for (int col = 0; col < width; ++col) {
                cout << "\\ / ";
            }
            
            if (row < height - 1) {
                cout << "\\";
            }
            
            cout << "\n";
        }
    }
};

class MazeFileReader {
public:
    static vector<string> readMaze(ifstream& input) {
        vector<string> grid;
        string line;
        
        while (getline(input, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                grid.push_back(line);
            }
        }
        
        if (grid.empty()) {
            throw runtime_error("Empty maze file");
        }
        
        return grid;
    }
};

class MazeSolverApplication {
public:
    int run(ifstream& input) {
        try {
            static vector<string> grid = MazeFileReader::readMaze(input);
            
            HexagonalMaze maze(grid);
            
            HexagonalPathFinder pathFinder(
                maze, 
                make_unique<HexagonalNeighborStrategy>()
            );
            
            PathFindingResult result = pathFinder.findShortestPath();
            
            if (result.pathFound) {
                MazeOutputFormatter formatter(maze);
                formatter.printMazeWithPath(result.path);
            } else {
                cout << "No path found from S to E\n";
            }
            
            return 0;
            
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }
    }
};

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
    
    MazeSolverApplication app;
    int result = app.run(input);
    
    input.close();
    return result;
}