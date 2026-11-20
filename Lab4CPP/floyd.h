#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <cstddef>

typedef Graph<string, int> GraphStrInt;
typedef Graph<string, size_t> NextGraphVersh;

void floyd_alg(GraphStrInt& graph, NextGraphVersh& next_versh);

Vector<size_t> vosstanovka_path(const NextGraphVersh& next_versh, size_t from, size_t to);


#endif
