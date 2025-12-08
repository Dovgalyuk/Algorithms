#include <iostream>
#include "graph.h"
using namespace std;

typedef Graph<int, int> MyGraph;

int main()
{
    MyGraph g(3);

    for (size_t i = 0; i < g.verticesCount(); i++)
    {
        g.setVertexData(i, static_cast<int>(i));
    }

    for (size_t i = 0; i < g.verticesCount(); i++)
    {
        if (g.getVertexData(i) != static_cast<int>(i))
        {
            cout << "Invalid vertex label\n";
            return 1;
        }
    }

    g.addEdge(0, 1);
    g.setEdgeData(0, 1, 5);
    g.addEdge(0, 2);
    g.setEdgeData(0, 2, 7);

    if (!g.hasEdge(0, 1) || !g.hasEdge(0, 2) || g.hasEdge(1, 2))
    {
        cout << "Invalid edge existence\n";
        return 1;
    }

    if (g.getEdgeData(0, 1) != 5 || g.getEdgeData(0, 2) != 7)
    {
        cout << "Invalid edge label\n";
        return 1;
    }

    MyGraph::Iterator it = g.getIterator(0);
    int sum = 0;
    int count = 0;
    while (it.valid())
    {
        sum += static_cast<int>(it.vertex());
        count++;
        it.next();
    }

    if (count != 2 || sum != 3)
    {
        cout << "Invalid iterator\n";
        return 1;
    }

    size_t newIndex = g.addVertex();
    if (newIndex != 3 || g.verticesCount() != 4)
    {
        cout << "Invalid addVertex\n";
        return 1;
    }

    g.removeVertex(1);
    if (g.verticesCount() != 3)
    {
        cout << "Invalid removeVertex\n";
        return 1;
    }

    cout << "Graph test passed\n";
}
