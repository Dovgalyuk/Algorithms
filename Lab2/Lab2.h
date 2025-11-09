#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"
#include "vector.h"

int scrabbleValue(char c) {
	switch (std::toupper(static_cast<unsigned char>(c))) {
	case 'A': case 'E': case 'I': case 'L': case 'N':
	case 'O': case 'R': case 'S': case 'T': case 'U': return 1;
	case 'D': case 'G': return 2;
	case 'B': case 'C': case 'M': case 'P': return 3;
	case 'F': case 'H': case 'V': case 'W': case 'Y': return 4;
	case 'K': return 5;
	case 'J': case 'X': return 8;
	case 'Q': case 'Z': return 10;
	default: return 0;
	}
}

int wordScore(const std::string& word) {
	int s = 0;
	for (char c : word) s += scrabbleValue(c);
	return s;
}

Vector<std::string> tokenize(const std::string& text) {
	Vector<std::string> words;
	std::string w;

	for (char c : text) {
		if (std::isalpha(static_cast<unsigned char>(c))) {
			w += (char)std::toupper(static_cast<unsigned char>(c));
		}
		else if (!w.empty()) {
			words.push_back(w);
			w.clear();
		}
	}
	if (!w.empty()) words.push_back(w);
	return words;
}

void run(const Vector<std::string>& words, std::istream& input, std::ostream& output) {
	Stack<int> stack;
	std::size_t ip = 0;

	while (ip < words.size()) {
		auto score = wordScore(words[ip]);
		++ip;

		switch (score) {
		case 5:
			if (ip < words.size()) {
				stack.push(wordScore(words[ip]) & 0xFF);
				++ip;
			}
			break;
		case 6:
			if (!stack.empty()) stack.pop();
			break;
		case 7:
			if (stack.size() >= 2) {
				auto a = stack.top(); stack.pop();
				auto b = stack.top(); stack.pop();
				stack.push((b + a) & 0xFF);
			}
			break;
		case 8:
		{
			int c = input.get();
			stack.push((c == EOF ? 0 : static_cast<unsigned char>(c)) & 0xFF);
		}
		break;
		case 9:
			if (!stack.empty()) {
				auto val = stack.top(); stack.pop();
				output.put(static_cast<char>(val & 0xFF));
				output.flush();
			}
			break;
		case 10:
			if (stack.size() >= 2) {
				auto a = stack.top(); stack.pop();
				auto b = stack.top(); stack.pop();
				int res = (b - a) & 0xFF;
				stack.push(res);
			}
			break;
		case 11:
			if (stack.size() >= 2) {
				auto a = stack.top(); stack.pop();
				auto b = stack.top(); stack.pop();
				stack.push(a);
				stack.push(b);
			}
			break;

		case 12:
			if (!stack.empty()) {
				auto n = stack.top();
				stack.pop();
				stack.push(n);
				stack.push(n);
			}
			break;
		case 13:
			if (ip < words.size() && !stack.empty()) {
				auto n = wordScore(words[ip]);
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond == 0) {
					ip += n;
				}
				else {
					++ip;
				}
			}
			break;

		case 14:
			if (ip < words.size() && !stack.empty()) {
				auto n = wordScore(words[ip]);
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond != 0) {
					ip += n;
				}
				else { 
					++ip; 
				}
			}
			break;

		case 15:
			if (ip < words.size() && !stack.empty()) {
				auto n = wordScore(words[ip]);
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond == 0 && n <= ip) { 
					ip -= (n + 1); 
				}
				else { 
					++ip; 
				}
			}
			break;

		case 16:
			if (ip < words.size() && !stack.empty()) {
				auto n = wordScore(words[ip]);
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond != 0 && n <= ip) {
					ip -= (n + 1);
				}
				else {
					++ip;
				}
			}
			break;
		case 17:
			return;

		default:
			break;
		}
	}
}