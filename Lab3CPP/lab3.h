#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "queue.h"

using namespace std;

vector<char> bfs(char start, unordered_map<char, vector<char>>& graph);
vector<char> task(ifstream& input, int reactions);

#endif