#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Graph g;

  g.addVertex("A");
  g.addVertex("B");
  g.addVertex("C");

  if (!g.hasVertex("A") || !g.hasVertex("B") || !g.hasVertex("C")) {
    cout << "Failed to add vertices\n";
    return 1;
  }

  g.addEdge("A", "B");
  g.addEdge("B", "C");

  if (!g.hasEdge("A", "B")) {
    cout << "Edge A->B not found\n";
    return 1;
  }
  if (!g.hasEdge("B", "C")) {
    cout << "Edge B->C not found\n";
    return 1;
  }
  if (g.hasEdge("A", "C")) {
    cout << "Unexpected edge A->C found\n";
    return 1;
  }

  g.setVertexLabel("A", "Start");
  if (g.getVertexLabel("A") != "Start") {
    cout << "Vertex label for A is incorrect\n";
    return 1;
  }

  g.setEdgeLabel("A", "B", "first");
  if (g.getEdgeLabel("A", "B") != "first") {
    cout << "Edge label for A->B is incorrect\n";
    return 1;
  }

  bool foundB = false;
  for (auto it = g.beginNeighbors("A"); it != g.endNeighbors("A"); ++it) {
    if (*it == "B") {
      foundB = true;
    }
  }
  if (!foundB) {
    cout << "Neighbor B of A not found via iterator\n";
    return 1;
  }

  g.removeEdge("A", "B");
  if (g.hasEdge("A", "B")) {
    cout << "Edge A->B should be removed\n";
    return 1;
  }

  g.addEdge("A", "B");

  auto labels = g.getAllVertexLabels();
  if (labels.size() != 3) {
    cout << "Expected 3 vertex labels, got " << labels.size() << "\n";
    return 1;
  }

  cout << "All graph tests passed!\n";
  return 0;
}
