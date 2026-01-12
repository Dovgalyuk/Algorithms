#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "queue.h"

using namespace std;

typedef vector<string> Maze;

struct Position {
    int x, y;
    int prev;
};

typedef vector<Position> PositionList;
typedef pair<int, int> Coord;
typedef vector<vector<bool>> Visited;
const int dx[8] = { -1,-1,-1, 0,0, 1,1,1 };
const int dy[8] = { -1, 0, 1,-1,1,-1,0,1 };

Maze readMaze(const string& filename) {
    ifstream file(filename);
    Maze maze;
    string line;
    while (getline(file, line))
        maze.push_back(line);
    return maze;
}

Coord findPosition(const Maze& maze, char c) {
    for (size_t i = 0; i < maze.size(); ++i)
        for (size_t j = 0; j < maze[i].size(); ++j)
            if (maze[i][j] == c)
                return { (int)i, (int)j };
    return { -1, -1 };
}

inline bool isValid(int x, int y, const Maze& maze) {
    return x >= 0 && y >= 0 &&
        x < (int)maze.size() &&
        y < (int)maze[0].size() &&
        maze[x][y] != '#';
}

PositionList findPath(const Maze& maze, int& visited_count) {
    visited_count = 0;

    Coord start = findPosition(maze, 'Q');
    Coord end = findPosition(maze, 'E');

    if (start.first == -1 || end.first == -1)
        return {};

    Queue q;
    Visited visited(maze.size(), vector<bool>(maze[0].size(), false));
    PositionList pos;

    pos.push_back({ start.first, start.second, -1 });
    q.insert(0);
    visited[start.first][start.second] = true;
    visited_count++;

    while (!q.empty()) {
        int idx = q.get();
        q.remove();
        Position cur = pos[idx];

        if (cur.x == end.first && cur.y == end.second)
            return pos;

        for (int d = 0; d < 8; d++) {
            int x = cur.x + dx[d];
            int y = cur.y + dy[d];

            while (isValid(x, y, maze)) {
                if (!visited[x][y]) {
                    visited[x][y] = true;
                    visited_count++;
                    pos.push_back({ x, y, idx });
                    q.insert((int)pos.size() - 1);

                    if (x == end.first && y == end.second)
                        return pos;
                }
                x += dx[d];
                y += dy[d];
            }
        }
    }

    return pos;
}

void printSolution(const Maze& maze,
    const PositionList& pos,
    const Coord& end,
    int visited_count,
    const string& output_file)
{
    ofstream out(output_file);
    if (!out) return;

    int end_idx = -1;
    for (size_t i = 0; i < pos.size(); i++)
        if (pos[i].x == end.first && pos[i].y == end.second)
            end_idx = (int)i;

    if (end_idx == -1) {
        out << "Path not found";
        return;
    }

    int path_len = 0;
    for (int i = end_idx; pos[i].prev != -1; i = pos[i].prev)
        path_len++;

    out << "Path found: " << visited_count << "\n";
    out << "Path length: " << path_len << " moves\n";
    out << "Maze with path:\n";

    Maze result = maze;

    if (path_len > 1) {
        int cur = pos[end_idx].prev;
        if (result[pos[cur].x][pos[cur].y] != 'Q')
            result[pos[cur].x][pos[cur].y] = '*';
    }

    for (const auto& row : result)
        out << row << "\n";

}

int main(int argc, char* argv[]) {
    if (argc < 3)
        return 1;

    Maze maze = readMaze(argv[1]);

    int visited_count = 0;
    PositionList pos = findPath(maze, visited_count);

    printSolution(
        maze,
        pos,
        findPosition(maze, 'E'),
        visited_count,
        argv[2]
    );

    return 0;
}
