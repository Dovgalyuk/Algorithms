#include "beatnik.h"
#include "stack.h"

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef vector<string> Slova;

string read_file(const string& path) {
	ifstream f(path, ios::binary);
	if (!f) {
		throw runtime_error("Ошибка, невозможно открыть файл");
	}

	ostringstream stroka;
	stroka << f.rdbuf();
	return stroka.str();
}

Slova razbitie_stroki(const string& text) {
	Slova slova;
	string vib;

	for (char c : text) {
		if (isalpha(static_cast<unsigned char>(c))) {
			vib += c;
		}
		else if (!vib.empty()) {
			slova.push_back(vib);
			vib.clear();
		}
	}

	if (!vib.empty()) {
		slova.push_back(vib);
	}

	return slova;
}

int beatnik_scrabble_ochki(char c) {
	c = static_cast<char>(toupper(static_cast<unsigned char>(c)));

	switch (c) {
	case 'A': case 'E': case 'I': case 'L': case 'N': case 'O': case 'R': case 'S': case 'T': case 'U':
		return 1;
	case 'D': case 'G':
		return 2;
	case 'B' : case 'C' : case 'M' : case 'P':
		return 3;
	case 'F' : case 'H' : case 'V' : case 'W' : case 'Y':
		return 4;
	case 'K':
		return 5;
	case 'J': case 'X':
		return 8;
	case 'Q' : case 'Z':
		return 10;
	default:
		return 0;
	}
}

int beatnik_word_ochki(const char* word) {
	if (!word) {
		return 0;
	}
	int ochki = 0;
	for (const char* s = word; *s; s++) {
		ochki += beatnik_scrabble_ochki(*s);
	}
	return ochki;
}


int beatnik_start(const char* script_file, const char* input_file) {
	if (!script_file || !input_file) {
		cerr << "Ошибка, не удается открыть один из файлов" << endl;
		return 1;
	}

	Stack* stack = nullptr;

	try {
		const string script_text = read_file(script_file);
		const string input_text = read_file(input_file);

		Slova slova = razbitie_stroki(script_text);
		size_t kolvo_slov = slova.size();

		stack = stack_create();

		size_t ip = 0;
		size_t posizia = 0;

		while (ip < kolvo_slov) {
			const int ochki = beatnik_word_ochki(slova[ip].c_str());

			switch (ochki) {
			case 5: {
				if (ip + 1 >= kolvo_slov) {
					throw runtime_error("command 5: no argument word");
				}
				stack_push(stack, beatnik_word_ochki(slova[ip + 1].c_str()));
				ip += 2;
				break;
			}
			case 6: {
				if (!stack_empty(stack)) {
					stack_pop(stack);
				}
				++ip;
				break;
			}


			case 7: {
				if (stack_empty(stack)) {
					++ip;
					break;
				}
				int a = stack_get(stack);
				stack_pop(stack);
				if (stack_empty(stack)) {
					stack_push(stack, a);
					++ip;
					break;
				}
				int b = stack_get(stack);
				stack_pop(stack);
				stack_push(stack, a + b);
				++ip;
				break;
			}

			case 8: {
				if (posizia >= input_text.size()) {
					throw runtime_error("no more input");
				}
				stack_push(stack, static_cast<unsigned char>(input_text[posizia++]));
				++ip;
				break;
			}
			case 9: {
				if (!stack_empty(stack)) {
					int v = stack_get(stack);
					stack_pop(stack);
					cout << static_cast<char>(v);
				}
				++ip;
				break;
			}
			case 10: {
				if (stack_empty(stack)) {
					++ip;
					break;
				}
				int a = stack_get(stack);
				stack_pop(stack);
				if (stack_empty(stack)) {
					stack_push(stack, a);
					++ip;
					break;
				}
				int b = stack_get(stack);
				stack_pop(stack);
				stack_push(stack, b - a);
				++ip;
				break;
			}
			case 11: {
				if (stack_empty(stack)) {
					++ip;
					break;
				}
				int a = stack_get(stack);
				stack_pop(stack);
				if (stack_empty(stack)) {
					stack_push(stack, a);
					++ip;
					break;
				}
				int b = stack_get(stack);
				stack_pop(stack);
				stack_push(stack, a);
				stack_push(stack, b);
				++ip;
				break;
			}
			case 12: {
				if (!stack_empty(stack)) {
					stack_push(stack, stack_get(stack));
				}
				++ip;
				break;
			}
			case 13: case 14: case 15: case 16: {

				if (ip + 1 >= kolvo_slov) {
					throw runtime_error("jump commmand: no parametr");
				}
				const int n = beatnik_word_ochki(slova[ip + 1].c_str());

				int v = 0;
				if (!stack_empty(stack)) {
					v = stack_get(stack);
					stack_pop(stack);
				}

				bool propusk = false;
				if (ochki == 13 && v == 0) {
					propusk = true;
				}
				if (ochki == 14 && v != 0) {
					propusk = true;
				}
				if (ochki == 15 && v == 0) {
					propusk = true;
				}
				if (ochki == 16 && v != 0) {
					propusk = true;
				}

				if (propusk) {
					if (ochki == 13 || ochki == 14) {
						ip = ip + 2 + static_cast<size_t>(n);
					}
					else {
						ip = (static_cast<size_t>(n) > ip) ? 0 : ip - static_cast<size_t>(n);
					}
				}
				else {
					ip += 2;
				}
				break;
			}
			case 17:
				stack_delete(stack);
				stack = nullptr;
				return 0;
			default:
				++ip;
				break;
			}
		}

		stack_delete(stack);
		return 0;
	}
	catch (const exception& e) {
		if (stack) {
			stack_delete(stack);
		}
		cerr << "beatnik error: " << e.what() << endl;
		return 1;
	}
}