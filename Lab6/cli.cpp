#include "matrix_chain.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

int runProgram(int argc, char* argv[], bool dynamic)
{
    try
    {
        if (argc > 2)
            throw invalid_argument(u8"Использование: программа [входной_файл]");

        ifstream file;
        istream* input = &cin;
        if (argc == 2)
        {
            file.open(argv[1]);
            if (!file)
                throw runtime_error(u8"Не удалось открыть входной файл.");
            input = &file;
        }

        Dimensions dimensions = readDimensions(*input);
        Result result = dynamic ? solveDynamic(dimensions) : solveBruteForce(dimensions);
        cout << result.cost << '\n' << parenthesize(dimensions, result) << '\n';
        if (!cout)
            throw runtime_error(u8"Ошибка записи результата.");
        return 0;
    }
    catch (const exception& error)
    {
        cerr << u8"Ошибка: " << error.what() << '\n';
        return 1;
    }
}
