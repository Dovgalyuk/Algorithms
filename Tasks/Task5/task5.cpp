#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "associative_array.h"

typedef int Key;
typedef int Value;
typedef std::milli Ratio;
typedef AssociativeArray<Value> Array;

const int MAX_CAPACITY = 1000000;
const int MIN_CAPACITY = 50000;
const int MAX_NUMBER = 1000000;
const int numberOfRequiredNumbers = 10;

class Table {
public:
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;

    void write() {
        int lengths[headers.size()];
        for (const auto &row : rows) {
            for (int i = 0; i < row.size(); ++i) {
                lengths[i] = row[i].length();
            }
        }
        std::vector<std::string> headCells;
        for (int i = 0; i < headers.size(); ++i) {
            std::string cell = createCell(headers[i], lengths[i]);
            int len = cell.length();
            if (lengths[i] < len) {
                lengths[i] = len;
            }
            headCells.push_back(cell);
        }
        std::string header = createTableRow(headCells);
        std::string rowSeparator = std::string(header.length(), '=');
        writeRow(header, rowSeparator);

        for (const auto &row : rows) {
            std::vector<std::string> cells;
            for (int i = 0; i < row.size(); ++i) {
                cells.push_back(createCell(row[i], lengths[i]));
            }
            std::string rowTable = createTableRow(cells);
            writeRow(rowTable, rowSeparator);
        }
    }

private:
    void writeRow(std::string row, const std::string& separator) {
        std::cout << row << "\n";
        std::cout << separator << "\n";
    }

    std::string createTableRow(const std::vector<std::string>& strings) {
        std::string sep = " | ";
        std::string result;
        for (const auto &item : strings) {
            result += sep;
            result += item;
        }
        return result.substr(sep.length());
    }

    std::string createCell(std::string value, int minLength) {
        int diff = minLength - value.length();
        int first = diff / 2;
        if (diff > 0) {
            return std::string (first, ' ') + value + std::string (diff - first, ' ');
        }
        return value;
    }

};

int generateNumber() {
    return rand() % MAX_NUMBER;
}

int* generateBuffer(int length) {
    int* buffer = new int[length];
    for (int i = 0; i < length; ++i) {
        buffer[i] = generateNumber();
    }
    return buffer;
}

Table* initTable() {
    Table *table = new Table();
    table->headers = {"length", "array-insert", "map-insert", "array-find", "map-find"};
    return table;
}

void pushTable(Table* table, int length, double arrayInsertTime, double mapInsertTime, double arrayFindTime, double mapFindTime) {
    table->rows.push_back({
        std::to_string(length),
        std::to_string(arrayInsertTime),
        std::to_string(mapInsertTime),
        std::to_string(arrayFindTime),
        std::to_string(mapFindTime)
    });
}

void testInsertAssociativeArrayVSMap(int length, Table* table) {
    srand(time(0));
    std::cout << "Capacity is " << length << std::endl;
    int* buffer = generateBuffer(length);

    auto *array = new Array();
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < length; ++i) {
        array->insert(i, buffer[i]);
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double, Ratio> insertToArray = end - start;
    std::cout << "Adding to the associative array took " << insertToArray.count() << " milliseconds." << "\n";

    std::map<Key, Value> map;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < length; ++i) {
        map[i] = buffer[i];
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double, Ratio> insertToMap = end - start;
    std::cout << "Adding to the map took " << insertToMap.count() << " milliseconds." << "\n";

    int numbers[numberOfRequiredNumbers];
    for (int i = 0; i < numberOfRequiredNumbers; ++i) {
        numbers[i] = length / numberOfRequiredNumbers * i;
    }

    start = std::chrono::system_clock::now();
    for (const auto &item : numbers) {
        int result = array->find(item);
        if (result == NULL) {
            std::cout << "The associative array search ERROR." << "\n";
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double, Ratio> findInArray = end - start;
    std::cout << "The associative array search took " << findInArray.count() << " milliseconds." << "\n";

    start = std::chrono::system_clock::now();
    for (const auto &item : numbers) {
        if (map.find(item) == map.end()) {
            std::cout << "The map search ERROR." << "\n";
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double, Ratio> findInMap = end - start;
    std::cout << "The map search took " << findInMap.count() << " milliseconds." << "\n";

    delete array;
    pushTable(table, length, insertToArray.count(), insertToMap.count(), findInArray.count(), findInMap.count());
}

int main() {
    Table* table = initTable();
    for (int i = MIN_CAPACITY; i <= MAX_CAPACITY; i+=MIN_CAPACITY) {
        std::cout << "\n";
        testInsertAssociativeArrayVSMap(i, table);
        std::cout << "\n";
    }
    table->write();
    delete table;
    return 0;
}