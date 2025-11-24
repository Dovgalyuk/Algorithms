#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "queue.h"
#include "vector.h"

static bool passable(char c) {
    return c != '#';
}

int main(int argc, char** argv) {
    std::istream* in = &std::cin;
    std::ifstream fin;

    if (argc > 1) {
        fin.open(argv[1]);
        if (fin) in = &fin;
    }

    std::vector<std::string> a;
    std::string line;

    while (std::getline(*in, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty())
            a.push_back(line);
    }

    if (a.empty()) return 0;

    int H = (int)a.size();
    int W = (int)a[0].size();

    std::pair<int,int> S{-1,-1}, T{-1,-1};

    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j) {
            if (a[i][j] == 'Q') S = {i,j};
            if (a[i][j] == 'E') T = {i,j};
        }

    if (S.first == -1 || T.first == -1) {
        for (auto& r : a) std::cout << r << '\n';
        return 0;
    }

    std::vector<std::vector<int>> dist(H, std::vector<int>(W, -1));
    std::vector<std::vector<int>> prev(H, std::vector<int>(W, -1));

    Queue* q = queue_create();
    queue_insert(q, S.first * W + S.second);
    dist[S.first][S.second] = 0;

    const int DIRS[8][2] = {
        {-1, 0}, { 1, 0}, { 0, 1},
        {-1,-1}, {-1, 1}, { 1,-1},
        { 0,-1}, { 1, 1}
    };

    while (!queue_empty(q)) {
        int idx = queue_get(q);
        queue_remove(q);

        int i = idx / W;
        int j = idx % W;

        if (i == T.first && j == T.second)
            break;

        for (int d = 0; d < 8; ++d) {
            int di = DIRS[d][0], dj = DIRS[d][1];
            int ni = i + di, nj = j + dj;

            while (0 <= ni && ni < H && 0 <= nj && nj < W && passable(a[ni][nj])) {
                if (dist[ni][nj] == -1) {
                    dist[ni][nj] = dist[i][j] + 1;
                    prev[ni][nj] = i * W + j;
                    queue_insert(q, ni * W + nj);
                }
                ni += di;
                nj += dj;
            }
        }
    }

    queue_delete(q);

    if (dist[T.first][T.second] == -1) {
        for (auto& r : a) std::cout << r << '\n';
        return 0;
    }

    std::vector<std::string> out = a;

    int cur = T.first * W + T.second;
    while (cur != -1) {
        int r = cur / W;
        int c = cur % W;
        out[r][c] = char('0' + (dist[r][c] % 10));
        cur = prev[r][c];
    }

    for (auto& r : out)
        std::cout << r << '\n';

    return 0;
}
