#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "priorityqueue.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Huffman {
public:
    Huffman() : root(nullptr) {}
    ~Huffman() {
        deleteTree(root);
    }
    void encode(std::istream& input, std::ostream& output) {
        buildTree(input);
        buildCodes(root, "");
        writeEncodedData(input, output);
    }
    void decode(std::istream& input, std::ostream& output) {
        readEncodedData(input, output);
    }

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

    void buildTree(std::istream& input) {
        std::unordered_map<char, int> freqs;
        char ch;
        while (input.get(ch)) {
            freqs[ch]++;
        }

        for (const auto& pair : freqs) {
            minHeap.insert(new Node(pair.first, pair.second), pair.second);
        }

        while (minHeap.size() > 1) {
            Node* left = minHeap.extractMin();
            Node* right = minHeap.extractMin();
            Node* parent = new Node('\0', left->freq + right->freq, left, right);
            minHeap.insert(parent, parent->freq);
        }

        root = minHeap.extractMin();
    }
    void buildCodes(Node* node, const std::string& str) {
        if (!node) {
            return;
        }

        if (node->ch != '\0') {
            huffmanCode[node->ch] = str;
            reverseCode[str] = node->ch;
        }

        buildCodes(node->left, str + "0");
        buildCodes(node->right, str + "1");
    }
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }
    void writeEncodedData(std::istream& input, std::ostream& output) {
        input.clear();
        input.seekg(0);
        char ch;
        while (input.get(ch)) {
            output << huffmanCode[ch];
        }
    }
    void readEncodedData(std::istream& input, std::ostream& output) {
        std::string encodedString;
        getline(input, encodedString);
        std::string code;
        for (char ch : encodedString) {
            code += ch;
            if (reverseCode.find(code) != reverseCode.end()) {
                output << reverseCode[code];
                code.clear();
            }
        }
    }

    PriorityQueue<Node*> minHeap;
    std::unordered_map<char, std::string> huffmanCode;
    std::unordered_map<std::string, char> reverseCode;
    Node* root;
};
#endif