#ifndef BEATNIK_INTERPRETER_H
#define BEATNIK_INTERPRETER_H

#include "stack.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>

int scrabbleScore(const char* word) {
    if (!word) return 0;
    int score = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        char c = static_cast<char>(std::toupper(static_cast<unsigned char>(word[i])));
        if (c == 'A' || c == 'E' || c == 'I' || c == 'L' || c == 'N' ||
            c == 'O' || c == 'R' || c == 'S' || c == 'T' || c == 'U') {
            score += 1;
        }
        else if (c == 'D' || c == 'G') {
            score += 2;
        }
        else if (c == 'B' || c == 'C' || c == 'M' || c == 'P') {
            score += 3;
        }
        else if (c == 'F' || c == 'H' || c == 'V' || c == 'W' || c == 'Y') {
            score += 4;
        }
        else if (c == 'K') {
            score += 5;
        }
        else if (c == 'J' || c == 'X') {
            score += 8;
        }
        else if (c == 'Q' || c == 'Z') {
            score += 10;
        }
    }
    return score;
}

class BeatnikInterpreter {
private:
    Stack<char> stack;
    std::ifstream input_stream;

    char safePop() {
        if (stack.empty()) {
            std::cerr << "Error: Stack underflow" << std::endl;
            std::exit(1);
        }
        char c = stack.get();
        stack.pop();
        return c;
    }

    unsigned char readInputChar() {
        if (!input_stream.good()) {
            std::cerr << "Error: Input file exhausted" << std::endl;
            std::exit(1);
        }
        return static_cast<unsigned char>(input_stream.get());
    }

public:
    BeatnikInterpreter(const char* input_filename) {
        input_stream.open(input_filename, std::ios::binary);
        if (!input_stream.is_open()) {
            std::cerr << "Error: Cannot open input file: " << input_filename << std::endl;
            std::exit(1);
        }
    }

    ~BeatnikInterpreter() {
        if (input_stream.is_open()) {
            input_stream.close();
        }
    }

    void run(const char* script_filename) {
        std::ifstream script_file(script_filename);
        if (!script_file.is_open()) {
            std::cerr << "Error: Cannot open script file: " << script_filename << std::endl;
            std::exit(1);
        }

        const int MAX_WORDS = 1000;
        const int MAX_WORD_LEN = 100;
        char words[MAX_WORDS][MAX_WORD_LEN];
        int word_count = 0;

        while (script_file >> words[word_count]) {
            word_count++;
            if (word_count >= MAX_WORDS) break;
        }
        script_file.close();

        int ip = 0;
        while (ip < word_count) {
            int score = scrabbleScore(words[ip]);
            ip++;

            if (score < 5) {
                return;
            }

            if (score == 5) {
                if (ip >= word_count) {
                    std::cerr << "Error: No next word for command 5" << std::endl;
                    std::exit(1);
                }
                int nextScore = scrabbleScore(words[ip]);
                stack.push(static_cast<char>(nextScore));
                ip++;
            }
            else if (score == 6) {
                safePop();
            }
            else if (score == 7) {
                unsigned char a = static_cast<unsigned char>(safePop());
                unsigned char b = static_cast<unsigned char>(safePop());
                stack.push(static_cast<char>((a + b) % 256));
            }
            else if (score == 8) {
                unsigned char c = readInputChar();
                stack.push(static_cast<char>(c));
            }
            else if (score == 9) {
                char c = safePop();
                std::cout << c;
                std::cout.flush();
            }
            else if (score == 10) {
                unsigned char a = static_cast<unsigned char>(safePop());
                unsigned char b = static_cast<unsigned char>(safePop());
                int diff = static_cast<int>(b) - static_cast<int>(a);
                unsigned char res = static_cast<unsigned char>((diff % 256 + 256) % 256);
                stack.push(static_cast<char>(res));
            }
            else if (score == 11) {
                unsigned char a = static_cast<unsigned char>(safePop());
                unsigned char b = static_cast<unsigned char>(safePop());
                stack.push(static_cast<char>(a));
                stack.push(static_cast<char>(b));
            }
            else if (score == 12) {
                unsigned char a = static_cast<unsigned char>(safePop());
                stack.push(static_cast<char>(a));
                stack.push(static_cast<char>(a));
            }
            else if (score == 13) {
                unsigned char n = static_cast<unsigned char>(safePop());
                if (n == 0) {
                    ip += (n + 1);
                }
            }
            else if (score == 14) {
                unsigned char n = static_cast<unsigned char>(safePop());
                if (n != 0) {
                    ip += (n + 1);
                }
            }
            else if (score == 15) {
                unsigned char n = static_cast<unsigned char>(safePop());
                if (n == 0 && ip >= n) {
                    ip -= n;
                }
            }
            else if (score == 16) {
                unsigned char n = static_cast<unsigned char>(safePop());
                if (n != 0 && ip >= n) {
                    ip -= n;
                }
            }
            else if (score == 17) {
                return;
            }
        }
    }
};

#endif // BEATNIK_INTERPRETER_H