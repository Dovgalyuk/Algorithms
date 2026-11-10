#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <cstddef>

typedef Vector<Vector<long long>> rastMatrix;
typedef Vector<Vector<size_t>> nextMatrix;
typedef Graph<string, int> GraphStrInt;

struct Floyd {
	rastMatrix rasstoyanie;
	nextMatrix next_versh;
};


Floyd floyd_alg(const GraphStrInt& graph);

Vector<size_t> vosstanovka_path(const Floyd& result, size_t from, size_t to);


#endif

