#include <iostream>
#include <fstream>
#include <cstdint>

#include "graph.h"

typedef Graph<std::string, int> MyGraph;

MyGraph primMST(const MyGraph& g)
{
    size_t n = g.size();
    if (n == 0) return MyGraph(0);

    Vector<int> min_e; 
    min_e.resize(n);
    Vector<int> sel_e; 
    sel_e.resize(n);
    Vector<bool> used;   
    used.resize(n);

    for (size_t i = 0; i < n; i++) {
        min_e.set(i, INT32_MAX);
        sel_e.set(i, -1);
        used.set(i, false);
    }

    min_e.set(0, 0);

    MyGraph mst(n);

    for (size_t i = 1; i < n; i++){
        mst.setVertexLabel(i, g.getVertexLabel(i));
    }

    mst.setVertexLabel(0, g.getVertexLabel(0));

    for (size_t i = 0; i < n; i++)
    {
        int v = -1;

        for (size_t j = 0; j < n; j++)
            if (!used.get(j) && (v == -1 || min_e.get(j) < min_e.get(v)))
                v = j;

        used.set(v, true);

        if (sel_e.get(v) != -1) {
            int from = sel_e.get(v);
            mst.addEdge(from, v, min_e.get(v));
            mst.addEdge(v, from, min_e.get(v));
        }

        for (auto it = g.neighbors_begin(v); it != g.neighbors_end(v); ++it)
        {
            int to = *it;
            int w = g.getEdgeLabel(v, to);

            if (!used.get(to) && w < min_e.get(to))
            {
                min_e.set(to, w);
                sel_e.set(to, v);
            }
        }
    }

    return mst;
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    size_t n, m;
    inputFile >> n >> m;

    MyGraph g(n);

    for (size_t i = 0; i < n; i++) {
        g.setVertexLabel(i, "v" + std::to_string(i));
    }

    for (size_t i = 0; i < m; i++) {
        size_t u, v;
        int w;
        inputFile >> u >> v >> w;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    MyGraph mst = primMST(g);

    for (size_t i = 0; i < mst.size(); i++) {
        for (auto it = mst.neighbors_begin(i); it != mst.neighbors_end(i); ++it) {
            size_t to = *it;
            if (i < to) {
                std::cout << i << "-" << to << std::endl;
            }
        }
    }

    return 0;
}