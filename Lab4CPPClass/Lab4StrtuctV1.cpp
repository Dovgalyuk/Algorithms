#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "vector.h"
#include "graph.h"

using namespace std;

typedef Vector<int> MyVector;
typedef Digraph<std::string, int> MyGraph;
MyGraph primMSTGraph(const MyGraph& primgraph) {
    size_t v = primgraph.countvert();
    MyGraph mstGraph(v);

    if (v == 0) {
        return mstGraph;
    }

    for (size_t i = 0; i < v; i++) {
        mstGraph.setvertlabel(i, primgraph.getvertexlabel(i));
    }

    Vector<int> parent(v, -1);
    Vector<int> key(v, INT_MAX);
    Vector<bool> inMST(v, false);

    std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> pq;

    key[0] = 0;
    pq.push({ 0, 0 });

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        if (inMST[currentVertex]) {
            continue;
        }

        inMST[currentVertex] = true;

        for (auto it = primgraph.nbegin(currentVertex);
            it != primgraph.nend(currentVertex); ++it) {

            int neighbor = (int)it.neighborid();
            int weight = it.edgelabel();

            if (weight > 0 && !inMST[neighbor] && weight < key[neighbor]) {
                key[neighbor] = weight;
                parent[neighbor] = currentVertex;
                pq.push({ weight, neighbor });
            }
        }
    }
    for (size_t i = 1; i < v; i++) {
        if (parent[i] != -1) {
            int weight = primgraph.getedgelabel(parent[i], i);
            mstGraph.addedge(parent[i], i, weight);
            mstGraph.addedge(i, parent[i], weight);
        }
    }

    return mstGraph;
}


int main(int argc, char* argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << endl;
        return 1;
    }
    size_t asize1 = 0;
    ifstream in(argv[1]);
    if (in.is_open()) {
        in >> asize1;
        if (asize1 > 0) {
            MyGraph primgraph(asize1);


            for (size_t i = 0; i < asize1; i++) {
                string vertlabe;
                in >> vertlabe;
                primgraph.setvertlabel(i, vertlabe);
            }
            for (size_t i = 0; i < asize1; i++) {
                for (int j = 0; j < asize1; j++) {
                    int weight;
                    in >> weight;
                    if (weight != 0) {
                        primgraph.addedge(i, j, weight);
                        primgraph.addedge(j, i, weight);
                    }
                }
            }
            primgraph.printadmatrix();
            int originalTotalWeight = 0;
            for (size_t i = 0; i < primgraph.countvert(); ++i) {
                for (auto it = primgraph.nbegin(i); it != primgraph.nend(i); ++it) {
                    if (i < it.neighborid()) {
                        originalTotalWeight += it.edgelabel();
                    }
                }
            }
            std::cout << "Original graph total weight: " << originalTotalWeight << endl;

            MyGraph mstGraph = primMSTGraph(primgraph);
            std::cout << "MST Graph adjacency matrix:" << endl;
            mstGraph.printadmatrix();
            int mstTotalWeight = 0;
            for (size_t i = 0; i < mstGraph.countvert(); ++i) {
                for (auto it = mstGraph.nbegin(i); it != mstGraph.nend(i); ++it) {
                    if (i < it.neighborid()) {
                        mstTotalWeight += it.edgelabel();
                    }
                }
            }
            std::cout << "MST total weight: " << mstTotalWeight << endl;
            ofstream out(argv[2]);

            if (!out.is_open()) {
                cerr << "Error: Cannot open output file " << argv[2] << endl;
                return 1;
            }
            out << mstGraph.countvert() << endl;
            Vector<string> vlabels = mstGraph.getallvertexlabels();
            for (size_t i = 0; i < mstGraph.countvert(); i++) {
                out << vlabels[i] << endl;
            }
            for (size_t i = 0; i < mstGraph.countvert(); i++) {
                for (size_t j = 0; j < mstGraph.countvert(); j++) {
                    out << mstGraph.getedgelabel(i, j) << " ";
                }
                out << endl;
            }
            out.close();
        }
        in.close();

    }
    return 0;
}