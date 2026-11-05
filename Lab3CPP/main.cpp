#include <iostream>
#include <fstream>

#include "Lab3CPP.h"
#include "queue.h"

#include <utility>
#include <vector>

using namespace std;

bool solve_bfs(Maze& m) {
    if (m.sr < 0 || m.er < 0 || m.width <= 0) return false;

    const int k = (int)m.grid.size();
    const int W = m.width;

    auto enc = [W](int r, int c) { return r * W + c; };

    vector<vector<bool>>          visited(k);
    vector<vector<pair<int, int>>> parent(k);
    for (int r = 0; r < k; ++r) {
        visited[r].assign(m.grid[r].size(), false);
        parent[r].assign(m.grid[r].size(), { -1, -1 });
    }

    Queue* q = queue_create();
    queue_insert(q, enc(m.sr, m.sc));
    visited[m.sr][m.sc] = true;

    bool found = false;
    while (!queue_empty(q)) {
        int v = queue_get(q);
        queue_remove(q);
        int r = v / W, c = v % W;

        if (r == m.er && c == m.ec) { found = true; break; }

        const int Lprev = (r > 0) ? (int)m.grid[r - 1].size() : 0;
        const int Lcur = (int)m.grid[r].size();
        const int Lnext = (r < k - 1) ? (int)m.grid[r + 1].size() : 0;

        pair<int, int> nb[6];
        int cnt = 0;

        nb[cnt++] = { r, c - 1 };
        nb[cnt++] = { r, c + 1 };

        if (r > 0) {
            if (Lprev < Lcur) {
                nb[cnt++] = { r - 1, c - 1 };
                nb[cnt++] = { r - 1, c };
            }
            else {
                nb[cnt++] = { r - 1, c };
                nb[cnt++] = { r - 1, c + 1 };
            }
        }
        if (r < k - 1) {
            if (Lnext > Lcur) {
                nb[cnt++] = { r + 1, c };
                nb[cnt++] = { r + 1, c + 1 };
            }
            else {
                nb[cnt++] = { r + 1, c - 1 };
                nb[cnt++] = { r + 1, c };
            }
        }

        for (int i = 0; i < cnt; ++i) {
            int nr = nb[i].first, nc = nb[i].second;
            if (nr < 0 || nr >= k) continue;
            if (nc < 0 || nc >= (int)m.grid[nr].size()) continue;
            if (visited[nr][nc]) continue;
            if (m.grid[nr][nc] == '#') continue;

            visited[nr][nc] = true;
            parent[nr][nc] = { r, c };
            queue_insert(q, enc(nr, nc));
        }
    }
    queue_delete(q);

    if (found) {
        int r = m.er, c = m.ec;
        while (!(r == m.sr && c == m.sc)) {
            if (m.grid[r][c] != 'S' && m.grid[r][c] != 'E')
                m.grid[r][c] = 'x';
            auto p = parent[r][c];
            r = p.first;
            c = p.second;
        }
    }
    return found;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "При использовании файла: " << argv[0]
            << " произошла ошибка, Вы не указали входной файл" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    Maze m;
    if (!maze_read(m, input)) {
        std::cerr << "Invalid maze\n";
        return 1;
    }

    bool found = solve_bfs(m);

    if (!found) {
        cout << "Path not found\n";
    }

    maze_print(m);

    return 0;
}