#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include "graph.h"

using namespace std;

int getID(const vector<string>& names, const string& name) {
    for (int i = 0; i < names.size(); ++i) 
        if (names[i] == name) return i;

    return -1;
}

int main(int argc, char** argv) {
    if (argc < 2)
        return 1;

    ifstream fin(argv[1]);
    if (!fin) 
        return 1;

    int n, m;
    fin >> n >> m;

    Graph<string, int> g(n);
    vector<string> names(n);

    for (int i = 0; i < n; ++i) {
        fin >> names[i];
        g.setLabel(i, names[i]);
    }

    for (int i = 0; i < m; ++i) {
        string u, v;
        int w;
        fin >> u >> v >> w;

        int u_id = getID(names, u);
        int v_id = getID(names, v);
        if (u_id != -1 && v_id != -1) 
            g.addEdge(u_id, v_id, w);
    }

    string start, end;
    fin >> start >> end;

    int s = getID(names, start);
    int e = getID(names, end);

    if (s == -1 || e == -1) {
        cout << "Нет пути\n";
        return 0;
    }

    vector<int> dist(n, 1e9);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[s] = 0;
    pq.push({ 0, s });

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) 
            continue;

        if (u == e) 
            break;

        for (auto it = g.getEdges(u).begin(); it != g.getEdges(u).end(); ++it) {
            int v = it->data.to;     
            int w = it->data.weight; 

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    if (dist[e] == 1e9) 
        cout << "Нет пути\n";
    
    else {
        cout << "Расстояние: " << dist[e] << "\nПуть: ";
        vector<int> path;
        for (int cur = e; cur != -1; cur = parent[cur]) 
            path.push_back(cur);
        
        for (int i = path.size() - 1; i >= 0; --i) 
            cout << names[path[i]] << (i > 0 ? " -> " : "\n");
    }
    return 0;
}