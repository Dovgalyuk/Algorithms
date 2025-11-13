#include <fstream>
#include <string>
#include "Lab3.h"

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "invalid arguments" << std::endl;
		std::exit(1);
	}

	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	if (!input.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		std::exit(1);
	}

	int n, start, finish;
	input >> n >> start >> finish;

	--start; --finish;

	if (start < 0 || start >= n || finish < 0 || finish >= n) {
		std::cerr << "Invalid value" << std::endl;
		std::exit(1);
	}

	Vector<Vector<int>> graph(n);

	int t, m;
	while (input >> t >> m) {
		--t; --m;
		if (t >= 0 && t < n && m >= 0 && m < n) {
			graph[t].push_back(m);
			graph[m].push_back(t);
		}
	}

	if (auto [dist, parent] = bfs(n, start, finish, graph); dist[finish] == -1) {
		output << "IMPOSSIBLE" << std::endl;
	} else {
		Vector<int> path;
		auto v = finish;
		while (v != -1) {
			path.push_back(v);
			v = parent[v];
		}

		std::ranges::reverse(path);

		for (std::size_t index{}; index < path.size(); ++index) {
			if (index > 0) {
				output << " ";
			}
			output << path[index] + 1;
		}
		output << std::endl;
	}

	return 0;
}
