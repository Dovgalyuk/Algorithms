#include "graph.h"
#include "vector.h"
#include "Kruskal.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Need input file" << endl;
        return 1;
    }

    Graph<char, int> graph(Graph<char, int>::Graph_Type::Undirected, 0);

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cout << "File not opened\n";
        return 1;
    }

    int vertices_count, edge_count;
    in >> vertices_count >> edge_count;

    char vertex;
    for (int i = 0; i < vertices_count; i++) {
        in >> vertex;
        graph.add_vertex(vertex);
    }

    char from, to; int weight;
    for (int i = 0; i < edge_count; i++) {
        in >> from >> to >> weight;
        graph.add_edge(from, to, weight);
    }
    
    Vector<Edge_Expanded<char, int>> result = kruskal<char, int>(graph, vertices_count);

    cout << "Minimal tree:" << endl;
    for (const Edge_Expanded<char, int>& e : result) {
        cout << e.u << " -- " << e.v << " : " << e.weight << endl;
    }

    in.close();

    return 0;
}