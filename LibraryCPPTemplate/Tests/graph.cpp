#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    Graph<int, int> g(3);

    g.add_edge(0, 1, 5);
    g.add_edge(0, 2, 1);

    if (!g.has_edge(0, 1)) {
        cout << "has_edge fail\n";
        return 1;
    }

    int cnt = 0;
    Graph<int, int>::NeighborIterator it = g.neighbors_begin(0);

    while (it.valid()) {
        ++cnt;
        it.next();
    }
    if (cnt < 2) {
        cout << "iter fail\n";
        return 1;
    }

    g.remove_edge(0, 1);

    if (g.has_edge(0, 1)) {
        cout << "remove_edge fail\n";
        return 1;
    }
    
    cout << "GraphOK\n";
    return 0;
}