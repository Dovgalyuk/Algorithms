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
	
	struct otr
	{
		size_t u;
		size_t v;
	};

	Vector<size_t> path;
	
	if (from == to) {
		path.add(from);
		return path;
	}

	if (!graph.has_rebro(from, to)) {
		return path;
	}


	size_t n = graph.size();

	Vector<otr> st;
	st.add({ from,to });

	while (st.size() > 0) {
		otr vibr = st[st.size() - 1];
		st.resize(st.size() - 1);

		size_t u = vibr.u;
		size_t v = vibr.v;

		if (u == v) {
			if (path.size() == 0 || path[path.size() - 1] != u) {
				path.add(u);
			}
			continue;
		}

		size_t found_pr = n;

		for (size_t pr = 0; pr < n; pr++) {
			if (pr == u || pr == v) {
				continue;
			}

			if (graph.has_rebro(u, pr) && graph.has_rebro(pr, v)) {
				if (graph.get_rebro_label(u, pr) + graph.get_rebro_label(pr, v) == graph.get_rebro_label(u, v)) {
					found_pr = pr;
					break;
				}
			}
		}
		if (found_pr == n) {
			if (path.size() == 0 || path[path.size() - 1] != u) {
				path.add(u);
			}
			path.add(v);
		}
		else {
			st.add({ found_pr, v });
			st.add({ u, found_pr });
		}
	}
	return path;
}