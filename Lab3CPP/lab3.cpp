#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "queue.h"

// координаты клетки в сетке
struct Position {
    int r;
    int c;
    Position(int rr = -1, int cc = -1) : r(rr), c(cc) {}
    bool operator==(const Position &o) const { return r == o.r && c == o.c; }
    bool operator!=(const Position &o) const { return !(*this == o); }
};

// соседи в гексагональной сетке (even-r offset)
static std::vector<Position> getNeighbors(int r, int c, int H,
                                          const std::vector<std::vector<char>> &grid) {
    static const int dirs[2][6][2] = {
        // чётный ряд
        {{-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}},
        // нечётный ряд
        {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}}
    };
    std::vector<Position> res;
    int parity = r & 1;
    for (int i = 0; i < 6; ++i) {
        int nr = r + dirs[parity][i][0];
        int nc = c + dirs[parity][i][1];
        if (nr < 0 || nr >= H) continue;
        if (nc < 0 || nc >= (int)grid[nr].size()) continue;
        res.push_back(Position(nr, nc));
    }
    return res;
}

// встречный BFS: гоняем две очереди с двух концов, пока волны не пересекутся
static Position bidirectionalBFS(const std::vector<std::vector<char>> &grid,
                                 int H, int maxW,
                                 Position start, Position end,
                                 std::vector<std::vector<int>> &distS,
                                 std::vector<std::vector<int>> &distE) {
    auto encode = [maxW](int r, int c) { return r * maxW + c; };
    auto decode = [maxW](int v, int &r, int &c) { r = v / maxW; c = v % maxW; };

    distS.assign(H, std::vector<int>(maxW, -1));
    distE.assign(H, std::vector<int>(maxW, -1));

    Queue qS, qE;

    qS.insert(encode(start.r, start.c));
    distS[start.r][start.c] = 0;

    qE.insert(encode(end.r, end.c));
    distE[end.r][end.c] = 0;

    // если S и E совпали, то сразу выходим, иначе BFS найдёт «путь» длиной 0 не там
    if (start == end) return start;

    while (!qS.empty() && !qE.empty()) {
        // шаг из старта
        {
            int v = qS.get(); qS.remove();
            int r, c; decode(v, r, c);
            for (const Position &nb : getNeighbors(r, c, H, grid)) {
                if (grid[nb.r][nb.c] == '#') continue;
                if (distS[nb.r][nb.c] != -1) continue;
                distS[nb.r][nb.c] = distS[r][c] + 1;
                qS.insert(encode(nb.r, nb.c));
                // как только сосед уже помечен с другой стороны, волны встретились
                if (distE[nb.r][nb.c] != -1) return nb;
            }
        }

        // шаг из финиша
        {
            int v = qE.get(); qE.remove();
            int r, c; decode(v, r, c);
            for (const Position &nb : getNeighbors(r, c, H, grid)) {
                if (grid[nb.r][nb.c] == '#') continue;
                if (distE[nb.r][nb.c] != -1) continue;
                distE[nb.r][nb.c] = distE[r][c] + 1;
                qE.insert(encode(nb.r, nb.c));
                if (distS[nb.r][nb.c] != -1) return nb;
            }
        }
    }

    return Position(-1, -1);
}

// восстанавливаем путь как две половины: от meet до start по distS
static std::vector<std::vector<bool>> reconstructPath(
        const std::vector<std::vector<char>> &grid,
        int H,
        Position start, Position end, Position meet,
        const std::vector<std::vector<int>> &distS,
        const std::vector<std::vector<int>> &distE) {

    std::vector<std::vector<bool>> onPath(H);
    for (int r = 0; r < H; ++r) onPath[r].assign(grid[r].size(), false);

    // первая половина: meet -> start
    Position cur = meet;
    while (!(cur == start)) {
        onPath[cur.r][cur.c] = true;  // включая meet
        bool moved = false;
        for (const Position &nb : getNeighbors(cur.r, cur.c, H, grid)) {
            if (distS[nb.r][nb.c] == distS[cur.r][cur.c] - 1) {
                cur = nb;
                moved = true;
                break;
            }
        }
        if (!moved) break;  // защита от зацикливания
    }

    // вторая половина: meet -> end
    cur = meet;
    while (!(cur == end)) {
        onPath[cur.r][cur.c] = true;  // включая meet
        bool moved = false;
        for (const Position &nb : getNeighbors(cur.r, cur.c, H, grid)) {
            if (distE[nb.r][nb.c] == distE[cur.r][cur.c] - 1) {
                cur = nb;
                moved = true;
                break;
            }
        }
        if (!moved) break;
    }

    return onPath;
}

// печать гексагональной сетки
static void printMaze(const std::vector<std::vector<char>> &grid,
                      const Position &start, const Position &end,
                      const std::vector<std::vector<bool>> &onPath) {
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

    std::vector<std::vector<char>> grid;
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
    std::vector<std::vector<int>> distS, distE;
    Position meet = bidirectionalBFS(grid, H, maxW, start, end, distS, distE);

    if (meet.r == -1) {
        std::cout << "No path found from S to E" << std::endl;
        return 0;
    }

    // восстановление пути
    std::vector<std::vector<bool>> onPath =
        reconstructPath(grid, H, start, end, meet, distS, distE);

    printMaze(grid, start, end, onPath);

    return 0;
}