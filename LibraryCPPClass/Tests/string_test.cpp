#include <iostream>
#include "string_custom.h"

#define ASSERT_TRUE(cond, msg) \
    if (!(cond)) { \
        std::cerr << "[FAIL] " << msg << " at line " << __LINE__ << "\n"; \
        exit(1); \
    } else { \
        std::cout << "[OK] " << msg << "\n"; \
    }

#define ASSERT_EQ_INT(val1, val2, msg) \
    if ((val1) != (val2)) { \
        std::cerr << "[FAIL] " << msg << ": expected " << (val2) << ", got " << (val1) << " at line " << __LINE__ << "\n"; \
        exit(1); \
    } else { \
        std::cout << "[OK] " << msg << "\n"; \
    }

void test_string_basics() {
    std::cout << "--- Testing String Basics ---\n";
    
    // 1. Создание
    String s1("Hello");
    ASSERT_TRUE(std::strcmp(s1.data(), "Hello") == 0, "Constructor with C-string");
    ASSERT_EQ_INT(s1.length(), 5, "Length check");

    // 2. Копирование
    String s2 = s1;
    ASSERT_TRUE(std::strcmp(s2.data(), "Hello") == 0, "Copy constructor data");
    ASSERT_TRUE(s1.data() != s2.data(), "Deep copy check (pointers must differ)");

    // 3. Присваивание
    String s3;
    s3 = s1;
    ASSERT_TRUE(std::strcmp(s3.data(), "Hello") == 0, "Assignment operator");
    
    // 4. Конкатенация
    String s4(" World");
    String s5 = s1 + s4;
    ASSERT_TRUE(std::strcmp(s5.data(), "Hello World") == 0, "Concatenation String + String");
}

void test_string_slice() {
    std::cout << "\n--- Testing StringSlice ---\n";

    String str("Heavy Metal");
    
    // 1. Создание среза из String
    StringSlice slice1(str);
    ASSERT_TRUE(std::strncmp(slice1.data(), "Heavy Metal", 11) == 0, "Slice from String");
    ASSERT_EQ_INT(slice1.length(), 11, "Slice length full");

    // 2. Создание частичного среза
    StringSlice slice2(str.data() + 6, 5);
    ASSERT_TRUE(std::strncmp(slice2.data(), "Metal", 5) == 0, "Partial Slice creation");
    ASSERT_EQ_INT(slice2.length(), 5, "Partial Slice length");

    // 3. Конкатенация String + Slice
    String prefix("I like ");
    String result = prefix + slice2; // "I like " + "Metal"
    ASSERT_TRUE(std::strcmp(result.data(), "I like Metal") == 0, "String + Slice concatenation");
    
    // 4. Конкатенация Slice + Slice
    StringSlice part1(str.data(), 5); // "Heavy"
    String full = part1 + slice2;     // "Heavy" + "Metal"
    ASSERT_TRUE(std::strcmp(full.data(), "HeavyMetal") == 0, "Slice + Slice concatenation");
}

void test_boyer_moore_search() {
    std::cout << "\n--- Testing Boyer-Moore Search ---\n";

    String text("abracadabra");

    // 1. Обычный поиск
    long idx = text.find("cad");
    ASSERT_EQ_INT(idx, 4, "Find existing substring 'cad'");

    // 2. Поиск в начале
    idx = text.find("abra");
    ASSERT_EQ_INT(idx, 0, "Find substring at start");

    // 3. Несуществующая подстрока
    idx = text.find("xyz");
    ASSERT_EQ_INT(idx, -1, "Find non-existing substring");

    // 4. Паттерн длиннее текста
    idx = text.find("abracadabrazzz");
    ASSERT_EQ_INT(idx, -1, "Find pattern longer than text");

    // 5. Тест StringSlice поиска (тот же алгоритм)
    // Текст: "bra" (взято из "abracadabra", смещение 1, длина 3)
    StringSlice slice(text.data() + 1, 3); 
    idx = slice.find("ra"); // должно найти "ra" внутри "bra" на позиции 1
    ASSERT_EQ_INT(idx, 1, "Search inside Slice");
}

void test_comparison() {
    std::cout << "\n--- Testing Comparison ---\n";
    
    String s1("Apple");
    String s2("Banana");
    String s3("Apple");

    ASSERT_TRUE(s1.compare(s2) < 0, "Compare: Apple < Banana");
    ASSERT_TRUE(s2.compare(s1) > 0, "Compare: Banana > Apple");
    ASSERT_EQ_INT(s1.compare(s3), 0, "Compare: Apple == Apple");

    StringSlice sl1("Apple");
    StringSlice sl2("Ap");
    
    // "Apple" > "Ap"
    ASSERT_TRUE(sl1.compare(sl2) > 0, "Compare Slice: Apple > Ap");
}

int main() {
    test_string_basics();
    test_string_slice();
    test_boyer_moore_search();
    test_comparison();

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
