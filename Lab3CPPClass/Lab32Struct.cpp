#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "queue.h"

using namespace std;

typedef vector<string> Maze;

struct Position {
    int x, y;
    int prev_index;
    char move;
};

typedef vector<Position> PositionList;
typedef pair<int, int> Coord;
typedef vector<vector<bool>> Visited;

const int dx[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
const int dy[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };

Maze readMaze(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: cannot open file " << filename << endl;
        return {};
    }

    Maze maze;
    string line;
    while (getline(file, line))
        maze.push_back(line);

    return maze;
}

Coord findPosition(const Maze& maze, char target) {
    for (size_t i = 0; i < maze.size(); ++i)
        for (size_t j = 0; j < maze[i].size(); ++j)
            if (maze[i][j] == target)
                return { (int)i, (int)j };

    return { -1, -1 };
}

inline bool isValid(int x, int y, const Maze& maze) {
    return x >= 0 && y >= 0 &&
        x < (int)maze.size() &&
        y < (int)maze[0].size() &&
        maze[x][y] != '#';
}

string getPath(const PositionList& pos, int index) {
    string path;
    while (index != -1 && pos[index].move) {
        path = pos[index].move + path;
        index = pos[index].prev_index;
    }
    return path;
}

PositionList findPath(const Maze& maze) {
    Coord start = findPosition(maze, 'Q');
    Coord end = findPosition(maze, 'E');

    if (start.first == -1 || end.first == -1)
        return {};

    Queue q;
    Visited visited(maze.size(), vector<bool>(maze[0].size(), false));
    PositionList pos;

    pos.push_back({ start.first, start.second, -1, 0 });
    q.insert(0);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        int idx = q.get();
        q.remove();

        Position cur = pos[idx];
        if (cur.x == end.first && cur.y == end.second)
            return pos;

        for (int i = 0; i < 8; i++) {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];

            while (isValid(x, y, maze)) {
                if (!visited[x][y]) {
                    visited[x][y] = true;
                    pos.push_back({ x, y, idx, char('1' + i) });

                    q.insert((int)pos.size() - 1);

                    if (x == end.first && y == end.second)
                        return pos;
                }
                x += dx[i];
                y += dy[i];
            }
        }
    }

    return {};
}

void printSolution(const Maze& maze,
    const PositionList& pos,
    const Coord& end_pos,
    const string& output_file)
{
    int end_index = -1;
    for (size_t i = 0; i < pos.size(); i++)
        if (pos[i].x == end_pos.first && pos[i].y == end_pos.second)
            end_index = (int)i;

    ofstream out(output_file);
    if (!out) return;

    if (end_index == -1) {
        out << "Path not found\n";
        return;
    }

    string path;
    int cur = end_index;
    while (cur != -1 && pos[cur].move) {
        path = pos[cur].move + path;
        cur = pos[cur].prev_index;
    }

    out << "Path found: " << path << "\n";
    out << "Path length: " << path.length() << " moves\n";
    out << "Maze with path:\n";

    Maze result = maze;
    cur = end_index;
    while (cur != -1) {
        if (result[pos[cur].x][pos[cur].y] != 'Q' &&
            result[pos[cur].x][pos[cur].y] != 'E')
            result[pos[cur].x][pos[cur].y] = '*';
        cur = pos[cur].prev_index;
    }

    for (const auto& row : result)
        out << row << "\n";
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    string input = argv[1];
    string output = argv[2];

    Maze maze = readMaze(input);

    if (maze.empty()) {
        cout << "Error: failed to read maze.\n";
        return 1;
    }

    Coord start = findPosition(maze, 'Q');
    Coord end = findPosition(maze, 'E');

    if (start.first == -1) {
        cout << "Error: start 'Q' not found.\n";
        return 1;
    }
    if (end.first == -1) {
        cout << "Error: finish 'E' not found.\n";
        return 1;
    }

    PositionList pos = findPath(maze);
    printSolution(maze, pos, end, output);

    return 0;
}
