#include <iostream>
#include <fstream>
#include <string>

int FAILED_TESTS = 0;

void write_inp(std::string &text) {
    std::ofstream input("input.txt");
    input << text;
    input.close();
}

std::string read_out() {
    std::ifstream output("output.txt");

    std::string result;
    std::string line;

    while (std::getline(output, line)) {
        result += line;
        result += "\n";
    }

    return result;
}

void clear_out() {
    std::ofstream output("output.txt", std::ios::trunc);
}

bool run_program(std::string &program) {
    std::string command = "\"" + program + "\" > output.txt";
    return std::system(command.c_str()) == 0;
}

void check(std::string &name, std::string &actual, std::string &expected) {
    if (actual == expected) {
        std::cout << "[PASSED] : " << name  << "\n";
    } else {
        std::cout << "[FAILED] : " << name << "\n";
        std::cout << actual << " != " << expected << "\n";
        FAILED_TESTS++;
    }
}

void test_knight(std::string &program) {
    {
        clear_out();

        std::string test =
            "K.######\n"
            "..#E....\n"
            "..#.....\n"
            "..#.###.\n"
            "..#.....\n"
            ".....###\n"
            ".#####..\n"
            "##......\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "0.######\n"
                "..#2....\n"
                ".1#.....\n"
                "..#.###.\n"
                "..#.....\n"
                ".....###\n"
                ".#####..\n"
                "##......\n";

            std::string actual = read_out();
            std::string name = "Knight: basic test";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "K.......\n"
            "........\n"
            ".E......\n"
            "........\n"
            "........\n"
            "........\n"
            "........\n"
            "........\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "0.......\n"
                "........\n"
                ".1......\n"
                "........\n"
                "........\n"
                "........\n"
                "........\n"
                "........\n";

            std::string actual = read_out();
            std::string name = "Knight: one move";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "K#######\n"
            "##.#####\n"
            "########\n"
            "###.####\n"
            "########\n"
            "####E###\n"
            "########\n"
            "########\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "0#######\n"
                "##1#####\n"
                "########\n"
                "###2####\n"
                "########\n"
                "####3###\n"
                "########\n"
                "########\n";

            std::string actual = read_out();
            std::string name = "Knight: obstacles";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "........\n"
            "........\n"
            "........\n"
            "........\n"
            "........\n"
            "......E.\n"
            "........\n"
            ".......K\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "........\n"
                "........\n"
                "........\n"
                "........\n"
                "........\n"
                "......1.\n"
                "........\n"
                ".......0\n";

            std::string actual = read_out();
            std::string name = "Knight: bottom right corner";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "K#######\n"
            "########\n"
            ".E######\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "0#######\n"
                "########\n"
                ".1######\n"
                "########\n"
                "########\n"
                "########\n"
                "########\n"
                "########\n";

            std::string actual = read_out();
            std::string name = "Knight: jump over obstacles";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "KE######\n"
            "##.#####\n"
            ".#######\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "03######\n"
                "##1#####\n"
                "2#######\n"
                "########\n"
                "########\n"
                "########\n"
                "########\n"
                "########\n";

            std::string actual = read_out();
            std::string name = "Knight: adjacent exit";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "K#######\n"
            "########\n"
            "#.######\n"
            "####.###\n"
            "##.#.###\n"
            "#..##.#.\n"
            ".####.##\n"
            "E#.###.#\n";

        write_inp(test);

        if (!run_program(program)) {
            std::cout << "[FAILED] Knight: program error\n";
            FAILED_TESTS++;
        } else {
            std::string exp =
                "0#######\n"
                "########\n"
                "#1######\n"
                "####3###\n"
                "##2#8###\n"
                "#129##4#6\n"
                "10####7##\n"
                "13#11###5#\n";

            std::string actual = read_out();
            std::string name = "Knight: long path";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "K#######\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "#######E\n";

        write_inp(test);

        if (run_program(program)) {
            std::cout << "[FAILED] Knight: unreachable exit\n";
            FAILED_TESTS++;
        } else {
            std::string exp = "";
            std::string actual = read_out();
            std::string name = "Knight: unreachable exit";

            check(name, actual, exp);
        }
    }

    {
        clear_out();

        std::string test =
            "KK######\n"
            "###E####\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n"
            "########\n";

        write_inp(test);

        if (run_program(program)) {
            std::cout << "[FAILED] Knight: duplicate start\n";
            FAILED_TESTS++;
        } else {
            std::string exp = "";
            std::string actual = read_out();
            std::string name = "Knight: duplicate start";

            check(name, actual, exp);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Lab3CPP executable not specified\n";
        return 1;
    }

    std::string program = argv[1];

    test_knight(program);

    std::cout << '\n';

    if (FAILED_TESTS == 0) {
        std::cout << "All tests passed!! Time for matcha latte with a coconut milk\n";
        return 0;
    }

    std::cout << FAILED_TESTS << " test(s) failed. sh..\n";

    return 1;
}