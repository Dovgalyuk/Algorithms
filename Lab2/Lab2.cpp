#include "Lab2.h"
#include "array.h"
#include "vector.h"
#include "stack.h"

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "Programm need 3 argument";
		std::exit(1);
	}

	std::ifstream scriptFile(argv[1]);
	if (!scriptFile) {
		std::cerr << "Failed to open script file";
		std::exit(1);
	}

	std::string script((std::istreambuf_iterator<char>(scriptFile)), std::istreambuf_iterator<char>());
	auto words = tokenize(script);

	std::ifstream inputFile(argv[2], std::ios::binary);
	if (!inputFile) {
		std::cerr << "Failed to open input file";
		std::exit(1);
	}

	run(words, inputFile, std::cout);

	return 0;
}

//#include <iostream>
//#include "vector.h"
//
//typedef Vector<int> MyVector;
//
//int main()
//{
//    MyVector vector;
//
//    vector.resize(5);
//    if (vector.size() != 5)
//    {
//        std::cout << "Invalid resize\n";
//        return 1;
//    }
//
//    for (size_t i = 0; i < vector.size(); ++i)
//        vector.set(i, (int)i);
//
//    vector = vector;
//
//    for (size_t i = 0; i < vector.size(); ++i)
//    {
//        if (vector.get(i) != (int)i)
//        {
//            std::cout << "Invalid vector element " << i << "\n";
//            return 1;
//        }
//    }
//
//    vector.resize(10);
//    if (vector.size() != 10)
//    {
//        std::cout << "Invalid resize\n";
//        return 1;
//    }
//
//    std::cout << "Vector: ";
//    for (size_t i = 0; i < vector.size(); ++i)
//        std::cout << vector.get(i) << " ";
//    std::cout << "\n";
//
//    vector.resize(3);
//    if (vector.size() != 3)
//    {
//        std::cout << "Invalid resize\n";
//        return 1;
//    }
//
//    for (size_t i = 0; i < vector.size(); ++i)
//    {
//        if (vector.get(i) != (int)i)
//        {
//            std::cout << "Invalid vector element " << i << "\n";
//            return 1;
//        }
//    }
//
//    std::cout << "Vector: ";
//    for (size_t i = 0; i < vector.size(); ++i)
//        std::cout << vector.get(i) << " ";
//    std::cout << "\n";
//
//    // Performance test
//    for (int i = 1; i <= 10000000; ++i)
//    {
//        vector.resize(i);
//        vector.set(i - 1, i);
//    }
//
//    MyVector copy = vector;
//
//    for (int i = 0; i < 10000000; ++i)
//    {
//        if (vector.get(i) != copy.get(i))
//        {
//            std::cout << "Invalid copy element " << i << "\n";
//            return 1;
//        }
//    }
//
//    long long sum = 0;
//    for (int i = 0; i < 10000000; ++i)
//        sum += vector.get(i);
//
//    std::cout << sum << "\n";
//}
