#include "stack.h"

int main() {
    Stack<char> s;
    if (!s.empty()) return 1;
    s.push('X');
    if (s.get() != 'X') return 1;
    s.push('Y');
    if (s.get() != 'Y') return 1;
    s.pop();
    if (s.get() != 'X') return 1;
    s.pop();
    if (!s.empty()) return 1;
    return 0;
}