#include "floyd.h"

static const long long INF = 1000000000000000LL;

void floyd_alg(const GraphStrInt& graph, rastMatrix& dist, nextMatrix& next_versh) {
	size_t n = graph.size();

	dist.resize(n);
	next_versh.resize(n);

	for (size_t i = 0; i < n; i++) {
		dist[i].resize(n);
		next_versh[i].resize(n);
		for (size_t j = 0; j < n; j++) {
			if (i == j) {
				dist[i][j] = 0;
				next_versh[i][j] = i;
			}
			else {
				dist[i][j] = INF;
				next_versh[i][j] = n;
			}

		}
	}

	for (size_t i = 0; i < n; i++) {
		for (auto it = graph.begin(i); it != graph.end(i); it++) {
			size_t j = *it;
			dist[i][j] = it.label();
			next_versh[i][j] = j;
		}
	}

	for (size_t k = 0; k < n; k++) {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (dist[i][k] < INF && dist[k][j] < INF) {
					long long new_rasstoyanie = dist[i][k] + dist[k][j];
					if (new_rasstoyanie < dist[i][j]) {
						dist[i][j] = new_rasstoyanie;
						next_versh[i][j] = next_versh[i][k];
					}
				}
			}
		}
	}
}

Vector<size_t> vosstanovka_path(const nextMatrix& next_versh, size_t from, size_t to) {
	Vector<size_t> path;
	size_t n = next_versh.size();

	if (next_versh[from][to] >= n) {
		return path;
	}

	size_t ver = from;
	path.add(ver);

	while (ver != to) {
		ver = next_versh[ver][to];
		path.add(ver);
	}
	return path;
}