#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"
#include "vector.h"

using ScoreVector = Vector<int>;

int scrabbleValue(char c);
int wordScore(const std::string& word);
ScoreVector tokenize(const std::string& text);
void run(const ScoreVector& scores, std::istream& input, std::ostream& output);