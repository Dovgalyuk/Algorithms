#include "graph.h"
#include "queue.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> bfsShortestPath(const Graph &g, const string &start,
                               const string &target) {
  if (!g.hasVertex(start) || !g.hasVertex(target)) {
    return {};
  }

  unordered_map<string, bool> visited;
  unordered_map<string, string> parent;
  Queue<string> q;

  q.push(start);
  visited[start] = true;
  parent[start] = "";

  while (!q.empty()) {
    string u = q.front();
    q.pop();

    if (u == target)
      break;

    for (auto it = g.beginNeighbors(u); it != g.endNeighbors(u); ++it) {
      string v = *it;
      if (!visited[v]) {
        visited[v] = true;
        parent[v] = u;
        q.push(v);
      }
    }
  }

  if (!visited[target])
    return {};

  vector<string> path;
  for (string at = target; !at.empty(); at = parent[at]) {
    path.push_back(at);
  }
  reverse(path.begin(), path.end());
  return path;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  ifstream fin(argv[1]);
  if (!fin.is_open()) {
    cerr << "Cannot open " << argv[1] << "\n";
    return 1;
  }

  Graph g;
  string line;

  getline(fin, line);
  istringstream vss(line);
  string name;
  while (vss >> name) {
    g.addVertex(name);
  }

  while (getline(fin, line)) {
    if (line.empty())
      continue;
    istringstream edge_ss(line);
    string from, to;
    if (edge_ss >> from >> to) {
      g.addEdge(from, to);
    }
  }

  string start = "A";
  string target = "E";

  auto path = bfsShortestPath(g, start, target);

  if (path.empty()) {
    cout << "No path found.\n";
  } else {
    cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); i++) {
      if (i > 0)
        cout << " -> ";
      cout << path[i];
    }
    cout << "\n";
  }

  return 0;
}
