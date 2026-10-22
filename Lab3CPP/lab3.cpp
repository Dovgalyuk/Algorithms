#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "queue.h"

typedef std::vector<std::vector<char>> MazeGrid; // входной лабиринт
typedef std::vector<std::vector<int>>  DistGrid; // массив расстояний (используется для distS и distE)
typedef std::vector<std::vector<bool>> PathGrid; // отметки клеток пути

// координаты клетки в сетке
struct Position {
    int r;
    int c;
    Position(int rr = -1, int cc = -1) : r(rr), c(cc) {}
    bool operator==(const Position &o) const { return r == o.r && c == o.c; }
    bool operator!=(const Position &o) const { return !(*this == o); }
};

// соседи в гексагональной сетке
// левый/правый: всегда в той же строке
// верхний/нижний: если соседняя строка не короче нашей, то
// граничат (nr, c) и (nr, c+1); если короче — (nr, c-1) и (nr, c).
static std::vector<Position> getNeighbors(int r, int c, int H,
                                          const MazeGrid &grid) {
    std::vector<Position> res;

    if (c - 1 >= 0) res.push_back(Position(r, c - 1));
    if (c + 1 < (int)grid[r].size()) res.push_back(Position(r, c + 1));

    for (int dr : {-1, 1}) {
        int nr = r + dr;
        if (nr < 0 || nr >= H) continue;

        if ((int)grid[nr].size() >= (int)grid[r].size()) {
            if (c < (int)grid[nr].size())
                res.push_back(Position(nr, c));
            if (c + 1 < (int)grid[nr].size())
                res.push_back(Position(nr, c + 1));
        } else {
            if (c - 1 >= 0 && c - 1 < (int)grid[nr].size())
                res.push_back(Position(nr, c - 1));
            if (c < (int)grid[nr].size())
                res.push_back(Position(nr, c));
        }
    }

    return res;
}

// один шаг BFS из очереди q по массиву dist
// если сосед уже помечен в otherDist — волны встретились, возвращаем его
static Position bfsStep(Queue &q,
                        DistGrid &dist,
                        const DistGrid &otherDist,
                        const MazeGrid &grid,
                        int H, int maxW) {
    int v = q.get(); q.remove();
    int r = v / maxW;
    int c = v % maxW;

    for (const Position &nb : getNeighbors(r, c, H, grid)) {
        if (grid[nb.r][nb.c] == '#') continue;
        if (dist[nb.r][nb.c] != -1) continue;
        dist[nb.r][nb.c] = dist[r][c] + 1;
        q.insert(nb.r * maxW + nb.c);
        if (otherDist[nb.r][nb.c] != -1) return nb;
    }
    return Position(-1, -1);
}

// встречный BFS: гоняем две очереди с двух концов, пока волны не пересекутся
static Position bidirectionalBFS(const MazeGrid &grid,
                                 int H, int maxW,
                                 Position start, Position end,
                                 DistGrid &distS,
                                 DistGrid &distE) {

    distS.assign(H, std::vector<int>(maxW, -1));
    distE.assign(H, std::vector<int>(maxW, -1));

    Queue qS, qE;

    qS.insert(start.r * maxW + start.c);
    distS[start.r][start.c] = 0;

    qE.insert(end.r * maxW + end.c);
    distE[end.r][end.c] = 0;

    // S и E совпадают — путь длины 0
    if (start == end) return start;

    while (!qS.empty() && !qE.empty()) {
        Position meet = bfsStep(qS, distS, distE, grid, H, maxW);
        if (meet.r != -1) return meet;

        meet = bfsStep(qE, distE, distS, grid, H, maxW);
        if (meet.r != -1) return meet;
    }

    return Position(-1, -1);
}

// обход от from к to по убыванию dist, отметка клеток на пути
static void traceBack(Position from, Position to,
                      const DistGrid &dist,
                      PathGrid &onPath,
                      const MazeGrid &grid,
                      int H) {
    Position cur = from;
    while (!(cur == to)) {
        onPath[cur.r][cur.c] = true;
        bool moved = false;
        for (const Position &nb : getNeighbors(cur.r, cur.c, H, grid)) {
            if (dist[nb.r][nb.c] == dist[cur.r][cur.c] - 1) {
                cur = nb;
                moved = true;
                break;
            }
        }
        if (!moved) break;
    }
}


// восстанавливаем путь: от meet к start по distS и от meet к end по distE
static PathGrid reconstructPath(
        const MazeGrid &grid,
        int H,
        Position start, Position end, Position meet,
        const DistGrid &distS,
        const DistGrid &distE) {

    PathGrid onPath(H);

    for (int r = 0; r < H; ++r) onPath[r].assign(grid[r].size(), false);

    traceBack(meet, start, distS, onPath, grid, H);
    traceBack(meet, end, distE, onPath, grid, H);

    return onPath;
}

// печать гексагональной сетки
static void printMaze(const MazeGrid &grid,
                      const Position &start, const Position &end,
                      const PathGrid &onPath) {
    int H = (int)grid.size();
    int maxW = 0;
    for (const auto &row : grid) maxW = std::max(maxW, (int)row.size());

    auto indentRow = [&](int r) {
        return 2 * (maxW - (int)grid[r].size()) + 2;
    };
    auto indentSep = [&](int r) {
        return std::min(indentRow(r), indentRow(r + 1)) + 1;
    };

    auto cellChar = [&](int r, int c) -> char {
        if (r == start.r && c == start.c) return 'S';
        if (r == end.r && c == end.c)     return 'E';
        if (onPath[r][c])                 return 'x';
        if (grid[r][c] == '#')            return '#';
        if (grid[r][c] == '.')            return '.';
        return ' ';
    };

    // верхняя граница
    std::cout << std::string(indentRow(0) + 1, ' ');
    for (int j = 0; j < (int)grid[0].size(); ++j) {
        if (j > 0) std::cout << " ";
        std::cout << "/ \\";
    }
    std::cout << "\n";

    // ряды + разделители между ними
    for (int r = 0; r < H; ++r) {
        // Ячейки
        std::cout << std::string(indentRow(r), ' ');
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            std::cout << "| " << cellChar(r, c) << " ";
        }
        std::cout << "|\n";

        // разделитель
        if (r < H - 1) {
            std::cout << std::string(indentSep(r), ' ');

            bool nextWider = (int)grid[r + 1].size() > (int)grid[r].size();
            if (nextWider) {
                // следующий ряд шире — разделитель " / \ / \ ..." (без пробела после последнего)
                for (int j = 0; j < (int)grid[r + 1].size(); ++j) {
                    if (j > 0) std::cout << " ";
                    std::cout << "/ \\";
                }
            } else {
                // следующий ряд не шире — разделитель " \ / \ / ..." (без пробела после последнего)
                for (int j = 0; j < (int)grid[r].size(); ++j) {
                    if (j > 0) std::cout << " ";
                    std::cout << "\\ /";
                }
            }
            std::cout << "\n";
        }
    }

    // нижняя граница
    std::cout << std::string(indentRow(H - 1) + 1, ' ');
    for (int j = 0; j < (int)grid[H - 1].size(); ++j) {
        if (j > 0) std::cout << " ";
        std::cout << "\\ /";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) lines.push_back(line);
    }
    input.close();

    if (lines.empty()) {
        std::cerr << "Error: empty input" << std::endl;
        return 1;
    }

    MazeGrid grid;
    for (const auto &s : lines) grid.emplace_back(s.begin(), s.end());

    int H = (int)grid.size();
    int maxW = 0;
    for (const auto &row : grid) maxW = std::max(maxW, (int)row.size());

    // поиск S и E
    Position start(-1, -1), end(-1, -1);
    for (int r = 0; r < H; ++r)
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            if (grid[r][c] == 'S') start = Position(r, c);
            if (grid[r][c] == 'E') end = Position(r, c);
        }

    if (start.r == -1 || end.r == -1) {
        std::cerr << "Error: maze must contain S and E" << std::endl;
        return 1;
    }

    // встречный BFS
    DistGrid distS, distE;
    Position meet = bidirectionalBFS(grid, H, maxW, start, end, distS, distE);

    if (meet.r == -1) {
        std::cout << "No path found from S to E" << std::endl;
        return 0;
    }

    // восстановление пути
    PathGrid onPath = reconstructPath(grid, H, start, end, meet, distS, distE);

    printMaze(grid, start, end, onPath);

    return 0;
}