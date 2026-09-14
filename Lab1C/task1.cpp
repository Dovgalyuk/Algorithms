#include <iostream>
#include <fstream>
#include "array.h" // Подключаем контейнер из LibraryC

void process_task1(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << "\n";
        return;
    }

    size_t n;
    if (!(in >> n)) return;

    Array<int> arr(n);
    size_t even_count = 0;

    for (size_t i = 0; i < n; ++i) {
        in >> arr[i];
        if (arr[i] % 2 == 0) even_count++;
    }

    Array<int> even_indices(even_count);
    for (size_t i = 0, j = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) even_indices[j++] = static_cast<int>(i);
    }

    for (size_t i = 0; i < even_indices.size(); ++i) {
        std::cout << even_indices[i] << (i + 1 == even_indices.size() ? "" : " ");
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    process_task1(argv[1]);
    return 0;
}