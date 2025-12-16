#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include "vector.h"
#include "graph.h"

using namespace std;

typedef Vector<int> MyVector;
typedef Digraph<std::string, int> MyGraph;

void bfsShortestPath(const MyGraph& graph, int start, int target,
    int& distance, MyVector& path) {
    size_t n = graph.countvert();
    if (start < 0 || start >= (int)n || target < 0 || target >= (int)n) {
        distance = -1;
        return;
    }

    if (start == target) {
        distance = 0;
        path.push_back(start);
        return;
    }

    MyVector visited(n, 0);
    MyVector parent(n, -1);
    MyVector queue;

    visited[start] = 1;
    queue.push_back(start);

    bool found = false;
    size_t front = 0;

    while (front < queue.size() && !found) {
        int current = queue[front];
        front++;

        for (auto it = graph.nbegin(current); it != graph.nend(current); ++it) {
            int neighbor = (int)it.neighborid();
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                parent[neighbor] = current;
                queue.push_back(neighbor);

                if (neighbor == target) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        distance = -1;
        return;
    }

    distance = 0;
    int node = target;
    while (node != -1) {
        path.push_back(node);
        node = parent[node];
        if (node != -1) distance++;
    }

    MyVector reversedPath(path.size());
    for (size_t i = 0; i < path.size(); ++i) {
        reversedPath[i] = path[path.size() - 1 - i];
    }
    path = reversedPath;
}

MyGraph readgraphfromfile(string prargv) {
    ifstream in(prargv);
    if (!in.is_open()) {
        MyGraph prprimgraph;
        return prprimgraph;
    }
    else {
        size_t asize1 = 0;
        in >> asize1;
        MyGraph prprimgraph(asize1);
        for (size_t i = 0; i < asize1; i++) {
            string vertlabe;
            in >> vertlabe;
            prprimgraph.setvertlabel(i, vertlabe);
        }
        size_t edgesize = 0;
        in >> edgesize;
        for (size_t i = 0; i < edgesize; i++) {
            string vertexfrom;
            string vertexto;
            int weight;
            in >> vertexfrom >> vertexto >> weight;
            int vertexfromid = prprimgraph.getvertexlabelid(vertexfrom);
            int vertextoid = prprimgraph.getvertexlabelid(vertexto);
            if (vertexfromid >= 0 && vertextoid >= 0) {
                prprimgraph.addedge((size_t)vertexfromid, (size_t)vertextoid, weight);
            }
        }
        in.close();
        return prprimgraph;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_filename> <start_vertex> <target_vertex>" << endl;
        return 1;
    }

    MyGraph graph = readgraphfromfile(argv[1]);
    string startLabel = argv[2];
    string targetLabel = argv[3];

    int startId = graph.getvertexlabelid(startLabel);
    int targetId = graph.getvertexlabelid(targetLabel);

    if (startId == -1) {
        cerr << "Error: Start vertex '" << startLabel << "' not found" << endl;
        return 1;
    }

    if (targetId == -1) {
        cerr << "Error: Target vertex '" << targetLabel << "' not found" << endl;
        return 1;
    }

    cout << "Adjacency matrix (" << graph.countvert() << " vertices):\n";
    graph.printadmatrix();

    int distance;
    MyVector path;
    bfsShortestPath(graph, startId, targetId, distance, path);

    if (distance == -1) {
        cout << "No path found from " << startLabel << " to " << targetLabel << endl;
    }
    else {
        cout << "Shortest path from " << startLabel << " to " << targetLabel << ":\n";
        cout << "Distance (edges): " << distance << "\n";
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << graph.getvertexlabel(path[i]);
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";
    }

    return 0;
}