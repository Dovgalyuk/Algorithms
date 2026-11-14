#include "floyd.h"
#include <stdexcept>


void floyd_alg(GraphStrInt& graph) {
	size_t n = graph.size();

	for (size_t i = 0; i < n; i++) {
		graph.set_rebro_label(i, i, 0);
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
				long long dist_kj = it.label();
				long long sum = static_cast<long long>(dist_ik) + dist_kj;

				if (!graph.has_rebro(i, j) || sum < graph.get_rebro_label(i, j)) {
					graph.set_rebro_label(i, j, static_cast<int>(sum));
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

Vector<size_t> vosstanovka_path(const GraphStrInt& graph, size_t from, size_t to) {
	Vector<size_t> path;
	
	if (from == to) {
		path.add(from);
		return path;
	}

	if (!graph.has_rebro(from, to)) {
		return path;
	}


	size_t n = graph.size();

	for (size_t k = 0; k < n; k++) {
		if (k == from || k == to) {
			continue;
		}

		if (graph.has_rebro(from, k) && graph.has_rebro(k, to)) {
			if (graph.get_rebro_label(from, k) + graph.get_rebro_label(k, to) == graph.get_rebro_label(from, to)) {
				Vector<size_t> left_path = vosstanovka_path(graph, from, k);
				Vector<size_t> right_path = vosstanovka_path(graph, k, to);

				for (size_t i = 0; i < left_path.size(); i++) {
					path.add(left_path[i]);
				}
				for (size_t i = 1; i < right_path.size(); i++) {
					path.add(right_path[i]);
				}
				return path;
			}
		}
	}

	path.add(from);
	path.add(to);
	return path;
}