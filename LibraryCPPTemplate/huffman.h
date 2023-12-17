#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "priorityqueue.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Huffman {
public:
    Huffman() : root(nullptr) {}
    void encode(std::istream& input, std::ostream& output) {
        buildTree(input);
        buildCodes(root, "");
        writeEncodedData(input, output);
        deleteTree(root);
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

        // Обработка случая с одним уникальным символом
        if (freqs.size() == 1) {
            // Добавляем фиктивный узел
            minHeap.insert(new Node('\0', 0), 0);
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
        std::string bitString;
        while (input.get(ch)) {
            bitString += huffmanCode[ch];
        }

        // Записываем общее количество бит в начало файла
        int totalBits = (int)bitString.length();
        output.write(reinterpret_cast<const char*>(&totalBits), sizeof(totalBits));

        // Кодирование битовой строки
        char byte = 0;
        int bitCount = 0;
        for (char bit : bitString) {
            byte = byte << 1 | (bit == '1');
            bitCount++;
            if (bitCount == 8) {
                output.write(&byte, sizeof(char));
                byte = 0;
                bitCount = 0;
            }
        }

        // Обработка последнего байта, если он не полный
        if (bitCount > 0) {
            byte <<= (8 - bitCount);
            output.write(&byte, sizeof(char));
        }
    }
    void readEncodedData(std::istream& input, std::ostream& output) {
        // Читаем общее количество бит из начала файла
        int totalBits;
        input.read(reinterpret_cast<char*>(&totalBits), sizeof(totalBits));

        char byte;
        std::string bitString;
        int readBits = 0;

        while (input.read(&byte, sizeof(char)) && readBits < totalBits) {
            for (int i = 7; i >= 0 && readBits < totalBits; --i) {
                bitString.push_back(((byte >> i) & 1) ? '1' : '0');
                readBits++;
            }
        }

        // Декодирование битовой строки
        std::string code;
        for (char bit : bitString) {
            code += bit;
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