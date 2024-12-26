#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "queue.h"

using namespace std;

typedef unordered_map<Data, vector<Data>> Graph;
typedef vector<Data> Vector;

Vector bfs(Data start, Graph& graph);
Vector task(ifstream& input, int reactions);

#endif