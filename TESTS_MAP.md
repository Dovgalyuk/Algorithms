# 🗺️ Карта всех тестов в проекте

## 📍 Полные пути к тестам

### 🔧 Исходники тестов (C++ файлы)

**Путь:** `/home/magnito/Algorithms/LibraryC/Tests/`

1. ✅ **stack.cpp** - Тест на стек *(нужен по заданию)*
   ```cpp
   /home/magnito/Algorithms/LibraryC/Tests/stack.cpp
   ```

2. ✅ **list.cpp** - Тест на двусвязный список *(нужен по заданию)*
   ```cpp
   /home/magnito/Algorithms/LibraryC/Tests/list.cpp
   ```

3. ❌ **array.cpp** - Тест на массив *(не нужен по заданию)*
   ```cpp
   /home/magnito/Algorithms/LibraryC/Tests/array.cpp
   ```

4. ❌ **queue.cpp** - Тест на очередь *(не нужен по заданию)*
   ```cpp
   /home/magnito/Algorithms/LibraryC/Tests/queue.cpp
   ```

5. ❌ **vector.cpp** - Тест на вектор *(не нужен по заданию)*
   ```cpp
   /home/magnito/Algorithms/LibraryC/Tests/vector.cpp
   ```

---

### 📝 Тестовые данные для Lab1C *(все нужны по заданию)*

**Путь:** `/home/magnito/Algorithms/Lab1C/`

1. ✅ **input.txt** - Основной тест
   ```
   /home/magnito/Algorithms/Lab1C/input.txt
   ```

2. ✅ **test_arithmetic.txt** - Арифметические операции
   ```
   /home/magnito/Algorithms/Lab1C/test_arithmetic.txt
   ```

3. ✅ **test_bitwise.txt** - Побитовые операции
   ```
   /home/magnito/Algorithms/Lab1C/test_bitwise.txt
   ```

4. ✅ **test_errors.txt** - Обработка ошибок
   ```
   /home/magnito/Algorithms/Lab1C/test_errors.txt
   ```

5. ✅ **test_functions.txt** - Вызовы функций
   ```
   /home/magnito/Algorithms/Lab1C/test_functions.txt
   ```

6. ✅ **test_swap.txt** - Операция swap
   ```
   /home/magnito/Algorithms/Lab1C/test_swap.txt
   ```

7. ✅ **test_variables.txt** - Работа с переменными
   ```
   /home/magnito/Algorithms/Lab1C/test_variables.txt
   ```

---

### 🚀 Исполняемые файлы тестов

**Путь:** `/home/magnito/Algorithms/build/`

#### Тесты структур данных:

1. ✅ **TestStackC** *(нужен по заданию)*
   ```
   /home/magnito/Algorithms/build/LibraryC/Tests/TestStackC
   ```

2. ✅ **TestListC** *(нужен по заданию)*
   ```
   /home/magnito/Algorithms/build/LibraryC/Tests/TestListC
   ```

3. ❌ **TestArrayC** *(не нужен по заданию)*
   ```
   /home/magnito/Algorithms/build/LibraryC/Tests/TestArrayC
   ```

#### Ваша программа:

4. ✅ **Lab1C** (Java-машина) *(нужна по заданию - использование стека)*
   ```
   /home/magnito/Algorithms/build/Lab1C/Lab1C
   ```

---

## 🧪 Как запустить тесты

### Все тесты разом:
```bash
cd /home/magnito/Algorithms/build
ctest
```

### Только тесты Lab1C:
```bash
cd /home/magnito/Algorithms/build
ctest -R Lab1C
```

### Только тесты на стек и список:
```bash
cd /home/magnito/Algorithms/build
ctest -R "TestStackC|TestListC"
```

### Запуск отдельных тестов вручную:
```bash
# Тест стека
./build/LibraryC/Tests/TestStackC

# Тест списка
./build/LibraryC/Tests/TestListC

# Ваша программа
./build/Lab1C/Lab1C Lab1C/test_arithmetic.txt
```

---

## 📋 Конфигурация в CMakeLists.txt

### LibraryC/Tests/CMakeLists.txt
```cmake
add_executable(TestArrayC array.cpp)
add_test(TestArrayC TestArrayC)

add_executable(TestListC list.cpp)
add_test(TestListC TestListC)

add_executable(TestStackC stack.cpp)
add_test(TestStackC TestStackC)
```

### Lab1C/CMakeLists.txt
```cmake
add_executable(Lab1C lab1.c)
# ... 7 тестов определены через add_test()
```

---

## ✅ Статус тестов

**Всего тестов:** 9  
**Пройдено:** 9  
**Провалено:** 0

### 🎯 Все тесты нужны по заданию (9 тестов):

```
✅ TestListC        ← Тест на двусвязный список (НУЖЕН)
✅ TestStackC      ← Тест на стек (НУЖЕН)
✅ TestLab1C_Basic ← Основной тест Java-машины (НУЖЕН)
✅ TestLab1C_Arithmetic ← Арифметика (НУЖЕН)
✅ TestLab1C_Variables  ← Переменные (НУЖЕН)
✅ TestLab1C_Bitwise     ← Побитовые операции (НУЖЕН)
✅ TestLab1C_Swap        ← Swap (НУЖЕН)
✅ TestLab1C_Functions    ← Функции (НУЖЕН)
✅ TestLab1C_Errors       ← Обработка ошибок (НУЖЕН)
```

**Итого: все 9 тестов нужны по заданию ✅**

