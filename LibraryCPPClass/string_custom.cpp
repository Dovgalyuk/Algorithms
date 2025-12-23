#include "string_custom.h"
#include <algorithm>

static size_t custom_strlen(const char* str) {
    const char* s = str;
    while (*s) {
        ++s;
    }
    return s - str;
}

static int custom_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

static int custom_strncmp(const char* s1, const char* s2, size_t n) {
    if (n == 0) return 0;
    while (n-- > 0) {
        if (*s1 != *s2) {
            return *(const unsigned char*)s1 - *(const unsigned char*)s2;
        }
        if (*s1 == '\0') return 0;
        ++s1;
        ++s2;
    }
    return 0;
}

static void custom_memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    while (n--) {
        *d++ = *s++;
    }
}

static long BoyerMooreSearch(const char* text, size_t textLen, const char* pattern) {
    size_t patLen = custom_strlen(pattern);
    if (patLen == 0) return 0;
    if (textLen < patLen) return -1;

    size_t badCharTable[256];
    
    // Заполняем таблицу длиной паттерна
    for (int i = 0; i < 256; ++i) {
        badCharTable[i] = patLen;
    }

    // Заполняем смещения для символов паттерна
    for (size_t i = 0; i < patLen - 1; ++i) {
        badCharTable[(unsigned char)pattern[i]] = patLen - 1 - i;
    }

    size_t shift = 0;
    while (shift <= (textLen - patLen)) {
        int j = static_cast<int>(patLen - 1);

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return static_cast<long>(shift);
        } else {
            shift += badCharTable[(unsigned char)text[shift + patLen - 1]];
        }
    }

    return -1;
}

String::String() : m_size(0) {
    m_data = new char[1];
    m_data[0] = '\0';
}

String::String(const char* rawStr) {
    if (rawStr) {
        m_size = custom_strlen(rawStr);
        m_data = new char[m_size + 1];
        custom_memcpy(m_data, rawStr, m_size + 1);
    } else {
        m_size = 0;
        m_data = new char[1];
        m_data[0] = '\0';
    }
}

String::String(const String& other) {
    m_size = other.m_size;
    m_data = new char[m_size + 1];
    custom_memcpy(m_data, other.m_data, m_size + 1);
}

String::~String() {
    delete[] m_data;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        custom_memcpy(m_data, other.m_data, m_size + 1);
    }
    return *this;
}

const char* String::data() const {
    return m_data;
}

size_t String::length() const {
    return m_size;
}

String String::operator+(const String& other) const {
    String newStr;
    delete[] newStr.m_data;
    
    newStr.m_size = m_size + other.m_size;
    newStr.m_data = new char[newStr.m_size + 1];
    
    custom_memcpy(newStr.m_data, m_data, m_size);
    custom_memcpy(newStr.m_data + m_size, other.m_data, other.m_size + 1);
    
    return newStr;
}

String String::operator+(const StringSlice& other) const {
    String newStr;
    delete[] newStr.m_data;
    
    size_t otherLen = other.length();
    newStr.m_size = m_size + otherLen;
    newStr.m_data = new char[newStr.m_size + 1];
    
    custom_memcpy(newStr.m_data, m_data, m_size);
    custom_memcpy(newStr.m_data + m_size, other.data(), otherLen);
    newStr.m_data[newStr.m_size] = '\0';
    
    return newStr;
}

long String::find(const char* substring) const {
    return BoyerMooreSearch(m_data, m_size, substring);
}

int String::compare(const String& other) const {
    return custom_strcmp(m_data, other.m_data);
}


StringSlice::StringSlice(const char* rawStr) {
    m_start = rawStr ? rawStr : "";
    m_len = rawStr ? custom_strlen(rawStr) : 0;
}

StringSlice::StringSlice(const String& str) {
    m_start = str.data();
    m_len = str.length();
}

StringSlice::StringSlice(const char* start, size_t len) 
    : m_start(start), m_len(len) {}

const char* StringSlice::data() const {
    return m_start;
}

size_t StringSlice::length() const {
    return m_len;
}

String StringSlice::operator+(const StringSlice& other) const {
    size_t totalLen = m_len + other.m_len;
    char* buffer = new char[totalLen + 1];
    custom_memcpy(buffer, m_start, m_len);
    custom_memcpy(buffer + m_len, other.m_start, other.m_len);
    buffer[totalLen] = '\0';
    
    String res(buffer); 
    delete[] buffer;
    return res;
}

long StringSlice::find(const char* substring) const {
    return BoyerMooreSearch(m_start, m_len, substring);
}

int StringSlice::compare(const StringSlice& other) const {
    size_t minLen = std::min(m_len, other.m_len);
    
    int res = custom_strncmp(m_start, other.m_start, minLen);
    if (res != 0) return res;
    
    if (m_len < other.m_len) return -1;
    if (m_len > other.m_len) return 1;
    return 0;
}
