#ifndef HUFFMAN_TEMPLATE_H
#define HUFFMAN_TEMPLATE_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdint>

#include "customPriorityQueue.h"


// Класс архиватора для кодирования и декодирования алогоритмом Хаффмана
class HuffmanArchiv {
public:
    // Структура узла дерева Хаффмана
    // ch - символ, freq - частота повторения
    struct Node {
        unsigned char ch;
        uint64_t freq;
        Node* left = nullptr;
        Node* right = nullptr;

        // Конструктор листа
        Node(unsigned char c, uint64_t f) : ch(c), freq(f) {}
        // Конструктор внутреннего узла
        Node(uint64_t f, Node* l, Node* r) : ch(0), freq(f), left(l), right(r) {}

        ~Node() {
            delete left;
            delete right;
        }

        bool is_leaf() const { return !left && !right; }
    };

    // Функтор сравнения узлов (Min-Heap по частоте)
    struct NodeCompare {
        bool operator()(const Node* a, const Node* b) const {
            return a->freq < b->freq;
        }
    };

    // Класс для побитовой записи
    class BitWrite {
    public:
        explicit BitWrite(std::ostream& os) : _out(os) {}

        // Записывает один бит
        void write_bit(bool bit) {
            _buffer = (_buffer << 1) | bit;
            _bit_count++;
            if (_bit_count == 8) {
                _out.put(_buffer);
                _bit_count = 0;
            }
        }

        // Записывает один байт
        void write_byte(unsigned char byte) {
            for (int i = 7; i >= 0; --i) {
                write_bit((byte >> i) & 1);
            }
        }

        // Сбрасывает буфер (дописывает нули)
        void flush() {
            if (_bit_count) _out.put(_buffer << (8 - _bit_count));
        }

    private:
        std::ostream& _out;
        unsigned char _buffer = 0;
        int _bit_count = 0;
    };

    // Класс для побитового чтения
    class BitRead {
    public:
        explicit BitRead(std::istream& is) : _in(is) {}

        // Читает один бит
        bool read_bit() {
            if (_bit_count == 0) {
                _buffer = _in.get();

                _bit_count = 8;
            }
            return (_buffer >> --_bit_count) & 1;
        }

        // Читает один байт
        unsigned char read_byte() {
            unsigned char byte = 0;
            for (int i = 0; i < 8; ++i) {
                byte = (byte << 1) | read_bit();
            }

            return byte;
        }

    private:
        std::istream& _in;
        unsigned char _buffer = 0;
        int _bit_count = 0;
    };

    HuffmanArchiv() = default;

    // Сжимает данные из входного потока в выходной
    void compress(std::istream& in, std::ostream& out) {
        // 1. Подсчет частот
        std::map<unsigned char, uint64_t> frequencies;
        char byte;
        uint64_t total_chars = 0;

        while (in.get(byte)) {
            frequencies[static_cast<unsigned char>(byte)]++;
            total_chars++;
        }

        if (frequencies.empty()) return;

        // 2. Построение дерева
        CustomPriorityQueue<Node*, NodeCompare> pq;
        for (const auto& pair : frequencies) {
            pq.push(new Node(pair.first, pair.second));
        }

        if (pq.size() == 1) {
            Node* child = pq.top(); pq.pop();
            pq.push(new Node(child->freq, child, new Node(0, 0)));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            pq.push(new Node(left->freq + right->freq, left, right));
        }

        Node* root = pq.top();

        // 3. Генерация кодов
        CodeMap codes;
        std::vector<bool> current_code;
        generate_codes(root, current_code, codes);

        // 4. Запись заголовка
        out.write(reinterpret_cast<const char*>(&total_chars), sizeof(total_chars));

        BitWrite bw(out);
        write_tree(root, bw);

        // 5. Запись тела
        in.clear();
        in.seekg(0);

        while (in.get(byte)) {
            const auto& code = codes[static_cast<unsigned char>(byte)];
            for (bool bit : code) {
                bw.write_bit(bit);
            }
        }
        bw.flush();

        delete root;
    }

    // Распаковывает данные из входного потока в выходной
    void decompress(std::istream& in, std::ostream& out) {
        // 1. Чтение заголовка
        uint64_t total_chars = 0;
        in.read(reinterpret_cast<char*>(&total_chars), sizeof(total_chars));
        if (in.gcount() != sizeof(total_chars)) return;

        BitRead br(in);

        // 2. Восстановление дерева и расшифровка
        Node* root = read_tree(br);

        Node* current = root;
        uint64_t decoded_count = 0;

        while (decoded_count < total_chars) {
            bool bit = br.read_bit();

            if (bit == 0) {
                current = current->left;
            }
            else {
                current = current->right;
            }

            if (!current) {
                delete root;
                return;
            }

            if (current->is_leaf()) {
                out.put(static_cast<char>(current->ch));
                current = root;
                decoded_count++;
            }
        }

        delete root;
    }

private:
    using CodeMap = std::map<unsigned char, std::vector<bool>>;

    // Рекурсивно генерирует коды Хаффмана
    void generate_codes(Node* root, std::vector<bool>& code, CodeMap& map) {
        if (!root) return;

        if (root->is_leaf()) {
            map[root->ch] = code;
        }

        code.push_back(false);
        generate_codes(root->left, code, map);
        code.pop_back();

        code.push_back(true);
        generate_codes(root->right, code, map);
        code.pop_back();
    }

    // Рекурсивная запись дерева
    void write_tree(Node* node, BitWrite& bw) {
        if (node->is_leaf()) {
            bw.write_bit(true);
            bw.write_byte(node->ch);
        }
        else {
            bw.write_bit(false);
            write_tree(node->left, bw);
            write_tree(node->right, bw);
        }
    }

    // Рекурсивное чтение дерева
    Node* read_tree(BitRead& br) {
        bool is_leaf = br.read_bit();
        if (is_leaf) {
            unsigned char ch = br.read_byte();
            return new Node(ch, 0);
        }
        else {
            Node* left = read_tree(br);
            Node* right = read_tree(br);
            return new Node(0, left, right);
        }
    }
};

#endif