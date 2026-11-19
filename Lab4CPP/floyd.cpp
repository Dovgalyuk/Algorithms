#include "floyd.h"
#include <stdexcept>


void floyd_alg(GraphStrInt& graph, Vector<size_t>& next_versh) {
	size_t n = graph.size();

	next_versh.resize(n * n);

	for (size_t i = 0; i < n; i++) {
		graph.set_rebro_label(i, i, 0);
		for (size_t j = 0; j < n; j++) {
			next_versh[i * n + j] = (i == j) ? i : n;
		}
	}

	for (size_t i = 0; i < n; i++) {
		for (auto it = graph.begin(i); it != graph.end(i); it++) {
			next_versh[i * n + *it] = *it;
		}
	}

	for (size_t k = 0; k < n; k++) {
		for (size_t i = 0; i < n; i++) {
			if (i == k) {
				continue;
			}
			if (!graph.has_rebro(i, k)) {
				continue;
			}
			int dist_ik = graph.get_rebro_label(i, k);

			for (auto it = graph.begin(k); it != graph.end(k); it++) {
				size_t j = *it;
				if (j == k) {
					continue;
				}
				long long sum = static_cast<long long>(dist_ik) + it.label();

				if (!graph.has_rebro(i, j) || sum < graph.get_rebro_label(i, j)) {
					graph.set_rebro_label(i, j, static_cast<int>(sum));
					next_versh[i * n + j] = next_versh[i * n + k];
				}
			}
		}
	}

	for (size_t i = 0; i < n; i++) {
		if (graph.get_rebro_label(i, i) < 0) {
			throw std::runtime_error("Граф содержит отрицательный цикл");
		}
	}
}

Vector<size_t> vosstanovka_path(const Vector<size_t>& next_versh, size_t n, size_t from, size_t to) {
	Vector<size_t> path;
	if (next_versh[from * n + to] >= n) {
		return path;
	}
	size_t vibr = from;
	path.add(vibr);

	while (vibr != to) {
		vibr = next_versh[vibr * n + to];
		path.add(vibr);
	}

	return path;
}