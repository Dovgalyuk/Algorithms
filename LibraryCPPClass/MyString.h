#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef> 

class String
{
public:
    static constexpr size_t npos = static_cast<size_t>(-1);
	String();

    String(const String& a);

    ~String();
    
    // конкатенация
    String& operator+=(const String& other);
    String operator+(const String& other) const;

    // присваивание
    String& operator=(const String& a);

    // поиск подстроки
    std::size_t find(const String& pattern, std::size_t pos = 0) const;

    // сравнение
    int compare(const String& other) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;

    char operator[](std::size_t index) const;

    // изменение размера
    void resize(std::size_t size);

    // Получение указателя на массив символов
    const char* c_str() const;

    std::size_t size() const;
private:
    std::size_t size_;
    char* data_;
    std::size_t capacity_;
};


#endif