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

vector<char> bfs(char start, unordered_map<char, vector<char>>& graph);
vector<char> task(ifstream& input, int reactions);

#endif