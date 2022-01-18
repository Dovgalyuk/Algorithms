#include "graph.h"


using namespace std;
const int maxVertices = 4;

void startDijkstra(Graph<pair<bool, int>> &graph, int vertexIndex);
void findCosts(Graph<pair<bool, int>> &graph, size_t vertexIndex);

int main() {

    int in[maxVertices][maxVertices] = {

            {0,4,1,0},
            {4,0,0,6},
            {3,1,0,0},
            {0,4,0,0},
    };

    Graph<pair<bool, int>> graph(maxVertices);
    for (int i = 0; i < maxVertices; i++) {
        graph.setVertex(i, pair<bool, int>(false, -1));
        for (int j = 0; j < maxVertices; j++) {
            int cost = in[i][j];
            graph.setEdge(i, j, cost);
        }
    }

    graph.displayMatrix();

    cout << endl;

    for (int i = 0; i < maxVertices; i++) {
        startDijkstra(graph, i);
    }

    return 0;
}

void startDijkstra(Graph<pair<bool, int>> &graph, int vertexIndex) {
    for (int i = 0; i < maxVertices; i++) {
        graph.setVertex(i, pair<bool, int>(false, INT_MAX));
    }
    graph.setVertex(vertexIndex, pair<bool, int>(false, 0));

    int lastIndex = vertexIndex;
    while (lastIndex != -1) {
        findCosts(graph, lastIndex);
        lastIndex = -1;
        auto nextIt = graph.getIterator();
        int minCost = INT_MAX;
        while (nextIt.hasNext()) {
            nextIt.next();
            auto vertex = *nextIt;
            size_t viewIndex = nextIt.getCurrentIndex();
            if (vertex->data.first) continue;
            if ( minCost <= vertex->data.second) continue;
            minCost = vertex->data.second;
            lastIndex = viewIndex;
        }
    }

    cout << "Paths from the vertex " << vertexIndex << ": " <<endl;
    for (size_t i = 0; i < maxVertices; i++) {
        if (i == vertexIndex) continue;
        cout << "Way to the vertex " << i << " cost is " << graph.getVertex(i)->data.second << endl;
    }
    cout << endl;
}
void findCosts(Graph<std::pair<bool, int>> &graph, size_t vertexIndex) {

    auto it = graph.getNeighbourIterator(vertexIndex);
    while (it.hasNext()) {
        it.next();
        auto vertex = *it;
        size_t viewIndex = it.getCurrentIndex();
        int newCost = graph.getEdgeCost(vertexIndex, viewIndex) + graph.getVertex(vertexIndex)->data.second;
        if (vertex->data.first) continue;
        if ( vertex->data.second <= newCost) continue;
        vertex->data.second = newCost;
    }
    graph.getVertex(vertexIndex)->data.first = true;
}