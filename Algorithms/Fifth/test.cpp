
#include "associative_array.h"
#include <iostream>
#include <string>
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
    return (rand() * MIN_CAPACITY) % MAX_CAPACITY;
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

int main() {
    srand(0);

    int length = generateCapacity();
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
    return 0;
}