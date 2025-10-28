#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"

const int INF = 1000000000;

struct Pos {
    int x, y;
    Pos(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};

const Pos dir[8] = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1},          {0,1},
    {1,-1},  {1,0},  {1,1}
};

int find_paths(Vector* map, int h, int w, Pos s, Pos e) {
    Vector* dist = vector_create();
    Vector* cnt = vector_create();
    vector_resize(dist, h * w);
    vector_resize(cnt, h * w);

    for (int i = 0; i < h * w; i++) {
        vector_set(dist, i, INF);
        vector_set(cnt, i, 0);
    }

    int start = s.y * w + s.x;
    int finish = e.y * w + e.x;
    vector_set(dist, start, 0);
    vector_set(cnt, start, 1);

    Queue* q = queue_create();
    queue_insert(q, start);

    while (!queue_empty(q)) {
        int cur = queue_get(q);
        queue_remove(q);
        int y = cur / w, x = cur % w;
        int d = vector_get(dist, cur);

        for (int i = 0; i < 8; i++) {
            int ny = y + dir[i].y;
            int nx = x + dir[i].x;

            while (ny >= 0 && ny < h && nx >= 0 && nx < w) {
                int idx = ny * w + nx;

                if ((char)vector_get(map, idx) == '#') {
                    break;
                }

                int nd = d + 1;
                int old_d = vector_get(dist, idx);

                if (nd < old_d) {
                    vector_set(dist, idx, nd);
                    vector_set(cnt, idx, vector_get(cnt, cur));
                    queue_insert(q, idx);
                }
                else if (nd == old_d) {
                    vector_set(cnt, idx, vector_get(cnt, idx) + vector_get(cnt, cur));
                }

                ny += dir[i].y;
                nx += dir[i].x;
            }
        }
    }

    int res = vector_get(cnt, finish);
    vector_delete(dist);
    vector_delete(cnt);
    queue_delete(q);
    return res;
}

void solve(std::ifstream& file) {
    Vector* map = vector_create();
    int h = 0, w = 0;
    std::string line;
    Pos start, end;

    while (std::getline(file, line)) {
        if (w == 0) {
            w = line.size();
        }
        vector_resize(map, (h + 1) * w);
        for (int i = 0; i < w; i++) {
            char c = line[i];
            vector_set(map, h * w + i, (Data)c);
            if (c == 'Q') {
                start = Pos(i, h);
            }
            else if (c == 'E') {
                end = Pos(i, h);
            }
        }
        h++;
    }
    std::cout << find_paths(map, h, w, start, end) << std::endl;
    vector_delete(map);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        return 1;
    }

    solve(file);
    return 0;
}