// Основной файл проекта, здесь main()

#include <iostream>
#include <queue>
#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

void output(Vector<int>& vector);

int main() {
    setlocale(0, "");
    Vector<int> vector;

    vector.push(10);
    vector.push(15);
    std::cout << vector.pop();
    std::cout << vector.pop();
	return 0;
}

void output(Vector<int>& vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << i << ": " << vector.get(i) << std::endl;
    }
    std::cout << std::endl;
}