#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <stdexcept>

struct Floyd {
	Vector<Vector<long long>> rasstoyanie;
	Vector<Vector<size_t>> next_versh;
};

Floyd floyd_alg(const Graph<string, int>& graph);

Vector<size_t> vosstanovka_path(const Floyd& result, size_t from, size_t to);

#endif

