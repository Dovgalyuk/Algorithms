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
        explicit BitWrite(std::ostream& os) : _out(os), _buffer(0), _bit_count(0) {}

        // Записывает один бит
        void write_bit(bool bit) {
            _buffer = _buffer << 1 | (bit ? 1 : 0);
            _bit_count++;
            if (_bit_count == 8) {
                _out.put(static_cast<char>(_buffer));
                _bit_count = 0;
                _buffer = 0;
            }
        }

        // Сбрасывает буфер (дописывает нули)
        void flush() {
            if (_bit_count > 0) {
                _buffer = _buffer << (8 - _bit_count);
                _out.put(static_cast<char>(_buffer));
                _bit_count = 0;
                _buffer = 0;
            }
        }

    private:
        std::ostream& _out;
        unsigned char _buffer;
        int _bit_count;
    };

    // Класс для побитового чтения
    class BitRead {
    public:
        explicit BitRead(std::istream& is) : _in(is), _buffer(0), _bit_count(0) {}

        // Читает один бит
        bool read_bit() {
            if (_bit_count == 0) {
                char c;

                if (!_in.get(c)) return false;

                _buffer = static_cast<unsigned char>(c);
                _bit_count = 8;
            }
            bool bit = (_buffer >> ((_bit_count - 1)) & 1);
            _bit_count--;
            return bit;
        }

    private:
        std::istream& _in;
        unsigned char _buffer;
        int _bit_count;
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
            pq.push(new Node(child->freq, child, nullptr));
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

        uint16_t table_size = static_cast<uint16_t>(frequencies.size());
        out.write(reinterpret_cast<const char*>(&table_size), sizeof(table_size));

        for (const auto& pair : frequencies) {
            out.put(static_cast<char>(pair.first));
            out.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }

        // 5. Запись тела
        in.clear();
        in.seekg(0);
        BitWrite bw(out);

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

        uint16_t table_size = 0;
        in.read(reinterpret_cast<char*>(&table_size), sizeof(table_size));
        if (table_size == 0) return;

        std::map<unsigned char, uint64_t> frequencies;
        for (int i = 0; i < table_size; ++i) {
            char ch;
            uint64_t freq;
            in.get(ch);
            in.read(reinterpret_cast<char*>(&freq), sizeof(freq));
            frequencies[static_cast<unsigned char>(ch)] = freq;
        }

        // 2. Восстановление дерева
        CustomPriorityQueue<Node*, NodeCompare> pq;
        for (const auto& pair : frequencies) {
            pq.push(new Node(pair.first, pair.second));
        }

        if (pq.size() == 1) {
            Node* child = pq.top(); pq.pop();
            pq.push(new Node(child->freq, child, nullptr));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            pq.push(new Node(left->freq + right->freq, left, right));
        }

        Node* root = pq.top();

        // 3. Декодирование
        BitRead br(in);
        Node* current = root;
        uint64_t decoded_count = 0;

        while (decoded_count < total_chars) {
            bool bit = br.read_bit();
            if (bit == 0) {
                current = current->left;
            }
            else if (current) {
                current = current->right;
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
};

#endif