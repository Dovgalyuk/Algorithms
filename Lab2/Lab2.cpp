#include "Lab2.h"

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

ScoreVector tokenize(const std::string& text) {
	ScoreVector scores;
	int score{};

	for (char c : text) {
		if (std::isalpha(static_cast<unsigned char>(c))) {
			score += scrabbleValue(c);
		}
		else if (score != 0) {
			scores.push_back(score);
			score = 0;
		}
	}
	if (score != 0) {
		scores.push_back(score);
	}
	return scores;
}

void run(const ScoreVector& scores, std::istream& input, std::ostream& output) {
	Stack<int> stack;
	std::size_t ip = 0;

	while (ip < scores.size()) {
		auto score = scores[ip];
		++ip;

		switch (score) {
		case 5:
			if (ip < scores.size()) {
				stack.push(scores[ip] & 0xFF);
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
			if (ip < scores.size() && !stack.empty()) {
				auto n = scores[ip];
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
			if (ip < scores.size() && !stack.empty()) {
				auto n = scores[ip];
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
			if (ip < scores.size() && !stack.empty()) {
				auto n = scores[ip];
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond == 0 && n <= (int)ip) { 
					ip -= (n + 1); 
				}
				else { 
					++ip; 
				}
			}
			break;

		case 16:
			if (ip < scores.size() && !stack.empty()) {
				auto n = scores[ip];
				auto cond = stack.top(); stack.pop();
				++ip;

				if (cond != 0 && n <= (int)ip) {
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