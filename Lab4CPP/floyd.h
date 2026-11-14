#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "vector.h"
#include <string>
#include <cstddef>

typedef Graph<string, int> GraphStrInt;

void floyd_alg(GraphStrInt& graph);

Vector<size_t> vosstanovka_path(const GraphStrInt& graph, size_t from, size_t to);


#endif

