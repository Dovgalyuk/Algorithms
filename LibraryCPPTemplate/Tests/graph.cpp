#include <iostream>
#include <sstream>
#include <string>
#include "graph.h"

using namespace std;

int main() {
    Graph<string, int> g(2);
    g.setVertexData(0, "A");
    g.setVertexData(1, "B");
    if (g.getVertexData(0) != "A" || g.getVertexData(1) != "B") return 1;

    size_t c = g.addVertex("C");
    if (g.vertexCount() != 3 || g.getVertexData(c) != "C") return 1;

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 30);

    if (!g.hasEdge(0, 1) || g.hasEdge(1, 0)) return 1;
    if (g.getEdgeData(0, 1) != 10) return 1;

    g.setEdgeData(0, 1, 15);
    if (g.getEdgeData(0, 1) != 15) return 1;

    int sum = 0;
    for (auto it = g.neighborsBegin(0); it != g.neighborsEnd(0); ++it)
        sum += g.getEdgeData(0, *it);

    if (sum != 35) return 1;

    g.removeEdge(0, 1);
    if (g.hasEdge(0, 1)) return 1;

    g.removeVertex(1);
    if (g.vertexCount() != 2) return 1;
    if (!g.hasEdge(0, 1) || g.getEdgeData(0, 1) != 20) return 1;

    Graph<string, int> copy(g);
    if (copy.getEdgeData(0, 1) != 20) return 1;

    istringstream iss("3 2\nX Y Z\nX Y 5\nY Z 7\n");
    Graph<string, int> fromStream;
    fromStream.read(iss);
    if (fromStream.vertexCount() != 3) return 1;
    if (!fromStream.hasEdge(0, 1) || fromStream.getEdgeData(1, 2) != 7) return 1;

    return 0;
}
