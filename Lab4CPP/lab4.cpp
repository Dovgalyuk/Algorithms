#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void findAllSimplePaths(const Graph<string> &g, const string &current,
                        const string &target, vector<string> &currentPath,
                        unordered_set<string> &visited,
                        vector<vector<string>> &allPaths) {
  if (current == target) {
    allPaths.push_back(currentPath);
    return;
  }

  for (auto it = g.beginNeighbors(current); it != g.endNeighbors(current);
       ++it) {
    string neighbor = *it;
    if (visited.find(neighbor) != visited.end()) {
      continue;
    }

    visited.insert(neighbor);
    currentPath.push_back(neighbor);
    findAllSimplePaths(g, neighbor, target, currentPath, visited, allPaths);
    currentPath.pop_back();
    visited.erase(neighbor);
  }
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

  Graph<string> g;
  string line;

  if (getline(fin, line) && !line.empty()) {
    istringstream vss(line);
    string name;
    while (vss >> name) {
      g.addVertex(name);
    }
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

  if (!g.hasVertex(start) || !g.hasVertex(target)) {
    cout << "No path found.\n";
    return 0;
  }

  vector<vector<string>> allPaths;
  vector<string> currentPath = {start};
  unordered_set<string> visited = {start};

  findAllSimplePaths(g, start, target, currentPath, visited, allPaths);

  if (allPaths.empty()) {
    cout << "No path found.\n";
  } else {
    for (const auto &path : allPaths) {
      for (size_t i = 0; i < path.size(); i++) {
        if (i > 0)
          cout << " -> ";
        cout << path[i];
      }
      cout << "\n";
    }
  }

  return 0;
}
