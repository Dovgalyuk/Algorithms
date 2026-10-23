#include <iostream>
#include <string>
#include <stdexcept>
#include "../list.h"
#include "../stack.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    int test = stoi(argv[1]);
    List<int> list;

    switch (test)
    {
    case 1:
        if (!list.empty() || list.size() != 0)
            return 1;
        break;

    case 2:
        list.pushFront(10);
        list.pushFront(20);
        if (list.front() != 20 || list.size() != 2)
            return 1;
        break;

    case 3:
        list.pushBack(10);
        list.pushBack(20);
        if (list.back() != 20 || list.size() != 2)
            return 1;
        break;

    case 4:
        list.pushBack(10);
        list.pushBack(20);
        if (list.front() != 10)
            return 1;
        break;

    case 5:
        list.pushBack(10);
        list.pushBack(20);
        if (list.back() != 20)
            return 1;
        break;

    case 6:
        list.pushBack(10);
        list.pushBack(20);
        list.popFront();
        if (list.front() != 20 || list.size() != 1)
            return 1;
        break;

    case 7:
        list.pushBack(10);
        list.pushBack(20);
        list.popBack();
        if (list.back() != 10 || list.size() != 1)
            return 1;
        break;

    case 8:
        list.pushBack(10);
        list.pushBack(20);
        list.pushBack(30);
        list.reverse();
        if (list.at(0) != 30 ||
            list.at(1) != 20 ||
            list.at(2) != 10)
            return 1;
        break;

    case 9:
        list.pushBack(10);
        list.pushBack(20);
        list.pushBack(30);
        if (list.at(1) != 20)
            return 1;
        break;

    case 10:
        list.pushBack(10);
        list.pushBack(20);
        list.clear();
        if (!list.empty() || list.size() != 0)
            return 1;
        break;

    case 11:
        try
        {
            list.at(0);
            return 1;
        }
        catch (const out_of_range&)
        {
        }
        break;

    case 12:
        try
        {
            list.popFront();
            return 1;
        }
        catch (const runtime_error&)
        {
        }
        break;

    default:
        return 1;
    }

    cout << "Test " << test << " passed" << endl;
    return 0;
}
