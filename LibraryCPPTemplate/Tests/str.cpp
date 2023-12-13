#include <iostream>
#include "str.h"


int main()
{
    // Тестирование конструктора
    std::cout << "Testing constructor..." << std::endl;
    const char* testString = "Hello";
    String str(testString, 5);
    if (str.getLength() != 5) 
    {
        std::cout << "Constructor test failed: wrong length." << std::endl;
        return 1;
    }

    // Тестирование конструктора копирования
    std::cout << "Testing copy constructor..." << std::endl;
    String copyStr = str;
    if (copyStr.getLength() != str.getLength()) 
    {
        std::cout << "Copy constructor test failed: lengths do not match." << std::endl;
        return 1;
    }

    // Тестирование оператора присваивания
    std::cout << "Testing assignment operator..." << std::endl;
    String assignStr;
    assignStr = str;
    if (assignStr.getLength() != str.getLength()) 
    {
        std::cout << "Assignment operator test failed: lengths do not match." << std::endl;
        return 1;
    }

    // Тестирование метода append (char)
    std::cout << "Testing append (char)..." << std::endl;
    str.append('!');
    if (str.getLength() != 6) 
    {
        std::cout << "Append (char) test failed: wrong length after append." << std::endl;
        return 1;
    }

    // Тестирование метода append (String)
    std::cout << "Testing append (String)..." << std::endl;
    String appendStr(" World", 6);
    str.append(appendStr);
    if (str.getLength() != 12) 
    {
        std::cout << "Append (String) test failed: wrong length after append." << std::endl;
        return 1;
    }

    // Тестирование метода compare
    std::cout << "Testing compare..." << std::endl;
    String compareStr1("Hello", 5);
    String compareStr2("World", 5);
    if (compareStr1.compare(compareStr2) == 0) 
    {
        std::cout << "Compare test failed: strings are not equal." << std::endl;
        return 1;
    }

    // Тестирование метода equal
    std::cout << "Testing equal..." << std::endl;
    if (!compareStr1.equal(compareStr1)) 
    {
        std::cout << "Equal test failed: strings should be equal." << std::endl;
        return 1;
    }

    // Тестирование метода resize
    std::cout << "Testing resize..." << std::endl;
    String resizeStr("ResizeTest", 10);
    resizeStr.resize(5);
    if (resizeStr.getLength() != 5) 
    {
        std::cout << "Resize test failed: wrong length after resize. Expected 5, got " << resizeStr.getLength() << std::endl;
        return 1;
    }

    resizeStr.resize(10);
    if (resizeStr.getLength() != 10) 
    {
        std::cout << "Resize test failed: wrong length after resize. Expected 10, got " << resizeStr.getLength() << std::endl;
        return 1;
    }

    // Тестирование метода getCharArray
    std::cout << "Testing getCharArray..." << std::endl;
    char* charArray = str.getCharArray();
    for (size_t i = 0; i < str.getLength(); i++)
    {
        if (charArray[i] != str[i])
        {
            std::cout << "getCharArray test failed: Mismatch at position " << i << std::endl;
            return 1;
        }
    }
    delete[] charArray;

    // Тестирование метода findString
    std::cout << "Testing findString..." << std::endl;
    String text("Hello World", 11);
    String subtext("World", 5);
    int position = text.findString(subtext);
    if (position != 6)
    {
        std::cout << "findString test failed: Expected position 6, got " << position << std::endl;
        return 1;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
