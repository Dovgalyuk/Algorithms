#include "associative_array.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>

typedef int Key;
typedef int Value;
typedef std::milli Ratio;
typedef AssociativeArray<Key, Value> Array;

const std::string BETWEEN_KEY_AND_VALUE = "->";
const std::string INPUT_FILE_NAME = "../../../Algorithms/Fifth/input.txt";
const int MAX_CAPACITY = 1000000;
const int MIN_CAPACITY = 50000;
const int MAX_NUMBER = 1000000;

int generateCapacity() {
    return ((rand() + 1) * MIN_CAPACITY) % MAX_CAPACITY;
}

int generateNumber() {
    return rand() % MAX_NUMBER;
}

std::string keyAndValueToString(Key key, Value value) {
    return (std::to_string(key)) + BETWEEN_KEY_AND_VALUE + std::to_string(value);
}

std::pair<Key, Value> keyAndValueFromString(std::string str) {
    int betweenIndex = str.find(BETWEEN_KEY_AND_VALUE);
    return std::make_pair(std::stoi(str.substr(0, betweenIndex)), std::stoi(str.substr(betweenIndex + BETWEEN_KEY_AND_VALUE.length())));
}

void generateInputFile(std::string name, int length) {
    std::ofstream os(name);
    if (!os.is_open()) return;
    for (int i = 0; i < length; ++i) {
        os << keyAndValueToString(generateNumber(), generateNumber()) << std::endl;
    }
    os.flush();
    os.close();
}

void readFileToArray(std::string name, Array* array) {
    std::ifstream is(name);
    if (!is.is_open()) return;
    std::string line;
    while (std::getline(is, line)) {
        std::pair<Key, Value> keyAndValue = keyAndValueFromString(line);
        array->insert(keyAndValue.first, keyAndValue.second);
    }
}

void readFileToMap(std::string name, std::map<Key, Value>& map) {
    std::ifstream is(name);
    if (!is.is_open()) return;
    std::string line;
    while (std::getline(is, line)) {
        std::pair<Key, Value> keyAndValue = keyAndValueFromString(line);
        map[keyAndValue.first] = keyAndValue.second;
    }
}

std::pair<double, double> testAssociativeArrayVSMap(int length) {
    srand(time(0));
    std::cout << "Capacity is " << length << std::endl;
    generateInputFile(INPUT_FILE_NAME, length);

    auto *array = new Array();
    auto start = std::chrono::system_clock::now();
    readFileToArray(INPUT_FILE_NAME, array);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double, Ratio> readToArray = end - start;
    std::cout << "Reading from a file into an associative array took " << readToArray.count() << " milliseconds." << "\n";

    std::map<Key, Value> map;
    start = std::chrono::system_clock::now();
    readFileToMap(INPUT_FILE_NAME, map);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double, Ratio> readToMap = end - start;
    std::cout << "Reading from a file into an map took " << readToMap.count() << " milliseconds." << "\n";

    delete array;
    return std::make_pair(readToArray.count(), readToMap.count());
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
            createCell("array", valueColumnWidth),
            createCell("map", valueColumnWidth)});
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
    int TESTS_AMOUNT = 5;
    std::map<int, std::pair<double, double>> tests;
    for (int i = 0; i < TESTS_AMOUNT; ++i) {
        int length = generateCapacity();
        std::cout << "\n";
        std::pair<double, double> pair = testAssociativeArrayVSMap(length);
        std::cout << "\n";
        tests[length] = pair;
    }
    writeTests(tests);
    return 0;
}
/*
 * Пример графика, который выводится.
 *
length  | array      | map
=================================
100000  | 98.759000  | 74.776400
=================================
250000  | 238.392900 | 179.198800
=================================
350000  | 330.903000 | 247.434500
=================================
900000  | 879.831300 | 623.212200
=================================
950000  | 901.864800 | 656.120100
=================================
*/