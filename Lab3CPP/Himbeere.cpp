#include "Himbeere.h"
#include "queue.h"
#include <vector>
#include <string>
#include <algorithm>

std::string solve_hex_maze(const std::vector<std::string>& maze) {
    int rows = static_cast<int>(maze.size());
    if (rows == 0) return "No path";
    int cols = 0;
    for (const auto& row : maze) cols = std::max(cols, static_cast<int>(row.size()));

    int sr = -1, sc = -1, fr = -1, fc = -1;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < static_cast<int>(maze[r].size()); ++c) {
            if (maze[r][c] == 'S') { sr = r; sc = c; }
            if (maze[r][c] == 'E') { fr = r; fc = c; }
        }
    }
    if (sr == -1 || fr == -1) return "No path";

    int dr[] = { -1, -1, 0, 0, 1, 1 };
    int dc_e[] = { -1, 0, -1, 1, 0, 1 };
    int dc_o[] = { 0, 1, -1, 1, -1, 0 };

    std::vector<std::vector<int>> pr_m(rows, std::vector<int>(cols, -1));
    std::vector<std::vector<int>> pc_m(rows, std::vector<int>(cols, -1));
    std::vector<std::vector<int>> vis_s(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> vis_f(rows, std::vector<int>(cols, 0));

    Queue* q_s = queue_create();
    Queue* q_f = queue_create();
    queue_insert(q_s, sr * cols + sc); vis_s[sr][sc] = 1;
    queue_insert(q_f, fr * cols + fc); vis_f[fr][fc] = 1;

    int mr = -1, mc = -1;
    bool found = (sr == fr && sc == fc);

    while (!queue_empty(q_s) && !queue_empty(q_f) && !found) {
        int curr = queue_get(q_s); queue_remove(q_s);
        int r = curr / cols, c = curr % cols;
        int* dc = (r % 2 == 0) ? dc_e : dc_o;
        for (int i = 0; i < 6; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < static_cast<int>(maze[nr].size()) && maze[nr][nc] != '#' && !vis_s[nr][nc]) {
                vis_s[nr][nc] = 1;
                pr_m[nr][nc] = r; pc_m[nr][nc] = c;
                queue_insert(q_s, nr * cols + nc);
                if (vis_f[nr][nc]) { mr = nr; mc = nc; found = true; break; }
            }
        }
        if (found) break;
        curr = queue_get(q_f); queue_remove(q_f);
        r = curr / cols; c = curr % cols;
        dc = (r % 2 == 0) ? dc_e : dc_o;
        for (int i = 0; i < 6; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < static_cast<int>(maze[nr].size()) && maze[nr][nc] != '#' && !vis_f[nr][nc]) {
                vis_f[nr][nc] = 1;
                queue_insert(q_f, nr * cols + nc);
            }
        }
    }

    queue_delete(q_s);
    queue_delete(q_f);
    if (!found) return "No path";

    auto solved = maze;
    if (!(sr == fr && sc == fc)) {
        int r = mr, c = mc;
        while (!(r == sr && c == sc)) {
            if (solved[r][c] != 'S' && solved[r][c] != 'E') solved[r][c] = 'x';
            int pr = pr_m[r][c], pc = pc_m[r][c];
            if (pr == -1 || pc == -1) break;
            r = pr; c = pc;
        }
    }

    std::string res = "Path found\n";
    std::string roof = "     ";
    for (int j = 0; j < static_cast<int>(solved[0].size()); ++j) roof += "/ \\ ";
    res += roof + "\n";

    for (int i = 0; i < rows; ++i) {
        int row_size = static_cast<int>(solved[i].size());
        std::string row_str = (i % 2 == 0) ? "    |" : "  |";
        for (int j = 0; j < row_size; ++j)
            row_str += " " + std::string(1, solved[i][j]) + " |";
        res += row_str + "\n";

        if (i + 1 < rows) {
            int next_size = static_cast<int>(solved[i + 1].size());
            int segs = std::max(row_size, next_size);
            std::string floor = "   ";
            std::string pat = (i % 2 == 0) ? "/ \\ " : "\\ / ";
            for (int j = 0; j < segs; ++j) floor += pat;
            if (!floor.empty() && floor.back() == ' ') floor.pop_back();
            floor += (i % 2 == 0) ? " /" : " \\";
            res += floor + "\n";
        }
    }

    int last_row = rows - 1;
    int bottom_size = static_cast<int>(solved[last_row].size());
    std::string bottom = (last_row % 2 == 0) ? "     " : "   ";
    std::string bottom_pattern = (last_row % 2 == 0) ? "\\ / " : "\\ / ";
    for (int j = 0; j < bottom_size; ++j) bottom += bottom_pattern;
    res += bottom + "\n";

    return res;
}