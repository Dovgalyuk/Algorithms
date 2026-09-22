#include "array.h"

#include <iostream>
#include <string>

void check(bool condition, const char *message)
{
    if (!condition)
        throw std::runtime_error(message);
}

int main()
{
    try
    {
        Array<int> source(3);
        check(source.size() == 3, "Wrong size");
        check(source.get(0) == 0 && source.get(2) == 0, "Wrong initial values");
        source.set(0, 7);
        source.set(2, -4);

        Array<int> copy(source);
        copy.set(0, 100);
        check(source.get(0) == 7 && copy.get(2) == -4, "Copy shares storage");

        Array<int> assigned(3);
        assigned = source;
        source.set(2, 10);
        check(assigned.get(0) == 7 && assigned.get(2) == -4, "Assignment shares storage");
        const Array<int> &alias = assigned;
        assigned = alias;
        check(assigned.get(0) == 7, "Self assignment failed");

        bool caught = false;
        try
        {
            Array<int> other(2);
            assigned = other;
        }
        catch (const std::length_error &)
        {
            caught = true;
        }
        check(caught && assigned.size() == 3 && assigned.get(0) == 7,
              "Different size assignment must preserve the array");

        caught = false;
        try { source.get(3); }
        catch (const std::out_of_range &) { caught = true; }
        check(caught, "Reading past the end was allowed");

        caught = false;
        try { source.set(3, 1); }
        catch (const std::out_of_range &) { caught = true; }
        check(caught, "Writing past the end was allowed");

        Array<int> empty(0);
        Array<int> empty_copy(empty);
        empty_copy = empty;
        check(empty_copy.size() == 0, "Empty array copy failed");
        caught = false;
        try { empty.get(0); }
        catch (const std::out_of_range &) { caught = true; }
        check(caught, "Empty array access was allowed");

        Array<std::string> words(1);
        words.set(0, "hello");
        Array<std::string> words_copy(words);
        words.set(0, "changed");
        check(words_copy.get(0) == "hello", "String copy failed");
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
