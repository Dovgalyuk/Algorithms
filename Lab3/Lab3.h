#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include "queue.h"
#include "vector.h"

std::pair<Vector<int>, Vector<int>> bfs(int n, int start, int finish, Vector<Vector<int>>& graph);

