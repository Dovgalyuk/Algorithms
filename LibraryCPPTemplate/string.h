#ifndef STACK_H
#define STACK_H

class String {

public:
    const int NULL_POS = -1;

    String(char* chars, int length): string(chars), capacity(length), length(length) {}
    String(String& src): string(src.string), capacity(src.length), length(src.length) {}

    size_t size() {
        return length;
    }

    void append(char ch) {
        int id = length;
        resize(id + 1);
        string[id] = ch;
    }

    void append(String secondString) {
        size_t startId = length;
        size_t secondLength = secondString.length;
        resize(length + secondLength);
        for (int i = 0; i < secondLength; ++i) {
            string[startId + i] = secondString.string[i];
        }
    }

    void resize(size_t newSize) {
        newSize++;
        if (capacity < newSize) {
            expand(newSize);
            char* newString = new char[capacity];
            for (int i = 0; i < capacity; ++i) {
                newString[i] = string[i];
            }
            string = newString;
        }
        length = newSize - 1;
        string[length] = '\0';
    }

    int findString(String str, size_t pos = 0) {
        for (int i = pos; i < length; ++i) {
            for (int j = 0; ; ++j) {
                if (j == str.length) return i;
                if (str.string[j] != string[i + j]) break;
            }
        }
        return NULL_POS;
    }

    int compare(String secondString) {
        char* str1 = string;
        char* str2 = secondString.string;
        while (*str1 != 0)
        {
            if (*str1 != *str2)
                return *str1 > *str2 ? 1 : -1;
            str1++;
            str2++;
        }
        return 0;
    }

    bool equal(String secondString) {
        return length == secondString.length && findString(secondString) == 0;
    }

    char* getCharArray() {
        return string;
    }

private:

    void expand(size_t newSize) {
        while (capacity < newSize)
            capacity *= multiplyCapacity;
    }

protected:
    char* string = nullptr;
    size_t capacity = 0;
    size_t length = 0;

    int multiplyCapacity = 2;
};

#endif