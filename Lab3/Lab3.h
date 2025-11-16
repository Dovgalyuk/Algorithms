#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include "queue.h"
#include "vector.h"

using IntVector = Vector<int>;
using Graph = Vector<IntVector>;
using BFSResult = std::pair<IntVector, IntVector>;

BFSResult bfs(int n, int start, int finish, Graph& graph);

