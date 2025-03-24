#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <cctype>    
#include "stack.h"   

using namespace std;

// Функция для преобразования строки к нижнему регистру
string to_lower(const string& str) {
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); }); 
    return lower_str;
}

// Функция для проверки, является ли тег открывающим
bool is_opening_tag(const string& tag) {
    return tag[1] != '/';
}

// Функция для получения закрывающего тега из открывающего
string get_closing_tag(const string& opening_tag) {
    return "</" + opening_tag.substr(1);
}

// Функция для проверки корректности последовательности HTML-тегов
bool check_html_tags(ifstream& input) {
    Stack* stack = stack_create();  
    string line;

    while (getline(input, line)) {
        
        line.erase(0, line.find_first_not_of(' '));
        line.erase(line.find_last_not_of(' ') + 1);

        if (line.empty()) continue; 

        if (is_opening_tag(line)) {
            
            stack_push(stack, to_lower(line));
        } else {
            
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;  
            }

            string top_tag = stack_get(stack);
            string expected_closing_tag = get_closing_tag(top_tag);

            if (to_lower(line) != to_lower(expected_closing_tag)) {
                stack_delete(stack);
                return false;  
            }

            stack_pop(stack);  
        }
    }

    // Если стек пуст, последовательность корректна
    bool result = stack_empty(stack);
    stack_delete(stack);
    return result;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // Проверка аргументов командной строки
    if (argc < 3) {
        cerr << "Ошибка: укажите путь к входному и выходному файлам." << endl;
        return 1;
    }

    // Открытие входного файла
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть входной файл " << argv[1] << endl;
        return 1;
    }

    // Открытие выходного файла
    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Ошибка: не удалось открыть выходной файл " << argv[2] << endl;
        inputFile.close();
        return 1;
    }

    // Проверка корректности HTML-тегов
    if (check_html_tags(inputFile)) {
        outputFile << "YES" << endl;
    } else {
        outputFile << "NO" << endl;
    }

    // Закрытие файлов
    inputFile.close();
    outputFile.close();
    return 0;
}