#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "stack.h"
#include "vector.h"

using namespace std;

bool parse_ll(const string& s, long long& out) {
    try {
        size_t pos = 0;
        long long value = stoll(s, &pos);
        if (pos != s.size())
            return false;
        out = value;
        return true;
    } catch (...) {
        return false;
    }
}

long long apply_op(long long a, long long b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return b ? a / b : 0;
        case '%':
            return b ? a % b : 0;
        default:
            return 0;
    }
}

string read_script(istream& in) {
    ostringstream buf;
    buf << in.rdbuf();
    string s = buf.str();
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r'))
        s.pop_back();
    return s;
}

class Interpreter {
   public:
    Interpreter(string script, istream& input) : script_(std::move(script)), input_(input) {}

    void run() {
        const size_t max_steps = 100000;
        for (size_t steps = 0; ip_ < script_.size() && steps < max_steps; ++steps) {
            switch (script_[ip_++]) {
                case '+':
                    stack_.push(read_arg());
                    break;
                case '>':
                    cout << read_arg() << "\n";
                    break;
                case '&':
                    cmd_math();
                    break;
                case '!':
                    cmd_jump();
                    break;
                case '$':
                    cmd_random();
                    break;
                case '?':
                    cmd_if();
                    break;
                case '-':
                    if (!stack_.empty())
                        stack_.pop();
                    break;
                case '<':
                    reverse_stack();
                    break;
                case ':':
                    cmd_join();
                    break;
                case '~':
                    if (!stack_.empty())
                        holder_ = stack_.get();
                    break;
                case '=':
                    cmd_save_var();
                    break;
                case '_':
                    cmd_input();
                    break;
                case '#':
                    ip_ = script_.size();
                    break;
            }
        }
    }

    void print_stack() {
        reverse_stack();
        while (!stack_.empty())
            cout << pop_stack() << "\n";
    }

   private:
    string pop_stack() {
        string value = stack_.get();
        stack_.pop();
        return value;
    }

    void reverse_stack() {
        Stack reversed;
        while (!stack_.empty())
            reversed.push(pop_stack());
        stack_ = reversed;
    }

    string read_arg() {
        if (ip_ >= script_.size())
            return "";
        char prefix = script_[ip_++];

        if (prefix == '{') {
            size_t end = script_.find('}', ip_);
            string arg = script_.substr(ip_, end == string::npos ? string::npos : end - ip_);
            ip_ = (end == string::npos) ? script_.size() : end + 1;
            return arg;
        }
        if (prefix == '@') {
            size_t start = ip_;
            while (ip_ < script_.size() && isdigit(static_cast<unsigned char>(script_[ip_])))
                ++ip_;
            long long idx = 0;
            if (parse_ll(script_.substr(start, ip_ - start), idx) && idx >= 1 && static_cast<size_t>(idx) <= vars_.size()) {
                return vars_.get(static_cast<size_t>(idx) - 1);
            }
            return "";
        }
        if (prefix == '~')
            return holder_;
        return string(1, prefix);
    }

    void cmd_math() {
        string op = read_arg();
        long long a = 0, b = 0;
        if (stack_.empty())
            return;
        bool ok_b = parse_ll(pop_stack(), b);
        if (stack_.empty())
            return;
        bool ok_a = parse_ll(pop_stack(), a);

        long long res = (ok_a && ok_b && !op.empty()) ? apply_op(a, b, op[0]) : 0;
        stack_.push(to_string(res));
    }

    void cmd_jump() {
        long long target = 0;
        if (parse_ll(read_arg(), target) && target >= 0 && static_cast<size_t>(target) < script_.size()) {
            ip_ = static_cast<size_t>(target);
        }
    }

    void cmd_random() {
        long long max_val = 1;
        parse_ll(read_arg(), max_val);
        stack_.push(to_string(max_val > 0 ? 1 + rand() % max_val : 0));
    }

    void cmd_if() {
        if (holder_ == read_arg())
            return;
        while (ip_ < script_.size()) {
            char c = script_[ip_++];
            if (c == '|')
                return;
            if (string("+>&!$?").find(c) != string::npos)
                read_arg();
        }
    }

    void cmd_join() {
        string joined;
        while (!stack_.empty())
            joined += pop_stack();
        stack_.push(joined);
    }

    void cmd_save_var() {
        size_t idx = vars_.size();
        vars_.resize(idx + 1);
        vars_.set(idx, holder_);
    }

    void cmd_input() {
        string line;
        if (getline(input_, line) && !line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        stack_.push(line);
    }

    string script_;
    istream& input_;
    size_t ip_ = 0;
    Stack stack_;
    Vector vars_;
    string holder_;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <script_file> <input_file>\n";
        return 1;
    }

    ifstream script_stream(argv[1]);
    if (!script_stream) {
        cerr << "Unable to open script file: " << argv[1] << "\n";
        return 1;
    }

    ifstream input_stream(argv[2]);
    if (!input_stream) {
        cerr << "Unable to open input file: " << argv[2] << "\n";
        return 1;
    }

    Interpreter interpreter(read_script(script_stream), input_stream);
    interpreter.run();
    interpreter.print_stack();

    return 0;
}