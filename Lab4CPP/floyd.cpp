#include "floyd.h"

static const long long INF = 1000000000000000LL;

Floyd floyd_alg(const Graph<string, int>& graph) {
	size_t n = graph.size();
	Floyd result;

	result.rasstoyanie.resize(n);
	result.next_versh.resize(n);

	for (size_t i = 0; i < n; i++) {
		result.rasstoyanie[i].resize(n);
		result.next_versh[i].resize(n);

		for (size_t j = 0; j < n; j++) {
			if (i == j) {
				result.rasstoyanie[i][j] = 0;
				result.next_versh[i][j] = i;
			}
			else if (graph.has_rebro(i, j)) {
				result.rasstoyanie[i][j] = graph.get_rebro_label(i, j);
				result.next_versh[i][j] = j;
			}
			else {
				result.rasstoyanie[i][j] = INF;
				result.next_versh[i][j] = n;
			}
		}
	}

	for (size_t k = 0; k < n; k++) {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (result.rasstoyanie[i][k] < INF && result.rasstoyanie[k][j] < INF) {
					long long new_rasstoyanie = result.rasstoyanie[i][k] + result.rasstoyanie[k][j];
					if (new_rasstoyanie < result.rasstoyanie[i][j]) {
						result.rasstoyanie[i][j] = new_rasstoyanie;
						result.next_versh[i][j] = result.next_versh[i][k];
					}
				}
			}
		}
	}
	return result;
}

Vector<size_t> vosstanovka_path(const Floyd& result, size_t from, size_t to) {
	Vector<size_t> path;

	if (result.rasstoyanie[from][to] >= INF) {
		return path;
	}

	size_t ver = from;

	path.add(ver);

	while (ver != to) {
		ver = result.next_versh[ver][to];
		path.add(ver);
	}
	return path;
}