#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "priorityqueue.h"
#include <iostream>
#include <string>
#include <unordered_map>

class Huffman {
public:
    Huffman() : root(nullptr) {}
    ~Huffman()
    { 
        deleteTree(root); 
    }
    void encode(std::istream& input, std::ostream& output) {
        buildTree(input);
        buildCodes(root, {});
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
    void buildCodes(Node* node, std::vector<bool> code) {
        if (!node) {
            return;
        }

        if (node->ch != '\0') {
            huffmanCode[node->ch] = code;
        }

        std::vector<bool> leftCode = code;
        leftCode.push_back(0);
        buildCodes(node->left, leftCode);

        std::vector<bool> rightCode = code;
        rightCode.push_back(1);
        buildCodes(node->right, rightCode);
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
        std::vector<bool> bitVector;
        while (input.get(ch)) {
            const std::vector<bool>& code = huffmanCode[ch];
            bitVector.insert(bitVector.end(), code.begin(), code.end());
        }

        // Записываем общее количество бит в начало файла
        int totalBits = (int)bitVector.size();
        output.write(reinterpret_cast<const char*>(&totalBits), sizeof(totalBits));

        // Кодирование битовой строки
        char byte = 0;
        int bitCount = 0;
        for (bool bit : bitVector) {
            byte = byte << 1 | (int)(bit);
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
        std::vector<bool> bitVector;
        int readBits = 0;

        Node* currentNode = root;
        while (input.read(&byte, sizeof(char)) && readBits < totalBits) {
            for (int i = 7; i >= 0 && readBits < totalBits; --i) {
                bool bit = (byte >> i) & 1;
                bitVector.push_back(bit);

                // Перемещаемся в дереве в соответствии с текущим битом
                if (bit) {
                    currentNode = currentNode->right;
                }
                else {
                    currentNode = currentNode->left;
                }

                // Если достигли листа, выводим символ и сбрасываем текущий узел в корень
                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    output << currentNode->ch;
                    currentNode = root;
                }

                readBits++;
            }
        }
    }
    PriorityQueue<Node*> minHeap;
    std::unordered_map<char, std::vector<bool>> huffmanCode;
    Node* root;
};
#endif