#include "graph.h"
#include <iostream>
using namespace std;
int main() {
    Graph< string, int> graph(3);
    graph.setVertexLabel(0, "A");
    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);

    if (graph.getVertexCount() == 3 && graph.hasEdge(0, 1)) {
         cout << "Basic functionality: OK" <<  endl;
    }

    return 0;
}