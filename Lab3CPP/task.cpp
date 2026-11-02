#include <cstring>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue.h"

#define MAXD 32
#define MAXH 128
#define MAXW 128

struct Maze
{
    int W, H, D;
    char grid[MAXD][MAXH][MAXW];
};

static int in_bounds(const Maze* m, int x, int y, int z)
{
    return x >= 0 && x < m->W && y >= 0 && y < m->H && z >= 0 && z < m->D;
}

static int passable(const Maze* m, int x, int y, int z)
{
    if (!in_bounds(m, x, y, z)) return 0;
    return m->grid[z][y][x] != '#';
}

static const int DX[6] = { 1, -1,  0,  0,  0,  0 };
static const int DY[6] = { 0,  0,  1, -1,  0,  0 };
static const int DZ[6] = { 0,  0,  0,  0,  1, -1 };

static int read_maze(const char* fname, Maze* m)
{
    std::ifstream f(fname);
    if (!f.is_open()) return 0;

    m->W = m->H = m->D = 0;
    std::string line;
    int z = 0, y = 0, maxW = 0;

    while (std::getline(f, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        size_t len = line.size();

        if (len == 0) {
            if (y > 0) {
                if (y > m->H) m->H = y;
                if (maxW > m->W) m->W = maxW;
                z++;
                y = 0;
            }
            continue;
        }

        if (z >= MAXD || y >= MAXH) return 0;
        if (len >= MAXW) return 0;

        memcpy(m->grid[z][y], line.data(), len);
        m->grid[z][y][len] = 0;
        if ((int)len > maxW) maxW = (int)len;
        y++;
    }

    if (y > 0) {
        if (y > m->H) m->H = y;
        if (maxW > m->W) m->W = maxW;
        z++;
    }
    m->D = z;
    return m->D > 0 && m->W > 0 && m->H > 0;
}

static void bfs_step(const Maze* m, Queue* q, int* dist, const int* other_dist, int* goal_id, bool is_goal_side, int* best_dist, int* best_digit)
{
    if (queue_empty(q)) return;

    int cur = queue_get(q);
    queue_remove(q);

    int cx = cur % m->W;
    int cy = (cur / m->W) % m->H;
    int cz = cur / (m->W * m->H);
    int cd = dist[cur];

    if (cd >= *best_dist) return;

    for (int k = 0; k < 6; k++) {
        int nx = cx + DX[k];
        int ny = cy + DY[k];
        int nz = cz + DZ[k];
        if (!passable(m, nx, ny, nz)) continue;
        int nidx = (nz * m->H + ny) * m->W + nx;

        if (dist[nidx] == -1) {
            dist[nidx] = cd + 1;
            if (is_goal_side) {
                goal_id[nidx] = goal_id[cur];
            }
            queue_insert(q, nidx);
        }
        else if (is_goal_side && dist[nidx] == cd + 1) {
            if (goal_id[cur] < goal_id[nidx]) {
                goal_id[nidx] = goal_id[cur];
            }
        }

        if (other_dist[nidx] != -1) {
            int total = dist[nidx] + other_dist[nidx];
            int digit = goal_id[nidx];
            if (digit >= 0 && (total < *best_dist || (total == *best_dist && digit < *best_digit))) {
                *best_dist = total;
                *best_digit = digit;
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) return 1;

    static Maze m;
    if (!read_maze(argv[1], &m)) return 1;

    int sx = -1, sy = -1, sz = -1;
    for (int z = 0; z < m.D; z++)
        for (int y = 0; y < m.H; y++)
            for (int x = 0; x < m.W; x++)
                if (m.grid[z][y][x] == 'X') { sx = x; sy = y; sz = z; }

    if (sx < 0) return 1;

    size_t cells = (size_t)m.W * m.H * m.D;
    std::vector<int> dist_start(cells, -1);
    std::vector<int> dist_goal(cells, -1);
    std::vector<int> goal_id(cells, -1);

    Queue* qs = queue_create();
    Queue* qg = queue_create();

    int sidx = (sz * m.H + sy) * m.W + sx;
    dist_start[sidx] = 0;
    queue_insert(qs, sidx);

    for (int z = 0; z < m.D; z++)
        for (int y = 0; y < m.H; y++)
            for (int x = 0; x < m.W; x++) {
                char c = m.grid[z][y][x];
                if (c >= '0' && c <= '9') {
                    int idx = (z * m.H + y) * m.W + x;
                    if (dist_goal[idx] == -1) {
                        dist_goal[idx] = 0;
                        goal_id[idx] = c - '0';
                        queue_insert(qg, idx);
                    }
                }
            }

    int best_dist = INT_MAX;
    int best_digit = -1;

    while (!queue_empty(qs) && !queue_empty(qg)) {
        bfs_step(&m, qs, dist_start.data(), dist_goal.data(), goal_id.data(), false, &best_dist, &best_digit);
        bfs_step(&m, qg, dist_goal.data(), dist_start.data(), goal_id.data(), true, &best_dist, &best_digit);
    }

    if (best_digit < 0) {
        std::cout << "no reachable goal\n";
    }
    else {
        std::cout << best_digit << "\n";
    }

    queue_delete(qs);
    queue_delete(qg);
    return 0;
}