#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string input_file = argv[1];
    string output_file = argv[2];

    ifstream in(input_file);
    if (!in) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    ofstream out(output_file);
    if (!out) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    int n;
    in >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> adj[i][j];
        }
    }
    in.close();

    vector<bool> visited(n, false);
    vector<vector<int>> components;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            Queue* q = queue_create();
            queue_insert(q, i);
            visited[i] = true;

            while (!queue_empty(q)) {
                int u = queue_get(q);
                queue_remove(q);
                component.push_back(u + 1);

                for (int v = 0; v < n; ++v) {
                    if (adj[u][v] && !visited[v]) {
                        visited[v] = true;
                        queue_insert(q, v);
                    }
                }
            }
            queue_delete(q);
            sort(component.begin(), component.end());
            components.push_back(component);
        }
    }

    out << components.size() << endl;
    for (const auto& comp : components) {
        for (size_t i = 0; i < comp.size(); ++i) {
            out << comp[i];
            if (i < comp.size() - 1) out << " ";
        }
        out << endl;
    }

    out.close();
    return 0;
}