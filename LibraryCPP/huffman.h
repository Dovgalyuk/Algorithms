#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "priorityqueue.h"
#include <iostream>
#include <unordered_map>

class Huffman {
public:
    Huffman();
    void encode(std::istream& input, std::ostream& output);
    void decode(std::istream& input, std::ostream& output);

private:
    struct Node {
        char ch;
        int freq;
        Node* left, * right;

        Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
            : ch(ch), freq(freq), left(left), right(right) {}

        bool operator>(const Node& other) const {
            return freq > other.freq;
        }
    };

    void buildTree(std::istream& input);
    void buildCodes(Node* node, const std::string& str);
    void deleteTree(Node* node);
    void writeEncodedData(std::istream& input, std::ostream& output);
    void readEncodedData(std::istream& input, std::ostream& output);

    PriorityQueue<Node*> minHeap; 
    std::unordered_map<char, std::string> huffmanCode;
    std::unordered_map<std::string, char> reverseCode;
    Node* root;
};
#endif