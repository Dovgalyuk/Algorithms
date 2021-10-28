//
// Created by KirilliriK on 21.10.2021.
//

#ifndef ALGORITHMS_AVLTREE_H
#define ALGORITHMS_AVLTREE_H

#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>


class AVLTree {
public:
    struct Node {
        static const char SPACE_CHAR = '.';

        size_t key;
        std::string str;
        size_t height;
        Node *left;
        Node *right;
        Node(size_t key, std::string str) {
            this->str = std::move(str);
            this->key = key;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
        Node(size_t key) {
            str = "";
            this->key = key;
            height = 1;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }

        int getLeftWidth() {
            return left != nullptr ? left->getWidth() : 1;
        }

        int getRightWidth() {
            return right != nullptr ? right->getWidth() : 1;
        }

        int getWidth() {
            int leftWidth = getLeftWidth();
            int rightWidth = getRightWidth();
            return std::max(leftWidth, rightWidth) * 2 + 1;
        }

        std::vector<std::string> printNode(Node &root, int maxWidth) {
            std::vector<std::string> strings;
            std::string spaces = std::string(maxWidth, SPACE_CHAR);
            std::string numberString  = spaces + std::to_string(root.key) + spaces;
            strings.push_back(numberString);

            int lastWidth = 0;
            for (int i = 1; i < maxWidth / 2 + 1; i++) {
                std::string string = std::string(numberString.size(), SPACE_CHAR);
                if (root.left != nullptr)
                    string.at(spaces.size() - i) = '/';
                if (root.right != nullptr)
                    string.at(spaces.size() + i) = '\\';
                strings.push_back(string);
                lastWidth = spaces.size() - i - 1;
            }

            std::vector<std::string> leftStrings;
            std::vector<std::string> rightStrings;
            if (root.left != nullptr)
                leftStrings = printNode(*root.left, lastWidth);
            if (root.right != nullptr)
                rightStrings = printNode(*root.right, lastWidth);

            size_t max = std::max(leftStrings.size(), rightStrings.size());
            for (int i = 0; i < max; i++) {
                std::string lStr = i < leftStrings.size() ? leftStrings[i] : spaces;
                std::string rStr = i < rightStrings.size() ? rightStrings[i] : spaces;
                std::string string;
                string += lStr;
                string += SPACE_CHAR;
                string += rStr;
                strings.push_back(string);
            }
            return strings;
        }
    };

    AVLTree();
    void addNode(std::string &str);
    Node *findNode(std::string &str);
    void removeNode(std::string &str);

    /// Testing
    void addNode(size_t key);
    Node *findNode(size_t key);
    void removeNode(size_t key);

    void clear();

    void print();
    std::vector<std::string> getPrintLog();

    static size_t hash(std::string &str);
private:
    Node *middle;

    int nodeHeight(Node *node);
    int balanceFactor(Node *node);
    void updateHeight(Node *node);
    Node *rotateLeft(Node *node);
    Node *rotateRight(Node *node);
    Node *balance(Node *node);
    Node *insert(Node *node, size_t key, std::string &str);
    Node *findMinimal(Node *node);
    Node *setMinimal(Node *node);
    Node *remove(Node *node, size_t key);

    Node *find(Node *node, size_t key);
    void print(Node *node, size_t space);

    //debug
    Node *insert(Node *node, size_t key);

    int maxSpace = 10;
};


#endif //ALGORITHMS_AVLTREE_H
