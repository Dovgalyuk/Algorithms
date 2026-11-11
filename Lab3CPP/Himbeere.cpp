#include "Himbeere.h"
#include "queue.h"
#include <vector>
#include <string>
#include <algorithm>

namespace {

    const int DR[6] = { -1, -1, 0, 0, 1, 1 };
    const int DC_E[6] = { 0,  1, -1, 1, 0, 1 };
    const int DC_O[6] = { -1,  0, -1, 1, -1, 0 };

    std::string render(const std::vector<std::string>& m)
    {
        int rows = static_cast<int>(m.size());
        size_t cols = 0;
        for (const auto& r : m) cols = std::max(cols, r.size());

        size_t width = 4 * cols + 6;
        std::vector<std::string> canvas(2 * rows + 1, std::string(width, ' '));

        for (int i = 0; i < rows; ++i) {
            for (size_t j = 0; j < m[i].size(); ++j) {
                size_t x = (i % 2 == 0 ? 4 : 2) + 4 * j;
                canvas[2 * i][x + 1] = '/';
                canvas[2 * i][x + 3] = '\\';
                canvas[2 * i + 1][x] = '|';
                canvas[2 * i + 1][x + 2] = m[i][j];
                canvas[2 * i + 1][x + 4] = '|';
                canvas[2 * i + 2][x + 1] = '\\';
                canvas[2 * i + 2][x + 3] = '/';
            }
        }

        std::string res;
        for (auto& line : canvas) {
            while (!line.empty() && line.back() == ' ') line.pop_back();
            res += line + "\n";
        }
        return res;
    }

}

std::string solve_hex_maze(const std::vector<std::string>& maze)
{
    int rows = static_cast<int>(maze.size());
    if (rows == 0) return "No path";
    int cols = 0;
    for (const auto& row : maze) cols = std::max(cols, static_cast<int>(row.size()));

    int s = -1, f = -1;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < static_cast<int>(maze[r].size()); ++c) {
            if (maze[r][c] == 'S') s = r * cols + c;
            if (maze[r][c] == 'E') f = r * cols + c;
        }
    if (s == -1 || f == -1) return "No path";

    const int N = rows * cols;

    std::vector<int> dist[2] = { std::vector<int>(N, -1), std::vector<int>(N, -1) };
    std::vector<int> par[2] = { std::vector<int>(N, -1), std::vector<int>(N, -1) };
    Queue* q[2] = { queue_create(), queue_create() };

    dist[0][s] = 0; queue_insert(q[0], s);
    dist[1][f] = 0; queue_insert(q[1], f);

    const int INF = 1 << 30;
    int best = INF, meetA = -1, meetB = -1, meetSide = -1;

    int side = 0;
    while (!queue_empty(q[0]) && !queue_empty(q[1]) && best == INF) {
        int other = 1 - side;
        int level = dist[side][queue_get(q[side])];
        while (!queue_empty(q[side]) && dist[side][queue_get(q[side])] == level) {
            int cur = queue_get(q[side]);
            queue_remove(q[side]);
            int r = cur / cols, c = cur % cols;
            const int* dc = (r % 2 == 0) ? DC_E : DC_O;
            for (int i = 0; i < 6; ++i) {
                int nr = r + DR[i], nc = c + dc[i];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= static_cast<int>(maze[nr].size())) continue;
                if (maze[nr][nc] == '#') continue;
                int nxt = nr * cols + nc;
                if (dist[other][nxt] != -1) {
                    int cand = dist[side][cur] + 1 + dist[other][nxt];
                    if (cand < best) { best = cand; meetA = cur; meetB = nxt; meetSide = side; }
                }
                if (dist[side][nxt] == -1) {
                    dist[side][nxt] = dist[side][cur] + 1;
                    par[side][nxt] = cur;
                    queue_insert(q[side], nxt);
                }
            }
        }
        side = other;
    }

    queue_delete(q[0]);
    queue_delete(q[1]);
    if (best == INF) return "No path";

    auto solved = maze;
    auto mark = [&](int idx) {
        int r = idx / cols, c = idx % cols;
        if (solved[r][c] != 'S' && solved[r][c] != 'E') solved[r][c] = 'x';
        };
    for (int v = meetA; v != -1; v = par[meetSide][v]) mark(v);
    for (int v = meetB; v != -1; v = par[1 - meetSide][v]) mark(v);

    return render(solved);
}
