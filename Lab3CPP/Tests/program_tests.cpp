
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

void write_inp(const std::string& text) {
    std::ofstream input("input.txt");
    input << text;
}

std::string read_out() {
    std::ifstream output("output.txt");
    std::string result;
    std::string line;

    while (std::getline(output, line)) {
        result += line + "\n";
    }

    return result;
}

bool run_program(const std::string& program) {
    std::string command = "\"" + program + "\"";
    return std::system(command.c_str()) == 0;
}

void check(const std::string& name,
           const std::string& actual,
           const std::string& expected,
           int& passed,
           int& failed) {
    if (actual == expected) {
        std::cout << "[PASSED] " << name << '\n';
        passed++;
    } else {
        std::cout << "[FAILED] " << name << '\n';
        std::cout << "Actual:\n" << actual;
        std::cout << "Expected:\n" << expected;
        failed++;
    }
}

void run_test(const std::string& program,
              const std::string& name,
              const std::string& input,
              const std::string& expected,
              int& passed,
              int& failed) {
    write_inp(input);

    std::remove("output.txt");

    if (!run_program(program)) {
        std::cout << "Failed " << name
                  << ": program error\n";
        failed++;
        return;
    }

    std::string actual = read_out();
    check(name, actual, expected, passed, failed);
}

bool test_task(const std::string& program) {
    int passed = 0;
    int failed = 0;

    {
        std::string input =
            "    9\n"
            "  3 4 5\n"
            "1 2 9 6 7\n"
            "  9 9 9\n"
            "    9\n";

        std::string expected =
            "    9\n"
            "  # # #\n"
            "# # 9 # #\n"
            "  9 9 9\n"
            "    9\n";

        run_test(program, "Test 1: have path",
                 input, expected, passed, failed);
    }

    {
        std::string input =
            "    9\n"
            "  9 9 9\n"
            "1 2 9 8 7\n"
            "  9 9 9\n"
            "    9\n";

        std::string expected = "";

        run_test(program, "Test 2: have no path",
                 input, expected, passed, failed);
    }

    {
        std::string input =
            "        50\n"
            "      50 50 50\n"
            "    5 6 7 50 50\n"
            "  3 4 50 8 9 50 50\n"
            "1 2 50 50 50 10 11 12 13\n"
            "  50 50 50 50 50 50 50\n"
            "    50 50 50 50 50\n"
            "      50 50 50\n"
            "        50\n";

        std::string expected =
            "        50\n"
            "      50 50 50\n"
            "    # # # 50 50\n"
            "  # # 50 # # 50 50\n"
            "# # 50 50 50 # # # #\n"
            "  50 50 50 50 50 50 50\n"
            "    50 50 50 50 50\n"
            "      50 50 50\n"
            "        50\n";

        run_test(program, "Test 3: have path",
                 input, expected, passed, failed);
    }

    {
        std::string input =
            "        50\n"
            "      50 50 50\n"
            "    5 6 7 50 50\n"
            "  3 4 50 50 9 50 50\n"
            "1 2 50 50 50 10 11 12 13\n"
            "  50 50 50 50 50 50 50\n"
            "    50 50 50 50 50\n"
            "      50 50 50\n"
            "        50\n";

        std::string expected = "";

        run_test(program, "Test 4: have no path",
                 input, expected, passed, failed);
    }

    {
        std::string input =
            "      3\n"
            "    8 2 5\n"
            "  6 7 1 4 1\n"
            "3 2 5 2 3 2 3\n"
            "  1 2 3 4 1\n"
            "    3 4 5\n"
            "      5\n";

        std::string expected =
            "      3\n"
            "    8 2 5\n"
            "  6 7 1 4 1\n"
            "# # 5 # # # #\n"
            "  # # # 4 1\n"
            "    3 4 5\n"
            "      5\n";

        run_test(program, "Test 5: example",
                 input, expected, passed, failed);
    }

    std::cout << "Tests passed: " << passed << '\n';
    std::cout << "Tests failed: " << failed << '\n';

    return failed == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Missing required arguments\n";
        return 1;
    }

    if (!test_task(argv[1])) {
        return 1;
    }

    return 0;
}
