#include <iostream>
#include "associative_array.h"
#include <vector>
#include <fstream>

typedef AssociativeArray<int, int> Array;

typedef AssociativeArray<int, int> Array;

int getNodeWidth(Array::Node* node);
int getNodeLessWidth(Array::Node* less);
int getNodeMoreWidth(Array::Node* more);

std::string getNodeTitle(Array::Node* node) {
    return std::to_string(node->key);
}

int getNodeWidth(Array::Node* node) {
    return getNodeLessWidth(node->less) + (getNodeTitle(node).length()) + getNodeMoreWidth(node->more);
}

int getNodeLessWidth(Array::Node* less) {
    return (less != nullptr) ? getNodeWidth(less) : 1;
}

int getNodeMoreWidth(Array::Node* more) {
    return (more != nullptr) ? getNodeWidth(more) : 1;
}

std::vector<std::string> getNodeDrawingStrings(Array::Node* node, bool is_left = false, bool is_right = false) {
    char SPACE = ' ';
    std::vector<std::string> strings;
    int left_width = getNodeLessWidth(node->less);
    int right_width = getNodeMoreWidth(node->more);
    std::string left_space = std::string(left_width, SPACE);
    std::string right_space = std::string(right_width, SPACE);
    std::string title = getNodeTitle(node);
    std::string first = left_space + title + right_space;

    bool lite = true;

    if (is_left) {
        if (lite) {
            std::string str(first.length() - right_width, SPACE);
            str.append("/");
            if (right_width > 2) {
                str.append(std::string(right_width - 2, '='));
            }
            if (right_width > 1) {
                str.append("/");
            }
            strings.push_back(str);
        } else {
            for (int i = 0; i < right_width; ++i) {
                strings.push_back(std::string(first.size() - i - 1, SPACE) + "/" + std::string(i, SPACE));
            }
        }
    } else if (is_right) {
        if (lite) {
            std::string str("\\");
            if (left_width > 2) {
                str.append(std::string(left_width - 2, '='));
            }
            if (left_width > 1) {
                str.append("\\");
            }
            str.append(first.length() - left_width, SPACE);
            strings.push_back(str);
        } else {
            for (int i = 0; i < left_width; ++i) {
                strings.push_back(std::string(i, SPACE) + '\\' + std::string(first.size() - i - 1, SPACE));
            }
        }
    }

    strings.push_back(first);

    std::vector<std::string> left_strings;
    if (node->less) left_strings = getNodeDrawingStrings(node->less, true);

    std::vector<std::string> right_strings;
    if (node->more) right_strings = getNodeDrawingStrings(node->more, false, true);

    for (int i = 0; i < std::max(left_strings.size(), right_strings.size()); ++i) {
        std::string left_string = (i < left_strings.size()) ? left_strings[i] : left_space;
        std::string right_string = (i < right_strings.size()) ? right_strings[i] : right_space;
        strings.push_back(left_string + std::string(title.length(), SPACE) + right_string);
    }
    return strings;
}

void writeArray(Array* array, int id) {
    if (!array->main) {
        std::cout << "array is empty";
        return;
    }
    std::ofstream os("../../../log" + std::to_string(id) + ".txt");
    if (!os.is_open()) {
        return;
    }
    std::vector<std::string> output = getNodeDrawingStrings(array->main);
    for (const auto &item : output) {
        os << item << "\n";
    }
    os.flush();
    os.close();
}

int main() {
    Array array;
    int count = 10;
    for (size_t i = 0; i < count; i++)
    {
        array.insert(i, i);
        if (!array.isCorrectAVLTree()) {
            std::cout << "Incorrect adding to an associative array.";
            return 1;
        }
    }

    writeArray(&array, -1);

    for (int i = 0; i < 15; ++i) {
        int key = rand() % (count * 2);
        if ((array.find(key) == key) != (key < count)) {
            std::cout << "Invalid search on associative array.";
            return 1;
        }
    }

    array.remove(7);
    writeArray(&array, 1);

//    for (size_t i = 0; i < count; i++)
//    {
//        array.remove(i);
//        writeArray(&array, i);
//        if (!array.isCorrectAVLTree()) {
//            std::cout << "Incorrect deletion from an associative array. ";
//            return 1;
//        }
//    }


//
//    if (!array.isEmpty()) {
//        std::cout << "Incorrect deletion from an associative array. ";
//        return 1;
//    }
//
//    std::vector<int> keys;
//
//    for (int i = 0; i < count; ++i) {
//        int num = rand();
//        keys.push_back(num);
//        array.insert(num, num);
//        if (!array.isCorrectAVLTree()) {
//            std::cout << "Incorrect adding to an associative array.";
//            return 1;
//        }
//    }
//
//    std::vector<int> removedKeys;
//
//    for (size_t i = 0; i < count; i++)
//    {
//        int id = rand() % keys.size();
//        int key = keys[id];
//        keys.erase(keys.begin() + id);
//        array.remove(key);
//        removedKeys.push_back(key);
//        if (!array.isCorrectAVLTree()) {
//            std::cout << "Incorrect deletion from an associative array. ";
//            return 1;
//        }
//    }
//
//    if (!array.isEmpty()) {
//        std::cout << "Incorrect deletion from an associative array. ";
//        return 1;
//    }

    return 0;
}