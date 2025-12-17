#include <iostream>
#include <stdexcept>
#include "MyString.h"
#include "substring.h"

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

static bool eq_slice_cstr(const StringSlice& sl, const char* text)
{
    const char* p = sl.c_str();
    std::size_t i = 0;
    for (;;)
    {
        if (text[i] == '\0') return true;
        if (p[i] != text[i]) return false;
        ++i;
    }
}

int main()
{
    String src;
    set_text(src, "Hello, World!");

    {
        StringSlice sl(src, 7, 5);

        if (sl.size() != 5)
        {
            std::cout << "Fail: size()\n";
            return 1;
        }

        if (sl.data() != src.c_str() + 7)
        {
            std::cout << "Fail: data() pointer\n";
            return 1;
        }

        if (!eq_slice_cstr(sl, "World"))
        {
            std::cout << "Fail: c_str() content\n";
            return 1;
        }

        if (sl[0] != 'W' || sl[1] != 'o' || sl[4] != 'd')
        {
            std::cout << "Fail: operator[] content\n";
            return 1;
        }
    }

    {
        StringSlice sl(src, 3, 0);
        if (sl.size() != 0)
        {
            std::cout << "Fail: zero-length slice size\n";
            return 1;
        }
    }

    {
        StringSlice sl(src, 0, 5);
        bool thrown = false;
        try
        {
            (void)sl[5];
        }
        catch (const std::out_of_range&)
        {
            thrown = true;
        }

        if (!thrown)
        {
            std::cout << "Fail: operator[] must throw out_of_range\n";
            return 1;
        }
    }

    {
        bool thrown = false;
        try
        {
            StringSlice bad(src, 10, 10);
        }
        catch (const std::out_of_range&)
        {
            thrown = true;
        }

        if (!thrown)
        {
            std::cout << "Fail: ctor must throw out_of_range\n";
            return 1;
        }
    }

    std::cout << "All substring tests passed!\n";
    return 0;
}
