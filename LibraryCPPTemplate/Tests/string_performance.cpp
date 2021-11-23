#include <iostream>
#include "string.h"
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>

const std::string BETWEEN_KEY_AND_VALUE = "->";
const int MAX_CAPACITY = 1000000;
const int MIN_CAPACITY = 50000;
const int MAX_NUMBER = 1000000;
const int FIRST_CHAR_ID = 33;
const int LAST_CHAR_ID = 126;

int generateLength() {
    return ((rand() + 1) * MIN_CAPACITY) % MAX_CAPACITY;
}

char* generateString(int length) {
    char* chars = new char[length];
    for (int i = 0; i < length; ++i) {
        chars[i] = (char) ((rand() % (LAST_CHAR_ID - FIRST_CHAR_ID)) + FIRST_CHAR_ID);
    }
    return chars;
}

std::pair<double, double> test_stl_string_vs_string(char* chars, size_t length) {
    String string(chars, length);
    std::string stl_string = chars;
    std::pair<double, double> pair = std::make_pair(0,0);

    int searching_length = length / 2;
    int first_symbol = searching_length / 2;
    char searching[searching_length];
    for (int i = 0; i < searching_length; ++i) {
        searching[i] = chars[i + first_symbol];
    }

    auto start = std::chrono::system_clock::now();
    int answer = string.findString(String(searching, searching_length));
    pair.first = std::chrono::duration<double, std::micro>(std::chrono::system_clock::now() - start).count();
    if (answer != first_symbol) {
        std::cout << "String search does not work correctly." << answer << "\n";
        return pair;
    }

    start = std::chrono::system_clock::now();
    searching[searching_length - 1] = '\0';
    answer = stl_string.find(searching);
    pair.second = std::chrono::duration<double, std::micro>(std::chrono::system_clock::now() - start).count();
    if (answer != first_symbol) {
        std::cout << "STL string search does not work correctly." << answer << "\n";
        return pair;
    }
    return pair;
}

void writeRow(std::string row, std::string separator) {
    std::cout << row << "\n";
    std::cout << separator << "\n";
}

std::string createTableRow(std::vector<std::string> strings) {
    std::string sep = " | ";
    std::string result = "";
    for (const auto &item : strings) {
        result += sep;
        result += item;
    }
    return result.substr(sep.length());
}

std::string createCell(std::string value, int minLength) {
    int diff = minLength - value.length();
    if (diff > 0) {
        return value + std::string (diff, ' ');
    }
    return value;
}

std::string createCell(double value, int minLength) {
    return createCell(std::to_string(value), minLength);
}

std::string createCell(int value, int minLength) {
    return createCell(std::to_string(value), minLength);
}

void writeTests(std::map<int, std::pair<double, double>> tests) {
    int lengthColumnWidth = std::to_string(MAX_CAPACITY).length();
    int valueColumnWidth = 0;
    for (const auto &item : tests) {
        int lengthArrayTestColumn = std::to_string(item.second.first).length();
        int lengthMapTestColumn = std::to_string(item.second.second).length();
        if (lengthArrayTestColumn > valueColumnWidth) {
            valueColumnWidth = lengthArrayTestColumn;
        }
        if (lengthMapTestColumn > valueColumnWidth) {
            valueColumnWidth = lengthMapTestColumn;
        }
    }
    std::string header = createTableRow({
                                                createCell("length", lengthColumnWidth),
                                                createCell("string (micro)", valueColumnWidth),
                                                createCell("str_string (micro)", valueColumnWidth)});
    std::string rowSeparator = std::string(header.length(), '=');
    writeRow(header, rowSeparator);
    for (const auto &item : tests) {
        std::string row = createTableRow({
                                                 createCell(item.first, lengthColumnWidth),
                                                 createCell(item.second.first, valueColumnWidth),
                                                 createCell(item.second.second, valueColumnWidth)});
        writeRow(row, rowSeparator);
    }
}

int main() {
    srand(time(0));
    int TESTS_AMOUNT = 5;
    std::map<int, std::pair<double, double>> tests;
    for (int i = 1; i < 21; ++i) {
        int length = 50000 * i;
        char* chars = generateString(length);
        std::pair<double, double> pair = test_stl_string_vs_string(chars, length);
        tests[length] = pair;
    }
    writeTests(tests);
    return 0;
}