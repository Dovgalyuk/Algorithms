#pragma once

class DSU {
private:
    Vector<int> parent;
    Vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent.set(i, i);
            rank.set(i, 0);
        }
    }

    int find_set(int v) {
        if (v == parent.get(v))
            return v;
        int root = find_set(parent.get(v));
        parent.set(v, root);
        return root;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank.get(a) < rank.get(b))
                std::swap(a, b);
            parent.set(b, a);
            if (rank.get(a) == rank.get(b))
                rank.set(a, rank.get(a) + 1);
        }
    }
};