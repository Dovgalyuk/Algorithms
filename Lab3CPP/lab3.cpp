#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream f;
    if (argc > 1) {
        f.open(argv[1]);
        if (!f) {
            cerr << "Cannot open " << argv[1] << endl;
            return 1;
        }
    }
    istream& in = (argc > 1) ? static_cast<istream&>(f) : cin;

    ofstream fout;
    if (argc > 2) {
        fout.open(argv[2], ios::binary);
        if (!fout) {
            cerr << "Cannot open " << argv[2] << endl;
            return 1;
        }
    }
    ostream& out = (argc > 2) ? static_cast<ostream&>(fout) : cout;

    Vector *v = vector_create();
    size_t w = 0;
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {line.pop_back();}
        if (line.empty()) continue;

        if (w == 0) w = line.size();
        if (line.size() != w) {
            cerr<<"Oshibka"<<endl;
            vector_delete(v);
            return 1;
        }
        size_t s  = vector_size(v);
        vector_resize(v, s+w);
        for (size_t i = 0; i < w; i++) {
            vector_set(v, s + i, (Data)line[i]);
        }
    }
    if (w==0) {
        vector_delete(v);
        return 0;
    }

    const int width = (int)w;
    const int height = (int)(vector_size(v)/w);
    const int z = width*height;

    int s = -1, fin = -1;
    for (int i = 0; i < z; i++) {
        char ch = (char)vector_get(v, i);
        if (ch == 'S') s = i;
        else if (ch == 'E') fin = i;
    }

    if (s == -1 || fin == -1) {
        cerr<<"S or E not found"<<endl;
        vector_delete(v);
        return 1;
    }

    Vector *p = vector_create();
    vector_resize(p, (size_t)z);
    for (int i = 0; i < z; i++) {
        vector_set(p, i, -1);
    }

    const int dr[6] = { 0,  0, -1, -1,  1, 1 };
    const int dc[6] = {-1,  1,  0,  1, -1, 0 };


    Queue *q = queue_create();
    queue_insert(q, (Data)s);
    vector_set(p, s, (Data)s);

    while (!queue_empty(q) && (int)vector_get(p, fin) == -1) {
        int cur = (int)queue_get(q);
        queue_remove(q);
        int r = cur / width, c = cur % width;
        for (int i = 0; i < 6; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= height || nc < 0 || nc >= width)
                continue;

            int next = nr * width + nc;

            if ((char)vector_get(v, next) == '#')
                continue;
            if ((int)vector_get(p, next) != -1)
                continue;
            vector_set(p, next, (Data)cur);
            queue_insert(q, (Data)next);
        }
    }
    queue_delete(q);

    if ((int)vector_get(p, fin) == -1) {
        out << "No path\n";
    } else {
        for (int cur = (int)vector_get(p, fin); cur != s; cur = (int)vector_get(p, cur))
            vector_set(v, cur, (Data)'x');
    }
    vector_delete(p);

    out << ' ';
    for (int i = 0; i < width; i++) {
        out << "/ \\";
        if (i + 1 < width) out << ' ';
    }
    out << '\n';
    for (int j = 0; j < height; j++) {
        out << string(2 * j, ' ');
        for (int i = 0; i < width; i++) {
            char ch = (char)vector_get(v, j * width + i);
            out << "| " << (ch == '.' ? ' ' : ch) << ' ';
        }
        out << "|\n";
        out << string(2 * j + 1, ' ');
        for (int c = 0; c < width; c++) {
            out << "\\ /";
            if (c + 1 < width) out << ' ';
        }
        if (j + 1 < height) out << " \\";
        out << '\n';
    }
    vector_delete(v);
    return 0;
}