#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <cstddef>

typedef Vector<Vector<long long>> rastMatrix;
typedef Vector<Vector<size_t>> nextMatrix;
typedef Graph<string, int> GraphStrInt;


void floyd_alg(const GraphStrInt& graph, rastMatrix& dist, nextMatrix& next_versh);

Vector<size_t> vosstanovka_path(const nextMatrix& next_versh, size_t from, size_t to);


#endif

