#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>

#include "graph.h" 

using namespace std;

int main() {
    Graph<int, string> g;
    
  
    if (!g.read(cin)) {
        cerr << "Error reading graph!" << endl;
        return 1;
    }

    string start_label;
    if (!(cin >> start_label)) {
        cerr << "No start vertex provided!" << endl;
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
        cerr << "Start vertex not found in graph!" << endl;
        return 1;
    }

    const int INF = numeric_limits<int>::max();
    vector<int> dist(g.size(), INF);
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
                    pq.push({dist[v], v});
                }
            }
        }
    }

  
    cout << "Shortest paths from " << start_label << ":\n";
    for (size_t i = 0; i < g.size(); ++i) {
        cout << g.vertex_label(i) << ": ";
        if (dist[i] == INF) {
            cout << "INF\n";
        } else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}