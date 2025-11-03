#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "queue.h"

using namespace std;

using Cell = pair<int, int>;
using Cells = vector<Cell>;
using Grid = vector<string>;

// Функция для чтения прямоугольной сетки из файла.

static bool read_grid(const string& filename, Grid& g) {
    ifstream in(filename);
    if (!in.is_open())
        return false;

    string s;
    while (getline(in, s)) {
        if (!s.empty() && s.back() == '\r')
            s.pop_back();
        if (!s.empty())
            g.push_back(s);
    }

    return !g.empty();
}

// Функция для печати сетки в виде шестиугольной (соты).

static void print_hex(const Grid& g) {
    size_t H = g.size();
    size_t W = H ? g[0].size() : 0;
    if (!H || !W)
        return;

    for (size_t c = 0; c < W; ++c)
        cout << " / \\";
    cout << "\n";

    for (size_t r = 0; r < H; ++r) {
        cout << string(2 * r, ' ');
        for (size_t c = 0; c < W; ++c)
            cout << "| " << (g[r][c] == '.' ? ' ' : g[r][c]) << ' ';
        cout << "|\n";

        cout << string(2 * r, ' ');
        for (size_t c = 0; c < W; ++c)
            cout << " \\ /";
        if (r < H - 1)
            cout << " \\";
        cout << "\n";
    }
}

// Функция для получения списка соседей клетки в шестиугольной решётке.

static void neighbors(int r, int c, size_t H, size_t W, Cells& out) {
    out.clear();
    auto push = [&](int rr, int cc) {
        if (rr >= 0 && cc >= 0 && (size_t)rr < H && (size_t)cc < W)
            out.push_back({ rr, cc });
    };

    push(r - 1, c - 1);
    push(r - 1, c);

    push(r, c - 1);
    push(r, c + 1);

    push(r + 1, c - 1);
    push(r + 1, c);
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        return 0;

    Grid g;
    if (!read_grid(argv[1], g))
        return 0;

    size_t H = g.size();
    size_t W = g[0].size();

    for (size_t r = 1; r < H; ++r)
        if (g[r].size() != W)
            return 0;

    int sr = -1, sc = -1, er = -1, ec = -1;

    for (size_t r = 0; r < H; ++r) {
        for (size_t c = 0; c < W; ++c) {
            if (g[r][c] == 'S') {
                sr = (int)r;
                sc = (int)c;
            }
            if (g[r][c] == 'E') {
                er = (int)r;
                ec = (int)c;
            }
        }
    }

    if (sr < 0 || er < 0) {
        print_hex(g);
        return 0;
    }

    int Wi = (int)W;
    auto id = [Wi](int r, int c) { return r * Wi + c; };
    auto rid = [Wi](int id) { return id / Wi; };
    auto cid = [Wi](int id) { return id % Wi; };

    size_t N = H * W;
    vector<int> parent(N, -1);
    vector<char> used(N, 0);

    Queue* q = queue_create();
    used[id(sr, sc)] = 1;
    queue_insert(q, id(sr, sc));

    while (!queue_empty(q)) {
        int cur = queue_get(q);
        queue_remove(q);

        int r = rid(cur), c = cid(cur);
        if (r == er && c == ec)
            break;

        Cells nb; nb.reserve(6);
        neighbors(r, c, H, W, nb);

        for (size_t k = 0; k < nb.size(); ++k) {
            int nr = nb[k].first;
            int nc = nb[k].second;
            char ch = g[nr][nc];

            if (ch == '#')
                continue;

            int nid = id(nr, nc);

            if (used[nid])
                continue;

            used[nid] = 1;
            parent[nid] = cur;
            queue_insert(q, nid);
        }
    }

    queue_delete(q);

    int cur = id(er, ec);
    int Sid = id(sr, sc);

    if (used[cur]) {
        while (cur != Sid && cur != -1) {
            int r = rid(cur), c = cid(cur);
            if (g[r][c] == '.')
                g[r][c] = 'x';

            cur = parent[cur];
        }
    }

    print_hex(g);
    return;
}