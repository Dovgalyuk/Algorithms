#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class ListNode {
public:
    int value;
    ListNode* next;
    ListNode(int val) : value(val), next(nullptr) {}
};

class LinkedList {
public:
    ListNode* head;
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front(int val) {
        ListNode* node = new ListNode(val);
        node->next = head;
        head = node;
    }

    int pop_front() {
        if (!head) throw runtime_error("Stack underflow");
        int val = head->value;
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    bool is_empty() { return head == nullptr; }
};

class Stack {
private:
    LinkedList list;

public:
    void push(int val) { list.push_front(val); }
    int pop() { return list.pop_front(); }
    bool empty() { return list.is_empty(); }
    int top() {
        if (list.head) return list.head->value;
        throw runtime_error("Stack is empty");
    }
};

int main() {
    Stack stack;
    unordered_map<string, int> registers = {{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}};
    vector<string> instructions;
    string command;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Ошибка открытия - input.txt" << endl;
        return 1;
    }

    while (getline(inputFile, command)) {
        if (!command.empty()) {
            instructions.push_back(command);
        }
    }
    inputFile.close();

    for (const string& instr : instructions) {
        if (instr.find("push") == 0) {
            string val = instr.substr(5);
            if (isdigit(val[0]) || (val[0] == '-' && isdigit(val[1]))) {
                stack.push(stoi(val));
            } else if (registers.find(val) != registers.end()) {
                stack.push(registers[val]);
            }
        } else if (instr.find("pop") == 0) {
            string reg = instr.substr(4);
            if (stack.empty()) {
                cout << "BAD POP" << endl;
                return 0;
            }
            registers[reg] = stack.pop();
        } else if (instr == "add" || instr == "sub" || instr == "mul") {
            if (stack.empty()) { cout << "BAD OPERATION" << endl; return 0; }
            int a = stack.pop();
            if (stack.empty()) { cout << "BAD OPERATION" << endl; return 0; }
            int b = stack.pop();
            int result = (instr == "add") ? (b + a) : (instr == "sub") ? (b - a) : (b * a);
            stack.push(result);
        } else if (instr == "call") {
            stack.push(-1);  // Маркер адреса возврата
        } else if (instr == "ret") {
            if (stack.empty() || stack.top() != -1) {
                cout << "BAD RET" << endl;
                return 0;
            }
            stack.pop();
        }
    }

    for (const auto& reg : {"A", "B", "C", "D"}) {
        cout << reg << " = " << registers[reg] << endl;
    }
    
    return 0;
}
