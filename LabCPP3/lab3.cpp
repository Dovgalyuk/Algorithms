#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

struct Position {
    int r, c;
    Position(int rr = -1, int cc = -1) : r(rr), c(cc) {}
    bool operator==(const Position& o) const { return r == o.r && c == o.c; }
};

static int maxWidth(const vector<string>& grid)
{
    int maxW = 0;
    for (const auto& row : grid) maxW = max(maxW, (int)row.size());
    return maxW;
}

static bool isWall(const vector<string>& grid, const Position& p)
{
    return grid[p.r][p.c] == '#';
}

static vector<string> readGrid(const char* filename)
{
    ifstream in(filename);
    if (!in) {
        cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }
    vector<string> grid;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) grid.push_back(line);
    }
    if (grid.empty()) {
        cerr << "Empty input\n";
        exit(1);
    }
    return grid;
}

static void findStartEnd(const vector<string>& grid,
    Position& start, Position& end)
{
    for (int r = 0; r < (int)grid.size(); ++r)
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            if (grid[r][c] == 'S') start = { r, c };
            if (grid[r][c] == 'E') end = { r, c };
        }
    if (start.r == -1 || end.r == -1) {
        cerr << "No S or E in maze\n";
        exit(1);
    }
}

static vector<Position> neighbors(const vector<string>& grid, int r, int c)
{
    vector<Position> res;
    int H = (int)grid.size();
    int w = (int)grid[r].size();

    if (c - 1 >= 0)          res.push_back({ r, c - 1 });
    if (c + 1 < w)           res.push_back({ r, c + 1 });

    for (int dr : {-1, 1}) {
        int nr = r + dr;
        if (nr < 0 || nr >= H) continue;
        int nw = (int)grid[nr].size();
        if (nw >= w) {
            if (c < nw) res.push_back({ nr, c });
            if (c + 1 < nw) res.push_back({ nr, c + 1 });
        }
        else {
            if (c - 1 >= 0 && c - 1 < nw) res.push_back({ nr, c - 1 });
            if (c >= 0 && c < nw) res.push_back({ nr, c });
        }
    }
    return res;
}

static void printHexBorder(int indent, int count, int kind,
    bool newline = true)
{
    cout << string(indent, ' ');
    for (int j = 0; j < count; ++j) {
        if (j > 0) cout << " ";
        cout << (kind == 0 ? "/ \\" : "\\ /");
    }
    if (newline) cout << '\n';
}

static void tracePath(const vector<string>& grid,
    const vector<vector<int>>& dist,
    Position start, Position end,
    vector<vector<bool>>& onPath)
{
    Position cur = end;
    while (!(cur == start)) {
        onPath[cur.r][cur.c] = true;
        bool moved = false;
        for (const Position& nb : neighbors(grid, cur.r, cur.c)) {
            if (isWall(grid, nb)) continue;
            if (dist[nb.r][nb.c] == dist[cur.r][cur.c] - 1) {
                cur = nb;
                moved = true;
                break;
            }
        }
        if (!moved) break;
    }
}

static void printMaze(const vector<string>& grid,
    const vector<vector<int>>& dist,
    Position start, Position end, int bestDist)
{
    int H = (int)grid.size();
    int maxW = maxWidth(grid);

    vector<vector<bool>> onPath(H);
    for (int r = 0; r < H; ++r) onPath[r].assign(grid[r].size(), false);

    if (bestDist >= 0)
        tracePath(grid, dist, start, end, onPath);

    auto indentRow = [&](int r) {
        return 2 * (maxW - (int)grid[r].size()) + 2;
        };
    auto indentSep = [&](int r) {
        return min(indentRow(r), indentRow(r + 1)) + 1;
        };
    auto cellChar = [&](int r, int c) -> char {
        if (r == start.r && c == start.c) return 'S';
        if (r == end.r && c == end.c)   return 'E';
        if (onPath[r][c])                 return 'x';
        return grid[r][c];
        };

    printHexBorder(indentRow(0) + 1, (int)grid[0].size(), 0);

    for (int r = 0; r < H; ++r) {
        cout << string(indentRow(r), ' ');
        for (int c = 0; c < (int)grid[r].size(); ++c)
            cout << "| " << cellChar(r, c) << " ";
        cout << "|\n";

        if (r < H - 1) {
            bool nextWider = (int)grid[r + 1].size() > (int)grid[r].size();
            int n = nextWider ? (int)grid[r + 1].size() : (int)grid[r].size();
            printHexBorder(indentSep(r), n, nextWider ? 0 : 1);
        }
    }

    printHexBorder(indentRow(H - 1) + 1, (int)grid[H - 1].size(), 1, false);
}

static int bfs(const vector<string>& grid, int maxW,
    Position start, Position end,
    vector<vector<int>>& dist)
{
    int H = (int)grid.size();
    dist.assign(H, {});
    for (int r = 0; r < H; ++r)
        dist[r].assign(grid[r].size(), -1);

    Queue q;
    q.insert(start.r * maxW + start.c);
    dist[start.r][start.c] = 0;

    while (!q.empty()) {
        int v = q.get(); q.remove();
        int r = v / maxW;
        int c = v % maxW;

        if (r == end.r && c == end.c) break;

        for (const Position& nb : neighbors(grid, r, c)) {
            if (isWall(grid, nb)) continue;
            if (dist[nb.r][nb.c] != -1) continue;
            dist[nb.r][nb.c] = dist[r][c] + 1;
            q.insert(nb.r * maxW + nb.c);
        }
    }
    return dist[end.r][end.c];
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    vector<string> grid = readGrid(argv[1]);
    int maxW = maxWidth(grid);

    Position start, end;
    findStartEnd(grid, start, end);

    vector<vector<int>> dist;
    int bestDist = bfs(grid, maxW, start, end, dist);

    if (bestDist == -1)
        cout << "No path found from S to E";
    else
        printMaze(grid, dist, start, end, bestDist);

    return 0;
}