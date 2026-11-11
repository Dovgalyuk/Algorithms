
#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "task.h"

int main() {
    int passed = 0, failed = 0;

    {
        std::ofstream input("unit_input.txt");
        input << "  9\n"
                 "1 2 3\n"
                 "  9\n";
        input.close();

        std::ifstream file("unit_input.txt");
        Vector* vec = vector_create();

        int rows = reader(vec, file);

        int expected[9] = {
            EMPTY, 9, EMPTY,
            1,     2, 3,
            EMPTY, 9, EMPTY
        };

        bool is_ok = false;

        if (rows == 3 && vector_size(vec) == 9) {
            is_ok = true;
        }

        for (int i = 0; i < 9; i++) {
            if (vector_get(vec, i) != expected[i]) {
                is_ok = false;
                break;
            }
        }

        if (is_ok) {
            std::cout << "Test 1 reader passed\n";
            passed++;
        } else {
            std::cout << "Test 1 reader failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        std::ofstream input("unit_input.txt");
        input << "    9\n"
                 "  3 4 5\n"
                 "1 2 9 6 7\n"
                 "  9 9 9\n"
                 "    9\n";
        input.close();

        std::ifstream file("unit_input.txt");
        Vector* vec = vector_create();

        int rows = reader(vec, file);

        int expected[25] = {
            EMPTY, EMPTY, 9, EMPTY, EMPTY,
            EMPTY, 3,     4, 5,     EMPTY,
            1,     2,     9, 6,     7,
            EMPTY, 9,     9, 9,     EMPTY,
            EMPTY, EMPTY, 9, EMPTY, EMPTY
        };

        bool is_ok = false;

        if (rows == 5 && vector_size(vec) == 25) {
            is_ok = true;
        }

        for (int i = 0; i < 25; i++) {
            if (vector_get(vec, i) != expected[i]) {
                is_ok = false;
                break;
            }
        }

        if (is_ok) {
            std::cout << "Test 2 reader passed\n";
            passed++;
        } else {
            std::cout << "Test 2 reader failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        int values[9] = {
            EMPTY, 9, EMPTY,
            1,     2, 3,
            EMPTY, 9, EMPTY
        };

        Vector* vec = vector_create();

        for (int i = 0; i < 9; i++) {
            vector_set(vec, i, values[i]);
        }

        bool found = find_path(vec, 3);

        int expected[9] = {
            EMPTY, 9,    EMPTY,
            PATH,  PATH, PATH,
            EMPTY, 9,    EMPTY
        };

        bool is_ok = false;

        if (found && vector_size(vec) == 9) {
            is_ok = true;
        }

        for (int i = 0; i < 9; i++) {
            if (vector_get(vec, i) != expected[i]) {
                is_ok = false;
                break;
            }
        }

        if (is_ok) {
            std::cout << "Test 3 find_path passed\n";
            passed++;
        } else {
            std::cout << "Test 3 find_path failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        int values[25] = {
            EMPTY, EMPTY, 9, EMPTY, EMPTY,
            EMPTY, 3,     4, 5,     EMPTY,
            1,     2,     9, 6,     7,
            EMPTY, 9,     9, 9,     EMPTY,
            EMPTY, EMPTY, 9, EMPTY, EMPTY
        };

        Vector* vec = vector_create();

        for (int i = 0; i < 25; i++) {
            vector_set(vec, i, values[i]);
        }

        bool found = find_path(vec, 5);

        int expected[25] = {
            EMPTY, EMPTY, 9,    EMPTY, EMPTY,
            EMPTY, PATH,  PATH, PATH,  EMPTY,
            PATH,  PATH,  9,    PATH,  PATH,
            EMPTY, 9,     9,    9,     EMPTY,
            EMPTY, EMPTY, 9,    EMPTY, EMPTY
        };

        bool is_ok = false;

        if (found && vector_size(vec) == 25) {
            is_ok = true;
        }

        for (int i = 0; i < 25; i++) {
            if (vector_get(vec, i) != expected[i]) {
                is_ok = false;
                break;
            }
        }

        if (is_ok) {
            std::cout << "Test 4 find_path passed\n";
            passed++;
        } else {
            std::cout << "Test 4 find_path failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        int values[9] = {
            EMPTY, 9, EMPTY,
            1,     9, 3,
            EMPTY, 9, EMPTY
        };

        Vector* vec = vector_create();

        for (int i = 0; i < 9; i++) {
            vector_set(vec, i, values[i]);
        }

        bool found = find_path(vec, 3);

        bool is_ok = false;

        if (!found && vector_size(vec) == 9) {
            is_ok = true;
        }

        for (int i = 0; i < 9; i++) {
            if (vector_get(vec, i) != values[i]) {
                is_ok = false;
                break;
            }
        }

        if (is_ok) {
            std::cout << "Test 5 find_path passed\n";
            passed++;
        } else {
            std::cout << "Test 5 find_path failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        Vector* vec = vector_create();

        bool found = find_path(vec, 0);

        if (!found) {
            std::cout << "Test 6 find_path passed\n";
            passed++;
        } else {
            std::cout << "Test 6 find_path failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    {
        int values[9] = {
            EMPTY, 9,    EMPTY,
            PATH,  PATH, PATH,
            EMPTY, 9,    EMPTY
        };

        Vector* vec = vector_create();

        for (int i = 0; i < 9; i++) {
            vector_set(vec, i, values[i]);
        }

        std::ofstream output("unit_output.txt");
        bool is_ok = output.is_open();

        if (is_ok) {
            writer(vec, 3, output);
            output.close();
        }

        std::ifstream output_read("unit_output.txt");

        std::string expected =
            "  9\n"
            "# # #\n"
            "  9\n";

        std::string actual;
        std::string line;

        while (std::getline(output_read, line)) {
            actual += line + "\n";
        }

        if (actual != expected) {
            is_ok = false;
        }

        if (is_ok) {
            std::cout << "Test 7 writer passed\n";
            passed++;
        } else {
            std::cout << "Test 7 writer failed\n";
            failed++;
        }

        vector_delete(vec);
    }

    std::cout << "Tests passed: " << passed << '\n';
    std::cout << "Tests failed: " << failed << '\n';

    return failed != 0;
}
