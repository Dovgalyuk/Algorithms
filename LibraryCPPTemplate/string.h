#ifndef STACK_H
#define STACK_H

class String {

public:
    const int NULL_POS = -1;

    String(char* chars, int length): string(copyChars(chars, length)), capacity(length), length(length) {}
    String(String& src): string(copyChars(src.string, src.length)), capacity(src.length), length(src.length) {}


    void append(char ch) {
        int id = length;
        resize(id + 1);
        string[id] = ch;
    }

    void append(String const &secondString) {
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

    int findString(String const &str, size_t pos = 0) {
        int* prefix = new int[str.length];
        prefix[0] = 0;
        for (int k = 0, i = 1; i < str.length; ++i) {
            while ((k > 0) && (str.string[i] != str.string[k])) {
                k = prefix[k - 1];
            }
            if (str.string[i] == str.string[k]) {
                k++;
            }
            prefix[i] = k;
        }

        for (int k = 0, i = pos; i < length; ++i) {
            while ((k > 0) && (string[i] != str.string[k])) {
                k = prefix[k - 1];
            }
            if (++k == str.length) {
                delete[] prefix;
                return (i - str.length + 1);
            }
        }
        delete[] prefix;
        return NULL_POS;
    }

    int compare(String const &secondString) {
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

    bool equal(String const &secondString) {
        return length == secondString.length && compare(secondString) == 0;
    }

    char* getCharArray() {
        return copyChars(string, length);
    }

private:

    void expand(size_t newSize) {
        while (capacity < newSize)
            capacity *= multiplyCapacity;
    }

    char* copyChars(char* chars, size_t length) {
        length++;
        char* result = new char[length];
        for (int i = 0; i < length; ++i) {
            result[i] = chars[i];
        }
        return result;
    }

protected:
    char* string = nullptr;
    size_t capacity = 0;
    size_t length = 0;

    int multiplyCapacity = 2;
};

#endif