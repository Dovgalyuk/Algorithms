#include "Himbeere.h"
#include "queue.h"
#include <vector>
#include <string>

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

    int dr[] = { -1, -1,  0,  0,  1,  1 };
    int dc_even[] = { -1,  0, -1,  1,  0,  1 };
    int dc_odd[] = { 0,  1, -1,  1, -1,  0 };

    std::vector<std::vector<int>> parent_r(rows, std::vector<int>(cols, -1));
    std::vector<std::vector<int>> parent_c(rows, std::vector<int>(cols, -1));
    std::vector<std::vector<int>> visited_s(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> visited_f(rows, std::vector<int>(cols, 0));

    Queue* q_s = queue_create();
    Queue* q_f = queue_create();

    queue_insert(q_s, start_r * cols + start_c);
    visited_s[start_r][start_c] = 1;
    queue_insert(q_f, finish_r * cols + finish_c);
    visited_f[finish_r][finish_c] = 1;

    int meet_r = -1, meet_c = -1;
    bool found = (start_r == finish_r && start_c == finish_c);

    while (!queue_empty(q_s) && !queue_empty(q_f) && !found) {
        int curr_s = queue_get(q_s);
        queue_remove(q_s);
        int r_s = curr_s / cols, c_s = curr_s % cols;
        int* dc_s = (r_s % 2 == 0) ? dc_even : dc_odd;

        for (int i = 0; i < 6; ++i) {
            int nr = r_s + dr[i], nc = c_s + dc_s[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != '#') {
                if (visited_s[nr][nc] == 0) {
                    visited_s[nr][nc] = 1;
                    parent_r[nr][nc] = r_s;
                    parent_c[nr][nc] = c_s;
                    queue_insert(q_s, nr * cols + nc);
                    if (visited_f[nr][nc] > 0) {
                        meet_r = nr;
                        meet_c = nc;
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found) break;

        int curr_f = queue_get(q_f);
        queue_remove(q_f);
        int r_f = curr_f / cols, c_f = curr_f % cols;
        int* dc_f = (r_f % 2 == 0) ? dc_even : dc_odd;

        for (int i = 0; i < 6; ++i) {
            int nr = r_f + dr[i], nc = c_f + dc_f[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && maze[nr][nc] != '#') {
                if (visited_f[nr][nc] == 0) {
                    visited_f[nr][nc] = 1;
                    queue_insert(q_f, nr * cols + nc);
                }
            }
        }
    }

    queue_delete(q_s);
    queue_delete(q_f);

    std::vector<std::string> solved_maze = maze;
    if (found && !(start_r == finish_r && start_c == finish_c)) {
        int curr_r = meet_r, curr_c = meet_c;
        while (!(curr_r == start_r && curr_c == start_c)) {
            if (solved_maze[curr_r][curr_c] != 'S' && solved_maze[curr_r][curr_c] != 'E') {
                solved_maze[curr_r][curr_c] = 'x';
            }
            int pr = parent_r[curr_r][curr_c];
            int pc = parent_c[curr_r][curr_c];
            if (pr == -1 || pc == -1) break;
            curr_r = pr;
            curr_c = pc;
        }
    }

    if (!found) return "No path";

    std::string result = "Path found\n";
    int width = cols;

    std::string roof = "   ";
    for (int j = 0; j < width; ++j) roof += "/ \\ ";
    result += roof + "\n";

    for (int i = 0; i < rows; ++i) {
        std::string row_str = "  ";
        if (i % 2 == 1) row_str = " ";

        row_str += "|";
        for (int j = 0; j < width; ++j) {
            row_str += " " + std::string(1, solved_maze[i][j]) + " |";
        }
        result += row_str + "\n";

        if (i + 1 < rows) {
            std::string floor = "   ";
            for (int j = 0; j < width; ++j) floor += "\\ / ";
            result += floor + "\n";
        }
    }

    std::string bottom = "   ";
    for (int j = 0; j < width; ++j) bottom += "\\ / ";
    result += bottom + "\n";

    return result;
}