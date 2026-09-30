#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    {
        List l;
        if (l.first() != nullptr) {
            cout << "list_empty error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);

        List::Item* p = l.first();
        if (!p || p->data() != 30) {
            cout << "list_insert error\n";
            return 1;
        }
        p = p->next();
        if (!p || p->data() != 20) {
            cout << "list_insert error\n";
            return 1;
        }
        p = p->next();
        if (!p || p->data() != 10) {
            cout << "list_insert error\n";
            return 1;
        }
        if (p->next() != nullptr) {
            cout << "list_insert error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);

        List::Item* next = l.erase_first();
        if (!next || next->data() != 20) {
            cout << "list_erase_first error\n";
            return 1;
        }
        if (l.first()->data() != 20) {
            cout << "list_erase_first error\n";
            return 1;
        }
        l.erase_first();
        l.erase_first();
        if (l.first() != nullptr) {
            cout << "list_erase_first error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);

        List copy = l;
        List::Item* p1 = l.first();
        List::Item* p2 = copy.first();
        while (p1 && p2) {
            if (p1->data() != p2->data()) {
                cout << "list_copy error\n";
                return 1;
            }
            p1 = p1->next();
            p2 = p2->next();
        }
        if (p1 != nullptr || p2 != nullptr) {
            cout << "list_copy error\n";
            return 1;
        }
        copy.erase_first();
        if (l.first()->data() != 30) {
            cout << "list_copy error\n";
            return 1;
        }
    }
    {
        List a;
        a.insert(1);
        a.insert(2);
        a.insert(3);

        List b;
        b.insert(99);
        b = a;
        List::Item* p1 = a.first();
        List::Item* p2 = b.first();
        while (p1 && p2) {
            if (p1->data() != p2->data()) {
                cout << "list_assignment error\n";
                return 1;
            }
            p1 = p1->next();
            p2 = p2->next();
        }
        if (p1 != nullptr || p2 != nullptr) {
            cout << "list_assignment error\n";
            return 1;
        }
        List& ref = a;
        a = ref;
        if (a.first()->data() != 3) {
            cout << "list_assignment error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);
        l.swap_first_two();

        List::Item* p = l.first();
        if (p->data() != 20) { cout << "list_swap_first_two error\n"; return 1; }
        p = p->next();
        if (p->data() != 30) { cout << "list_swap_first_two error\n"; return 1; }
        p = p->next();
        if (p->data() != 10) { cout << "list_swap_first_two error\n"; return 1; }
        if (p->next() != nullptr) { cout << "list_swap_first_two error\n"; return 1; }
    }
    {
        List l;
        l.swap_first_two();
        if (l.first() != nullptr) {
            cout << "list_swap_first_two_edge error\n";
            return 1;
        }

        List one;
        one.insert(42);
        one.swap_first_two();
        if (one.first()->data() != 42 || one.first()->next() != nullptr) {
            cout << "list_swap_first_two_edge error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);
        l.insert(40);
        l.reverse();

        List::Item* p = l.first();
        int expected[] = { 10, 20, 30, 40 };
        for (int i = 0; i < 4; ++i) {
            if (!p || p->data() != expected[i]) {
                cout << "list_reverse_even error\n";
                return 1;
            }
            p = p->next();
        }
        if (p != nullptr) {
            cout << "list_reverse_even error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.reverse();

        List::Item* p = l.first();
        int expected[] = { 1, 2, 3 };
        for (int i = 0; i < 3; ++i) {
            if (!p || p->data() != expected[i]) {
                cout << "list_reverse_odd error\n";
                return 1;
            }
            p = p->next();
        }
        if (p != nullptr) {
            cout << "list_reverse_odd error\n";
            return 1;
        }
    }
    {
        List empty;
        empty.reverse();
        if (empty.first() != nullptr) {
            cout << "list_reverse_edge error\n";
            return 1;
        }

        List one;
        one.insert(7);
        one.reverse();
        if (one.first()->data() != 7 || one.first()->next() != nullptr) {
            cout << "list_reverse_edge error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);
        l.reverse();
        l.reverse();

        List::Item* p = l.first();
        int expected[] = { 30, 20, 10 };
        for (int i = 0; i < 3; ++i) {
            if (!p || p->data() != expected[i]) {
                cout << "list_reverse_twice error\n";
                return 1;
            }
            p = p->next();
        }
        if (p != nullptr) {
            cout << "list_reverse_twice error\n";
            return 1;
        }
    }
    {
        List l;
        l.insert(10);
        l.insert(20);
        l.insert(30);
        l.insert(40);
        l.swap_first_two();
        l.reverse();

        List::Item* p = l.first();
        int expected[] = { 10, 20, 40, 30 };
        for (int i = 0; i < 4; ++i) {
            if (!p || p->data() != expected[i]) {
                cout << "list_swap_reverse error\n";
                return 1;
            }
            p = p->next();
        }
        if (p != nullptr) {
            cout << "list_swap_reverse error\n";
            return 1;
        }
    }
    cout << "All List tests passed\n";
    return 0;
}
