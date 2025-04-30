#ifndef DSU_H
#define DSU_H

#include "vector.h"

class DSU {
private:
    Vector<size_t> parent;
    Vector<size_t> rank;

public:
    DSU(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    size_t find(size_t x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(size_t a, size_t b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b])
                parent[a] = b;
            else if (rank[a] > rank[b])
                parent[b] = a;
            else {
                parent[b] = a;
                rank[a]++;
            }
        }
    }
};

#endif
