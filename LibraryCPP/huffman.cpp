#include "huffman.h"
#include <sstream>
#include <bitset>

Huffman::Huffman() : root(nullptr) {}

void Huffman::encode(std::istream& input, std::ostream& output) {
    buildTree(input);
    buildCodes(root, "");
    writeEncodedData(input, output);
    deleteTree(root);
}

void Huffman::decode(std::istream& input, std::ostream& output) {
    readEncodedData(input, output);
}

void Huffman::buildTree(std::istream& input) {
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

void Huffman::buildCodes(Node* node, const std::string& str) {
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

void Huffman::deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void Huffman::writeEncodedData(std::istream& input, std::ostream& output) {
    input.clear();
    input.seekg(0);
    char ch;
    while (input.get(ch)) {
        output << huffmanCode[ch];
    }
}

void Huffman::readEncodedData(std::istream& input, std::ostream& output) {
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