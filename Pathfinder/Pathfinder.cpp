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

	std::map<std::string, int> dict;
	std::vector<std::string> dictReverse;

	std::vector < std::vector<int> > g;
	int n = 1;
	int s, e;
	Queue* q = queue_create();

	while (!input.eof()) {
		std::string origin;
		std::string ending;
		input >> origin >> ending;

		if (!dict[origin]) {
			dict[origin] = n;
			dictReverse.push_back(origin);
			n++;
		}
		if (!dict[ending]) {
			dict[ending] = n;
			dictReverse.push_back(ending);
			n++;
		}

		if (!input.eof()) {
			if (dict[origin] > g.size()) {
				g.resize(dict[origin]);
			}
			g[dict[origin] - 1].push_back(dict[ending] - 1);
		}
		else {
			s = dict[origin] - 1;
			e = dict[ending] - 1;
		}
	}

	g.resize(n - 1);
	std::vector<bool> used(n);
	std::vector<int> d(n), p(n);
	queue_insert(q, s);
	used[s] = true;
	p[s] = -1;
	while (!queue_empty(q)) {
		int v = queue_get(q);
		queue_remove(q);
		for (size_t i = 0; i < g[v].size(); ++i) {
			int to = g[v][i];
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
		std::vector<int> path;
		for (int v = e; v != -1; v = p[v])
			path.push_back(v);
		for (size_t i = path.size() - 1; i < path.size(); --i)
			output << dictReverse[path[i]] << " ";
	}

}
