#include <iostream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;

struct Cell {
    char type;
    int r, c, id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    if (lines.empty()) return 0;

    int total = 0;
    vector<Cell> cells;
    vector<vector<int>> row_ids(lines.size());

    for (size_t r = 0; r < lines.size(); ++r) {
        for (size_t c = 0; c < lines[r].size(); ++c) {
            cells.push_back({lines[r][c], (int)r, (int)c, total});
            row_ids[r].push_back(total);
            total++;
        }
    }

    vector<vector<int>> adj(total);
    for (int i = 0; i < total; ++i) {
        int r = cells[i].r, c = cells[i].c;
        if (cells[i].type == '#') continue;

        if (c > 0) adj[i].push_back(row_ids[r][c - 1]);
        if (c + 1 < (int)row_ids[r].size()) adj[i].push_back(row_ids[r][c + 1]);

        auto link = [&](int nr) {
            if (nr < 0 || nr >= (int)lines.size()) return;
            int diff = (int)row_ids[nr].size() - (int)row_ids[r].size();
            if (diff > 0) {
                adj[i].push_back(row_ids[nr][c]);
                adj[i].push_back(row_ids[nr][c + 1]);
            } else {
                if (c > 0) adj[i].push_back(row_ids[nr][c - 1]);
                if (c < (int)row_ids[nr].size()) adj[i].push_back(row_ids[nr][c]);
            }
        };
        link(r - 1);
        link(r + 1);
    }

    int S = -1, E = -1;
    for (int i = 0; i < total; ++i) {
        if (cells[i].type == 'S') S = i;
        if (cells[i].type == 'E') E = i;
    }

    if (S == -1 || E == -1) {
        cout << "No path\n";
        return 0;
    }

    Queue qF, qB;
    vector<int> dF(total, -1), dB(total, -1), pF(total, -1), pB(total, -1);
    
    qF.insert(S); dF[S] = 0;
    qB.insert(E); dB[E] = 0;
    
    int best_dist = 1e9;
    int inter = -1;

    while (!qF.empty() && !qB.empty()) {
        if (!qF.empty()) {
            int curr = qF.get(); qF.remove();
            if (dB[curr] != -1 && dF[curr] + dB[curr] < best_dist) {
                best_dist = dF[curr] + dB[curr];
                inter = curr;
            }
            for (int n : adj[curr]) {
                if (cells[n].type != '#' && dF[n] == -1) {
                    dF[n] = dF[curr] + 1;
                    pF[n] = curr;
                    qF.insert(n);
                }
            }
        }

        if (!qB.empty()) {
            int curr = qB.get(); qB.remove();
            if (dF[curr] != -1 && dF[curr] + dB[curr] < best_dist) {
                best_dist = dF[curr] + dB[curr];
                inter = curr;
            }
            for (int n : adj[curr]) {
                if (cells[n].type != '#' && dB[n] == -1) {
                    dB[n] = dB[curr] + 1;
                    pB[n] = curr;
                    qB.insert(n);
                }
            }
        }
    }

    if (inter != -1) {
        for (int c = inter; c != S; c = pF[c]) 
            if (cells[c].type != 'E') cells[c].type = 'x';
        for (int c = inter; c != E; c = pB[c]) 
            if (cells[c].type != 'S') cells[c].type = 'x';
    } else {
        cout << "No path\n";
        return 0;
    }

    // Отрисовка (гексагональная)
    size_t max_len = 0;
    for (const auto& l : lines) if (l.size() > max_len) max_len = l.size();

    for (size_t r = 0; r < lines.size(); ++r) {
        size_t current_len = lines[r].size();
        size_t leading_spaces = (max_len - current_len) + (r % 2);

        for (size_t s = 0; s < leading_spaces; ++s) cout << " ";
        for (size_t c = 0; c < current_len; ++c) cout << " / \\";
        cout << "\n";

        for (size_t s = 0; s < leading_spaces; ++s) cout << " ";
        int cell_idx = 0;
        for (size_t prev_r = 0; prev_r < r; ++prev_r) cell_idx += (int)lines[prev_r].size();

        for (size_t c = 0; c < current_len; ++c) cout << " | " << cells[cell_idx + c].type;
        cout << " |\n";
    }

    size_t last_len = lines.back().size();
    size_t last_leading = (max_len - last_len) + ((lines.size() - 1) % 2);
    for (size_t s = 0; s < last_leading; ++s) cout << " ";
    for (size_t c = 0; c < last_len; ++c) cout << " \\ /";
    cout << "\n";

    return 0;
}