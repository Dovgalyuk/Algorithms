#include "Himbeere.h"
#include "queue.h"
#include <vector>

std::string solve_hex_maze(const std::vector<std::string>& maze) {
    int rows = static_cast<int>(maze.size());
    if (rows == 0) return "No path";
    int cols = static_cast<int>(maze.front().size());

    int start_r = -1, start_c = -1, finish_r = -1, finish_c = -1;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (maze[r][c] == 'S') { start_r = r; start_c = c; }
            if (maze[r][c] == 'E') { finish_r = r; finish_c = c; }
        }
    }

    if (start_r == -1 || finish_r == -1) return "No path";
    if (start_r == finish_r && start_c == finish_c) return "Path found";

    int dr[] = { -1, -1,  0,  0,  1,  1 };
    int dc_even[] = { -1,  0, -1,  1,  0,  1 };
    int dc_odd[] = { 0,  1, -1,  1, -1,  0 };

    std::vector<std::vector<int>> visited_s(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> visited_f(rows, std::vector<int>(cols, 0));

    Queue* q_s = queue_create();
    Queue* q_f = queue_create();

    queue_insert(q_s, start_r * cols + start_c);
    visited_s[start_r][start_c] = 1;
    queue_insert(q_f, finish_r * cols + finish_c);
    visited_f[finish_r][finish_c] = 1;

    bool found = false;

    while (!queue_empty(q_s) && !queue_empty(q_f) && !found) {
        auto step = [&](Queue* q, auto& vis, auto& opp_vis) {
            int curr = queue_get(q);
            queue_remove(q);
            int r = curr / cols, c = curr % cols;
            int* dc = (r % 2 == 0) ? dc_even : dc_odd;

            for (int i = 0; i < 6; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != '#') {
                    if (opp_vis[nr][nc] > 0) return true;
                    if (vis[nr][nc] == 0) {
                        vis[nr][nc] = 1;
                        queue_insert(q, nr * cols + nc);
                    }
                }
            }
            return false;
            };

        if (step(q_s, visited_s, visited_f) || step(q_f, visited_f, visited_s)) {
            found = true;
            break;
        }
    }

    queue_delete(q_s);
    queue_delete(q_f);

    return found ? "Path found" : "No path";
}