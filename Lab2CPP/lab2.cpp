#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <fstream>

using namespace std;

class LinkedList {
public:
    struct ListNode {
        int value;
        ListNode* next;
        ListNode(int val) : value(val), next(nullptr) {}
    };

    ListNode* head;

    LinkedList() : head(nullptr) {}

    void push_front(int val) {
        ListNode* node = new ListNode(val);
        node->next = head;
        head = node;
    }

    int pop_front() {
        if (!head) throw runtime_error("Недостаточный расход стека.");
        int val = head->value;
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    bool isEmpty() const { return head == nullptr; } 

    ~LinkedList() { 
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Stack {
private:
    LinkedList list;

public:
    void push(int val) { list.push_front(val); }
    int pop() { return list.pop_front(); }
    bool empty() { return list.isEmpty(); }
    int top() {
        if (list.head) return list.head->value;
        throw runtime_error("Stack is empty");
    }
};

int main() {
    Stack stack;
    unordered_map<string, int> registers = {{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}};
    string command;
    ifstream inputFile("in.txt"); 

    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    while (getline(inputFile, command)) {
        if (command == "end") break;
        if (command.empty()) continue;

        stringstream ss(command);
        string op;
        ss >> op;

        if (op == "push") {
            string val;
            ss >> val;
            if (isdigit(val[0]) || (val[0] == '-' && isdigit(val[1]))) {
                try {
                    stack.push(stoi(val));
                } catch (const invalid_argument& e) {
                    cerr << "Invalid number format: " << val << endl;
                    return 1;
                }
            } else if (registers.find(val) != registers.end()) {
                stack.push(registers[val]);
            } else {
                cerr << "Unknown register or value: " << val << endl;
                return 1;
            }
        } else if (op == "pop") {
            string reg;
            ss >> reg;
            if (registers.find(reg) == registers.end()) {
                cerr << "Invalid register: " << reg << endl;
                return 1;
            }
            if (stack.empty()) {
                cout << "BAD POP" << endl;
                return 0;
            }
            registers[reg] = stack.pop();
        } else if (op == "add" || op == "sub" || op == "mul") {
            if (stack.empty()) { cout << "BAD OPERATION" << endl; return 0; }
            int a = stack.pop();
            if (stack.empty()) { cout << "BAD OPERATION" << endl; return 0; }
            int b = stack.pop();
            int result = (op == "add") ? (b + a) : (op == "sub") ? (b - a) : (b * a);
            stack.push(result);
        } else if (op == "call") {
            stack.push(-1);
        } else if (op == "ret") {
            if (stack.empty()) {
                cout << "BAD RET" << endl;
                return 0;
            }
            if(stack.top() != -1) {
                cout << "BAD RET" << endl;
                return 0;
            }

            stack.pop();

        } else {
            cerr << "Ошибочная инструкция: " << command << endl;
            return 1;
        }
    }

    inputFile.close(); 

    for (const auto& reg : {"A", "B", "C", "D"}) {
        cout << reg << " = " << registers[reg] << endl;
    }

    return 0;
}
