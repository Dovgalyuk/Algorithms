#ifndef BEATNIK_INTERPRETER_H
#define BEATNIK_INTERPRETER_H

#include "stack.h"      // Ваш шаблонный Stack<char>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>      // для exit

// Вспомогательная функция: вычисление стоимости слова по Scrabble
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
        // Игнорируем всё остальное (цифры, пунктуация и т.д.)
    }
    return score;
}

class BeatnikInterpreter {
private:
    Stack<char> stack;
    std::ifstream input_stream;

    // Безопасное извлечение из стека
    char safePop() {
        if (stack.empty()) {
            std::cerr << "Error: Stack underflow" << std::endl;
            std::exit(1);
        }
        char c = stack.get();
        stack.pop();
        return c;
    }

    // Безопасное чтение символа из входного файла
    char readInputChar() {
        if (!input_stream.good()) {
            std::cerr << "Error: Input file exhausted" << std::endl;
            std::exit(1);
        }
        return static_cast<char>(input_stream.get());
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

        // Массив слов (макс. 1000 слов, каждое до 100 символов — достаточно для тестов)
        const int MAX_WORDS = 1000;
        const int MAX_WORD_LEN = 100;
        char words[MAX_WORDS][MAX_WORD_LEN];
        int word_count = 0;

        // Чтение всех слов из скрипта
        while (script_file >> words[word_count]) {
            word_count++;
            if (word_count >= MAX_WORDS) break;
        }
        script_file.close();

        int ip = 0; // instruction pointer
        while (ip < word_count) {
            int score = scrabbleScore(words[ip]);
            ip++; // переходим к следующему слову (для команд, требующих "следующее слово")

            if (score < 5) {
                return; // остановка программы
            }

            if (score == 5) {
                char c = readInputChar();
                stack.push(c);
            }
            else if (score == 6) {
                safePop(); // отбрасываем
            }
            else if (score == 7) {
                char a = safePop();
                char b = safePop();
                unsigned char res = (static_cast<unsigned char>(a) + static_cast<unsigned char>(b)) % 256;
                stack.push(static_cast<char>(res));
            }
            else if (score == 8) {
                char a = safePop(); // верх стека (первый)
                char b = safePop(); // следующий (второй)
                // Вычисляем: a - b (как в спецификации: "из первого вычитается второе")
                int diff = static_cast<int>(static_cast<unsigned char>(a)) -
                    static_cast<int>(static_cast<unsigned char>(b));
                unsigned char res = static_cast<unsigned char>((diff % 256 + 256) % 256);
                stack.push(static_cast<char>(res));
            }
            else if (score == 9) {
                char c = safePop();
                std::cout << c;
                std::cout.flush();
            }
            else if (score == 10) {
                char c = safePop();
                if (static_cast<unsigned char>(c) == 0) {
                    if (ip < word_count) {
                        ip++; // пропустить следующее слово
                    }
                }
            }
            else if (score >= 11 && score <= 17) {
                if (ip >= word_count) {
                    std::cerr << "Error: No next word for jump command" << std::endl;
                    std::exit(1);
                }
                int nextScore = scrabbleScore(words[ip]);
                ip++; // потребляем следующее слово
                ip += nextScore; // переход: ip += nextScore (уже увеличили ip выше)
                // Защита от выхода за границы
                if (ip < 0) ip = 0;
                if (ip > word_count) ip = word_count;
            }
            else if (score >= 18) {
                if (ip >= word_count) {
                    std::cerr << "Error: No next word to push" << std::endl;
                    std::exit(1);
                }
                char firstChar = words[ip][0];
                if (firstChar == '\0') firstChar = '\0';
                stack.push(firstChar);
                ip++; // потребляем следующее слово
            }
        }
    }
};

#endif // BEATNIK_INTERPRETER_H