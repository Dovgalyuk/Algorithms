#include "Lab3CPP.h"

#include <algorithm>
#include <iostream>

using namespace std;

bool maze_read(Maze& m, istream& in) {
    m.grid.clear();
    m.sr = m.sc = m.er = m.ec = -1;
    m.width = 0;

    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        while (!line.empty() && line.back() == ' ') line.pop_back();
        if (!line.empty()) m.grid.push_back(line);
    }
    if (m.grid.empty()) return false;

    const int k = (int)m.grid.size();
    for (auto& s : m.grid) m.width = max(m.width, (int)s.size());

    for (int r = 0; r < k; ++r)
        for (int c = 0; c < (int)m.grid[r].size(); ++c) {
            if (m.grid[r][c] == 'S') { m.sr = r; m.sc = c; }
            if (m.grid[r][c] == 'E') { m.er = r; m.ec = c; }
        }

    return m.sr >= 0 && m.er >= 0;
}

void maze_print(const Maze& m) {
    const int k = (int)m.grid.size();
    const int W = m.width;

    for (int r = 0; r < k; ++r) {
        int bc;
        string bp;
        if (r == 0) {
            bc = (int)m.grid[0].size();
            bp = "/ \\";
        }
        else {
            const int Lp = (int)m.grid[r - 1].size();
            const int Lc = (int)m.grid[r].size();
            bc = max(Lp, Lc);
            bp = (Lc > Lp) ? "/ \\" : "\\ /";
        }
        int bi = 2 * (W - bc) + 3;
        string bs = bp;
        for (int j = 1; j < bc; ++j) { bs += " "; bs += bp; }
        cout << string(bi, ' ') << bs << '\n';

        int ci = 2 * (W - (int)m.grid[r].size()) + 2;
        string cs = "|";
        for (char ch : m.grid[r]) { cs += " "; cs += ch; cs += " |"; }
        cout << string(ci, ' ') << cs << '\n';
    }

    int bc = (int)m.grid[k - 1].size();
    int bi = 2 * (W - bc) + 3;
    string bs = "\\ /";
    for (int j = 1; j < bc; ++j) { bs += " "; bs += "\\ /"; }
    cout << string(bi, ' ') << bs << '\n';
}