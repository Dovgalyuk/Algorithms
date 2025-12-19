#include <iostream>
#include <cstddef>
#include <chrono>
#include <vector>
#include <iomanip>
#include "MyString.h"

struct Res {
    const char* label;
    long long time;
};

static std::vector<Res> res;

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


static void fill_with_char(String& s, std::size_t n, char ch)
{
    s.resize(n);
    char* buf = const_cast<char*>(s.c_str());
    for (std::size_t i = 0; i < n; ++i) buf[i] = ch;
    buf[n] = '\0';
}

static void write_at(String& s, std::size_t pos, const char* text)
{
    char* buf = const_cast<char*>(s.c_str());
    std::size_t i = 0;
    while (text[i] != '\0')
    {
        buf[pos + i] = text[i];
        ++i;
    }
}

static std::size_t find_naive(const String& text, const String& pat, std::size_t pos = 0)
{
    const std::size_t n = text.size();
    const std::size_t m = pat.size();

    if (m == 0) return (pos <= n) ? pos : String::npos;
    if (pos > n) return String::npos;
    if (m > n - pos) return String::npos;

    const char* a = text.c_str();
    const char* b = pat.c_str();

    for (std::size_t i = pos; i + m <= n; ++i)
    {
        std::size_t j = 0;
        while (j < m && a[i + j] == b[j]) ++j;
        if (j == m) return i;
    }
    return String::npos;
}

static long long measure_kmp_find(const String& text, const String& pat, int runs)
{
    std::size_t sink = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < runs; ++i)
        sink ^= text.find(pat);
    auto end = std::chrono::high_resolution_clock::now();

    if (sink == 123456789u) std::cout << "";

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / runs;
}

static long long measure_naive_find(const String& text, const String& pat, int runs)
{
    std::size_t sink = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < runs; ++i)
        sink ^= find_naive(text, pat);
    auto end = std::chrono::high_resolution_clock::now();

    if (sink == 123456789u) std::cout << "";

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / runs;
}

static void print_time()
{
    std::cout << "\nResults (microseconds):\n\n";
    for (auto& r : res)
    {
        std::cout << std::left << std::setw(28) << r.label << " | "
            << std::right << std::setw(12) << r.time << " us\n";
    }
}

static void perf_case(const char* label, std::size_t N, const char* pat_cstr, int runs)
{
    String text, pat;
    fill_with_char(text, N, 'A');
    set_text(pat, pat_cstr);

    std::size_t insert_pos = N - pat.size() - 10;
    write_at(text, insert_pos, pat.c_str());

    if (text.find(pat) != insert_pos)
    {
        std::cout << "Fail: perf wrong pos (KMP)\n";
        std::exit(1);
    }
    if (find_naive(text, pat) != insert_pos)
    {
        std::cout << "Fail: perf wrong pos (Naive)\n";
        std::exit(1);
    }

    long long t_kmp = measure_kmp_find(text, pat, runs);
    long long t_naive = measure_naive_find(text, pat, runs);

    res.push_back({ label, t_kmp });
    res.push_back({ "Naive (same case)", t_naive });
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
        const int RUNS = 5;

        perf_case("KMP find (N=100000)", 100'000, "AAAAAAAAAAAAAAAAAAAAAB", RUNS);
        perf_case("KMP find (N=500000)", 500'000, "AAAAAAAAAAAAAAAAAAAAAB", RUNS);
        perf_case("KMP find (N=1000000)", 1'000'000, "AAAAAAAAAAAAAAAAAAAAAB", RUNS);
        perf_case("KMP find (N=5000000)", 5'000'000, "AAAAAAAAAAAAAAAAAAAAAB", RUNS);
        perf_case("KMP find (N=10000000)", 10'000'000, "AAAAAAAAAAAAAAAAAAAAAB", RUNS);

        print_time();
    }

    std::cout << "All tests passed!\n";
    return 0;
}