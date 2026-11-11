#include "matrix_chain.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        if (argc > 2)
            throw invalid_argument(u8"Использование: Lab6Dynamic [входной_файл]");

        Dimensions dimensions;
        if (argc == 2)
        {
            ifstream file(argv[1]);
            if (!file)
                throw runtime_error(u8"Не удалось открыть входной файл.");
            dimensions = readDimensions(file);
        }
        else
        {
            dimensions = readDimensions(cin);
        }

        Result result = solveDynamic(dimensions);
        cout << result.cost << '\n' << parenthesize(dimensions, result) << '\n';
        if (!cout)
            throw runtime_error(u8"Ошибка записи результата.");
    }
    catch (const exception& error)
    {
        cerr << u8"Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
