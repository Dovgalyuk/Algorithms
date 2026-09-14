#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>

template <typename T>
class Array {
private:
    T* data;
    size_t sz;

public:
    explicit Array(size_t size) : sz(size), data(new T[size]{}) {}
    ~Array() { delete[] data; }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
    size_t size() const { return sz; }
};

void process_task2(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << "\n";
        return;
    }

    size_t n;
    if (!(in >> n)) {
        std::cerr << "Некорректный формат файла\n";
        return;
    }

    Array<int> arr(n);
    size_t even_count = 0;

    for (size_t i = 0; i < n; ++i) {
        in >> arr[i];
        if (arr[i] % 2 == 0) even_count++;
    }

    if (even_count < 2) {
        std::cout << "Недостаточно четных чисел\n";
        return;
    }

    Array<int> evens(even_count);
    for (size_t i = 0, j = 0; i < n; ++i) if (arr[i] % 2 == 0) evens[j++] = arr[i];

    std::sort(&evens[0], &evens[0] + evens.size());

    int min_diff = -1;
    for (size_t i = 1; i < evens.size(); ++i) {
        if (evens[i] != evens[i - 1]) { 
            int diff = evens[i] - evens[i - 1];
            if (min_diff == -1 || diff < min_diff) min_diff = diff;
        }
    }

    if (min_diff == -1) std::cout << "Нет различных четных чисел\n";
    else std::cout << min_diff << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу>\n";
        return 1;
    }

    process_task2(argv[1]);
    return 0;
}