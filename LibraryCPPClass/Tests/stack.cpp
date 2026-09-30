#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    // stack_empty
    Stack e;
    if (!e.empty()) { cout << "stack_empty error\n"; return 1; }

    // stack_push
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    if (s.empty()) { cout << "stack_push error\n"; return 1; }
    if (s.get() != 3) { cout << "stack_push error\n"; return 1; }

    // stack_pop
    s.pop();
    if (s.get() != 2) { cout << "stack_pop error\n"; return 1; }
    s.pop();
    if (s.get() != 1) { cout << "stack_pop error\n"; return 1; }
    s.pop();
    if (!s.empty()) { cout << "stack_pop error\n"; return 1; }

    // stack_get
    Stack g;
    g.push(42);
    if (g.get() != 42) { cout << "stack_get error\n"; return 1; }
    if (g.get() != 42) { cout << "stack_get error\n"; return 1; }
    if (g.empty()) { cout << "stack_get error\n"; return 1; }

    // stack_copy
    Stack a;
    a.push(1);
    a.push(2);
    a.push(3);
    Stack b = a;
    if (b.get() != 3) { cout << "stack_copy error\n"; return 1; }
    b.pop();
    if (b.get() != 2) { cout << "stack_copy error\n"; return 1; }
    if (a.get() != 3) { cout << "stack_copy error\n"; return 1; }

    // stack_assignment
    Stack c;
    c.push(99);
    c = a;
    if (c.get() != 3) { cout << "stack_assignment error\n"; return 1; }
    c.pop();
    if (c.get() != 2) { cout << "stack_assignment error\n"; return 1; }
    Stack& self = a;
    a = self;
    if (a.get() != 3) { cout << "stack_assignment error\n"; return 1; }

    // stack_swap
    Stack sw;
    sw.push(1);
    sw.push(2);
    sw.push(3);
    sw.swap();
    if (sw.get() != 2) { cout << "stack_swap error\n"; return 1; }
    sw.pop();
    if (sw.get() != 3) { cout << "stack_swap error\n"; return 1; }

    // stack_swap_edge
    Stack se;
    se.swap();
    if (!se.empty()) { cout << "stack_swap_edge error\n"; return 1; }
    Stack s1;
    s1.push(42);
    s1.swap();
    if (s1.get() != 42) { cout << "stack_swap_edge error\n"; return 1; }

    // stack_reverse
    Stack r;
    r.push(1);
    r.push(2);
    r.push(3);
    r.reverse();
    if (r.get() != 1) { cout << "stack_reverse error\n"; return 1; }
    r.pop();
    if (r.get() != 2) { cout << "stack_reverse error\n"; return 1; }
    r.pop();
    if (r.get() != 3) { cout << "stack_reverse error\n"; return 1; }

    // stack_reverse_twice
    Stack rt;
    rt.push(1);
    rt.push(2);
    rt.push(3);
    rt.reverse();
    rt.reverse();
    if (rt.get() != 3) { cout << "stack_reverse_twice error\n"; return 1; }

    // stack_reverse_edge
    Stack re;
    re.reverse();
    if (!re.empty()) { cout << "stack_reverse_edge error\n"; return 1; }
    Stack r1;
    r1.push(7);
    r1.reverse();
    if (r1.get() != 7) { cout << "stack_reverse_edge error\n"; return 1; }

    cout << "All Stack tests passed\n";
    return 0;
}
