#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#include "stack.h"

struct Token {
    std::string open;
    std::string close;
    bool symmetric;
};

static const char* kCurlyDoubleOpen = "\xE2\x80\x9C";
static const char* kCurlyDoubleClose = "\xE2\x80\x9D";
static const char* kCurlySingleOpen = "\xE2\x80\x98";
static const char* kCurlySingleClose = "\xE2\x80\x99";

static const Token TOKENS[] = {
    {"(", ")", false}, {"[", "]", false}, {"{", "}", false},
    {kCurlyDoubleOpen,  kCurlyDoubleClose, false},
    {kCurlySingleOpen,  kCurlySingleClose, false},
    {"\"", "\"", true},
    {"'",  "'",  true}
};

static inline bool matchAt(const std::string& s, size_t i, const std::string& t) {
    return s.compare(i, t.size(), t) == 0;
}

static bool validateSequence(const std::string& s)
{
    Stack<std::string> st;

    for (size_t i = 0; i < s.size(); ) {
        bool matched = false;

        for (const auto& tk : TOKENS) {
            if (matchAt(s, i, tk.open) && tk.symmetric) {
                if (!st.empty() && st.get() == tk.close) st.pop();
                else st.push(tk.close);
                i += tk.open.size();
                matched = true;
                break;
            }
            if (matchAt(s, i, tk.open) && !tk.symmetric) {
                st.push(tk.close);
                i += tk.open.size();
                matched = true;
                break;
            }
            if (!tk.symmetric && matchAt(s, i, tk.close)) {
                if (st.empty() || st.get() != tk.close) return false;
                st.pop();
                i += tk.close.size();
                matched = true;
                break;
            }
        }
        if (!matched) {
            ++i;
        }
    }
    return st.empty();
}

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: " << argv[0] << " <input-file> [output-file]\n";
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = (argc == 3) ? argv[2] : nullptr;

    std::ifstream input(input_path, std::ios::binary);
    if (!input) {
        std::cerr << "Fail open file: " << input_path << "\n";
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>());

    if (content.size() >= 3 &&
        static_cast<unsigned char>(content[0]) == 0xEF &&
        static_cast<unsigned char>(content[1]) == 0xBB &&
        static_cast<unsigned char>(content[2]) == 0xBF) {
        content.erase(0, 3);
    }

    const bool is_valid = validateSequence(content);
    const std::string result = is_valid ? "YES" : "NO";

    if (output_path != nullptr) {
        std::ofstream output(output_path);
        if (!output) {
            std::cerr << "Fail open file: " << output_path << "\n";
            return 1;
        }
        output << result << '\n';
    }

    std::cout << result << '\n';
    return 0;
}