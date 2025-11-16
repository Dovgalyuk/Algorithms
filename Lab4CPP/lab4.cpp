#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "graph.h"
using namespace std;

const double INF = 1e12;

void build_matrix(Graph<string, double>& graph, vector<vector<double>>& dist, vector<vector<int>>& next, vector<string>& names) {

	size_t n = graph.vertex_count();
	
	dist.resize(n, vector<double>(n, INF));
	next.resize(n, vector<int>(n, -1));
	names.resize(n);

	for (size_t i = 0; i < n; i++) {
		names[i] = graph.vertex_name(i);
		dist[i][i] = 0;
	}

	for (size_t i = 0; i < n; i++) {
		string s = names[i];
		auto it = graph.get_neighbors(s);

		while (it.valid()) {

			int j = (int)it.current();
			dist[i][j] = it.edge_data();
			next[i][j] = j;
			it.next();
		}

	}
}

void floyd(vector<vector<double>>& dist, vector<vector<int>>& next) {

	size_t n = dist.size();

	for (size_t k = 0; k < n; k++) {

		for (size_t i = 0; i < n; i++) {

			for (size_t j = 0; j < n; j++) {

				if (dist[i][k] + dist[k][j] < dist[i][j]) {

					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

void print_distans(vector<vector<double>>& dist, vector<string>& names) {

	size_t n = dist.size();

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {

			cout << names[i] << " to " << names[j] << ": ";

			if (dist[i][j] == INF) {
				cout << "INF\n";
			}
			else {
				cout << dist[i][j] << "\n";
			}
		}
	}
}	

int main(int argc, char* argv[]) {
	(void)argc;

	Graph<string, double> graph;
	map<string, bool> add;

	ifstream file(argv[1]);	

	if (!file.is_open()) {
		return 1;
	}

	string from, to;
	double ves;

	while (file >> from >> to >> ves) {

		if (!add[from]) {

			graph.add_vertex(from);
			add[from] = true;
		}

		if (!add[to]) {
			graph.add_vertex(to);
			add[to] = true;
		}
		graph.add_edge(from, to, ves);
	}
	file.close();


	vector<vector<double>> dist;
	vector<vector<int>> next;
	vector<string> names;

	build_matrix(graph, dist, next, names);
	floyd(dist, next);
	print_distans(dist, names);

}
