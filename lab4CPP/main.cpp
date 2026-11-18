#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include "graph.h" 

using namespace std;


int main() {
    Graph<int, string> g;
    
    if (!g.read(cin)) {
        cout << "Error reading graph!" << endl;
        return 1;
    }


    string start_label;
    if (!(cin >> start_label)) {
        cout << "No start vertex provided!" << endl;
        return 1;
    }

    size_t start_idx = g.size();
    for (size_t i = 0; i < g.size(); ++i) {
        if (g.vertex_label(i) == start_label) {
            start_idx = i;
            break;
        }
    }

    if (start_idx == g.size()) {
        cout << "Start vertex not found in graph!" << endl;
        return 1;
    }

    const int INF = numeric_limits<int>::max();
    vector<int> dist(g.size(), INF);
    

    vector<size_t> parent(g.size(), g.size()); 
    
    dist[start_idx] = 0;

    using pii = pair<int, size_t>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    pq.push({0, start_idx});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        size_t u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto it = g.begin(u); it != g.end(u); ++it) {
            size_t v = *it;
            if (g.has_edge(u, v)) {
                int weight = g.edge_label(u, v);
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

  
    cout << "Shortest paths from " << start_label << ":\n";
    for (size_t i = 0; i < g.size(); ++i) {
        cout << g.vertex_label(i) << ": ";
        if (dist[i] == INF) {
            cout << "No path\n";
        } else {
        
            vector<size_t> path;
            for (size_t curr = i; curr != g.size(); curr = parent[curr]) {
                path.push_back(curr);
                if (curr == start_idx) break;
            }
            reverse(path.begin(), path.end());
            for (size_t j = 0; j < path.size(); ++j) {
                cout << g.vertex_label(path[j]);
                if (j < path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
    }

    return 0;
}