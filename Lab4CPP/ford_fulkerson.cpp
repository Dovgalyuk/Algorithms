#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    const char* filename = (argc > 1) ? argv[1] : "input1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) return 1;

    Graph<string, int> g;
    g.read(fin);

    string sourceName, sinkName;
    if (!(fin >> sourceName >> sinkName)) return 1;

    size_t n = g.vertexCount();
    size_t source = g.findVertex(sourceName);
    size_t sink = g.findVertex(sinkName);
    if (source >= n || sink >= n) return 1;
    if (source == sink) {
        cout << 0 << '\n';
        return 0;
    }

    Graph<string, int> residual(g);
    for (size_t u = 0; u < n; u++) {
        for (auto it = g.neighborsBegin(u); it != g.neighborsEnd(u); ++it) {
            size_t v = *it;
            if (!residual.hasEdge(v, u)) residual.addEdge(v, u, 0);
        }
    }

    int maxFlow = 0;
    Vector<int> parent;
    Vector<bool> visited;
    Vector<size_t> queue;
    parent.resize(n);
    visited.resize(n);

    while (true) {
        for (size_t i = 0; i < n; i++) {
            parent.set(i, -1);
            visited.set(i, false);
        }
        queue.resize(0);
        queue.resize(1);
        queue.set(0, source);
        visited.set(source, true);

        size_t head = 0;
        bool reached = false;
        while (head < queue.size()) {
            size_t u = queue.get(head);
            head++;
            if (u == sink) {
                reached = true;
                break;
            }
            for (auto it = residual.neighborsBegin(u); it != residual.neighborsEnd(u); ++it) {
                size_t v = *it;
                if (!visited.get(v) && residual.getEdgeData(u, v) > 0) {
                    visited.set(v, true);
                    parent.set(v, (int)u);
                    size_t qSize = queue.size();
                    queue.resize(qSize + 1);
                    queue.set(qSize, v);
                }
            }
        }

        if (!reached) break;

        int pathFlow = -1;
        for (size_t v = sink; v != source; v = (size_t)parent.get(v)) {
            size_t u = (size_t)parent.get(v);
            int cap = residual.getEdgeData(u, v);
            if (pathFlow == -1 || cap < pathFlow) pathFlow = cap;
        }

        for (size_t v = sink; v != source; v = (size_t)parent.get(v)) {
            size_t u = (size_t)parent.get(v);
            residual.setEdgeData(u, v, residual.getEdgeData(u, v) - pathFlow);
            residual.setEdgeData(v, u, residual.getEdgeData(v, u) + pathFlow);
        }

        maxFlow += pathFlow;
    }

    cout << maxFlow << '\n';
    return 0;
}
