#include <iostream>
#include <cstddef>
#include "MyString.h"

static void set_text(String& s, const char* text)
{
    std::size_t len = 0;
    while (text[len] != '\0') ++len;

    s.resize(len);

    char* buf = const_cast<char*>(s.c_str());

    for (std::size_t i = 0; i < len; ++i)
        buf[i] = text[i];

    buf[len] = '\0';
}

static bool eq_cstr(const String& s, const char* text)
{
    const char* a = s.c_str();
    std::size_t i = 0;
    for (;;)
    {
        if (a[i] != text[i]) return false;
        if (text[i] == '\0') return true;
        ++i;
    }
}

int main()
{
    {
        String s;
        if (s.size() != 0 || s.c_str()[0] != '\0')
        {
            std::cout << "Fail: default ctor\n";
            return 1;
        }
    }

    {
        String s;
        set_text(s, "Hello");
        if (s.size() != 5) { std::cout << "Fail: resize size\n"; return 1; }
        if (!eq_cstr(s, "Hello")) { std::cout << "Fail: set_text/eq\n"; return 1; }
        if (s[0] != 'H' || s[4] != 'o') { std::cout << "Fail: operator[]\n"; return 1; }
    }

    {
        String a;
        set_text(a, "ABC");

        String b(a);
        if (!eq_cstr(b, "ABC")) { std::cout << "Fail: copy ctor content\n"; return 1; }

        if (a.c_str() == b.c_str()) { std::cout << "Fail: copy ctor shallow copy\n"; return 1; }

        char* buf = const_cast<char*>(a.c_str());
        buf[0] = 'X';
        if (!eq_cstr(a, "XBC")) { std::cout << "Fail: modify original\n"; return 1; }
        if (!eq_cstr(b, "ABC")) { std::cout << "Fail: copy not independent\n"; return 1; }
    }

    {
        String a, b;
        set_text(a, "First");
        set_text(b, "Second");

        b = a;
        if (!eq_cstr(b, "First")) { std::cout << "Fail: operator=\n"; return 1; }
        if (a.c_str() == b.c_str()) { std::cout << "Fail: operator= shallow copy\n"; return 1; }

        a = a;
        if (!eq_cstr(a, "First")) { std::cout << "Fail: self assignment\n"; return 1; }
    }

    {
        String a, b;
        set_text(a, "Hello");
        set_text(b, " World");

        a += b;
        if (!eq_cstr(a, "Hello World")) { std::cout << "Fail: operator+=\n"; return 1; }
        if (a.size() != 11) { std::cout << "Fail: operator+= size\n"; return 1; }
    }

    {
        String a, b;
        set_text(a, "Hi");
        set_text(b, "!");

        String c = a + b;
        if (!eq_cstr(c, "Hi!")) { std::cout << "Fail: operator+\n"; return 1; }

        if (!eq_cstr(a, "Hi") || !eq_cstr(b, "!")) { std::cout << "Fail: operator+ modifies operands\n"; return 1; }
    }

    {
        String a, b, c;
        set_text(a, "ABC");
        set_text(b, "ABD");
        set_text(c, "ABC");

        if (!(a == c)) { std::cout << "Fail: operator==\n"; return 1; }
        if (!(a != b)) { std::cout << "Fail: operator!=\n"; return 1; }
        if (!(a < b)) { std::cout << "Fail: operator<\n"; return 1; }
        if (!(b > a)) { std::cout << "Fail: operator>\n"; return 1; }

        if (a.compare(b) >= 0) { std::cout << "Fail: compare (ABC vs ABD)\n"; return 1; }
        if (b.compare(a) <= 0) { std::cout << "Fail: compare (ABD vs ABC)\n"; return 1; }
        if (a.compare(c) != 0) { std::cout << "Fail: compare (ABC vs ABC)\n"; return 1; }
    }

    {
        String text, pat;
        set_text(text, "AXABGABAERABAB");
        set_text(pat, "ABAB");

        std::size_t p0 = text.find(pat);
        if (p0 != 10) { std::cout << "Fail: find first (expected 10)\n"; return 1; }

        std::size_t p1 = text.find(pat, 11);
        if (p1 != String::npos) { std::cout << "Fail: find with pos (expected npos)\n"; return 1; }

        String no;
        set_text(no, "ZZ");
        if (text.find(no) != String::npos) { std::cout << "Fail: find not found\n"; return 1; }
    }

    {
        String text, empty;
        set_text(text, "Hello");

        if (empty.size() != 0) { std::cout << "Fail: empty pattern not empty\n"; return 1; }

        if (text.find(empty, 0) != 0) { std::cout << "Fail: find empty pos0\n"; return 1; }
        if (text.find(empty, 3) != 3) { std::cout << "Fail: find empty pos3\n"; return 1; }
        if (text.find(empty, 10) != String::npos) { std::cout << "Fail: find empty pos>size\n"; return 1; }
    }

    {
        String s;
        set_text(s, "ABCDE");

        s.resize(3);
        if (s.size() != 3) { std::cout << "Fail: resize smaller size\n"; return 1; }
        if (!(s[0] == 'A' && s[2] == 'C')) { std::cout << "Fail: resize smaller content\n"; return 1; }
        if (s.c_str()[3] != '\0') { std::cout << "Fail: resize smaller null\n"; return 1; }

        s.resize(6);
        if (s.size() != 6) { std::cout << "Fail: resize bigger size\n"; return 1; }
        if (s[0] != 'A' || s[2] != 'C') { std::cout << "Fail: resize bigger keeps prefix\n"; return 1; }
        if (s.c_str()[6] != '\0') { std::cout << "Fail: resize bigger null\n"; return 1; }
    }

    std::cout << "All tests passed!\n";
    return 0;
}
