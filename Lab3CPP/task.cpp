#include <fstream>
#include <iostream>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

constexpr int INF = 1000000000;
constexpr int END = -1;
constexpr int DR[4] = { -1, 1, 0, 0 };
constexpr int DC[4] = { 0, 0, -1, 1 };

static bool is_digit(int ch) { return ch >= '0' && ch <= '9'; }

static void relax(Queue* q, const Vector* grid, Vector* self_dist, const Vector* other_dist,
    Vector* near_d, bool from_x, int rows, int cols,
    int& best_dist, char& best_digit)
{
    queue_insert(q, END);

    while (!queue_empty(q))
    {
        int cur = queue_get(q);
        queue_remove(q);
        if (cur == END) return;

        size_t cur_i = static_cast<size_t>(cur);
        int nd = vector_get(self_dist, cur_i) + 1;
        int digit = vector_get(near_d, cur_i);
        int r = cur / cols, c = cur % cols;

        for (int k = 0; k < 4; ++k)
        {
            int nr = r + DR[k], nc = c + DC[k];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

            size_t nxt_i = static_cast<size_t>(nr * cols + nc);
            int ch = vector_get(grid, nxt_i);
            if (ch == '#' || vector_get(self_dist, nxt_i) <= nd) continue;

            vector_set(self_dist, nxt_i, nd);
            if (!from_x) vector_set(near_d, nxt_i, digit);

            int d_digit = from_x ? vector_get(near_d, nxt_i) : digit;
            int od = vector_get(other_dist, nxt_i);
            if (od < INF && nd + od < best_dist)
            {
                best_dist = nd + od;
                best_digit = static_cast<char>(d_digit);
            }

            if (!from_x || ch == '.') queue_insert(q, nr * cols + nc);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    ifstream fin(argv[1]);
    if (!fin.is_open()) return 1;

    string lines, line;
    int rows = 0, cols = 0;
    while (getline(fin, line))
    {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        if (cols == 0) cols = static_cast<int>(line.size());
        lines += line;
        ++rows;
    }
    if (rows == 0 || cols == 0) return 0;

    size_t n = static_cast<size_t>(rows) * static_cast<size_t>(cols);
    Vector* grid = vector_create();
    Vector* dist_x = vector_create();
    Vector* dist_d = vector_create();
    Vector* near_d = vector_create();
    vector_resize(grid, n);
    vector_resize(dist_x, n);
    vector_resize(dist_d, n);
    vector_resize(near_d, n);

    Queue* qx = queue_create();
    Queue* qd = queue_create();
    int start = -1;

    for (size_t i = 0; i < n; ++i)
    {
        int ch = static_cast<unsigned char>(lines[i]);
        vector_set(grid, i, ch);
        vector_set(dist_x, i, INF);
        vector_set(dist_d, i, INF);
        vector_set(near_d, i, 0);

        int idx = static_cast<int>(i);
        if (ch == 'X') start = idx;
        if (is_digit(ch))
        {
            vector_set(dist_d, i, 0);
            vector_set(near_d, i, ch);
            queue_insert(qd, idx);
        }
    }

    if (start != -1)
    {
        vector_set(dist_x, static_cast<size_t>(start), 0);
        queue_insert(qx, start);

        int best_dist = INF;
        char best_digit = 0;

        while (!queue_empty(qx) && !queue_empty(qd) && best_dist == INF)
        {
            relax(qx, grid, dist_x, dist_d, near_d, true, rows, cols, best_dist, best_digit);
            relax(qd, grid, dist_d, dist_x, near_d, false, rows, cols, best_dist, best_digit);
        }
        if (best_dist != INF) cout << best_digit << '\n';
    }

    queue_delete(qx);
    queue_delete(qd);
    vector_delete(near_d);
    vector_delete(dist_d);
    vector_delete(dist_x);
    vector_delete(grid);
    return 0;
}