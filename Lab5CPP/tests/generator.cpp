#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <output_file>\n";
        return 1;
    }

    std::ofstream out(argv[1]);
    if (!out.is_open()) return 1;

    const int N = 1000000;
    for (int i = 0; i < N; ++i) {
        out << "key" << i << " value" << i << "\n";
    }

    std::cout << "Generated " << N << " pairs into " << argv[1] << "\n";
    return 0;
}