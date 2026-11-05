#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <stdexcept>

typedef Vector<Vector<long long>> rastMatrix;
typedef Vector<Vector<size_t>> nextMatrix;
typedef Graph<string, int> cr_Graph;

struct Floyd {
	rastMatrix rasstoyanie;
	nextMatrix next_versh;
};

Floyd floyd_alg(const cr_Graph& graph);

Vector<size_t> vosstanovka_path(const Floyd& result, size_t from, size_t to);

#endif

