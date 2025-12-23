#ifndef STRING_CUSTOM_H
#define STRING_CUSTOM_H

#include <cstddef>
#include <iostream>

class StringSlice;

class String {
public:
    String();
    String(const char* rawStr);
    String(const String& other);
    ~String();

    String& operator=(const String& other);

    const char* data() const;
    
    size_t length() const;

    String operator+(const String& other) const;
    String operator+(const StringSlice& other) const;

    // Поиск подстроки (Алгоритм Бойера-Мура)
    // Возвращает индекс первого вхождения или -1, если не найдено
    long find(const char* substring) const;

    int compare(const String& other) const;

private:
    char* m_data;
    size_t m_size;
};

class StringSlice {
public:
    StringSlice(const char* rawStr);
    StringSlice(const String& str);
    StringSlice(const char* start, size_t len);
    
    StringSlice(const StringSlice& other) = default;

    const char* data() const;
    size_t length() const;

    String operator+(const StringSlice& other) const;

    long find(const char* substring) const;

    int compare(const StringSlice& other) const;

private:
    const char* m_start;
    size_t m_len;
};

#endif
