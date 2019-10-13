#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "queue.h"

int main()
{
	std::ifstream input;
	input.open("input.txt");
	std::ofstream output;
	output.open("output.txt");

	std::string s, e;

	std::map<std::string, std::vector<std::string>> g;
	std::map<std::string, bool> used;
	std::map<std::string, std::string> p;
	std::map<std::string, int> d;
	Queue* q = queue_create();

	while (!input.eof()) {
		std::string origin;
		std::string ending;
		input >> origin >> ending;
		if (!input.eof()) {
			g[origin].push_back(ending);
		}
		else {
			queue_insert(q, origin);
			used[origin] = true;
			p[origin] = "\0";
			e = ending;
		}
	}

	while (!queue_empty(q)) {
		std::string v = queue_get(q);
		queue_remove(q);
		for (size_t i = 0; i < g[v].size(); ++i) {
			std::string to = g[v][i];
			if (!used[to]) {
				used[to] = true;
				queue_insert(q, to);
				d[to] = d[v] + 1;
				p[to] = v;
			}
		}
	}

	if (!used[e]) {
		output << "No path!";
	}
	else {
		std::vector<std::string> path;
		for (std::string v = e; v[0] != '\0'; v = p[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		for (size_t i = 0; i < path.size(); ++i)
			output << path[i] << " ";
	}

}
