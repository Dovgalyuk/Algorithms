add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

string(CONCAT EXPECTED_1
    "   / \\\\ / \\\\ \r?\n"
    "  \\| S \\| x \\| \r?\n"
    " / \\\\ / \\\\ / \\\\ \r?\n"
    "\\| # \\| # \\| x \\| \r?\n"
    " \\\\ / \\\\ / \\\\ / \r?\n"
    "  \\| \\. \\| E \\| \r?\n"
    "   \\\\ / \\\\ / "
)
add_test(NAME Lab3_Test_Canonical COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST Lab3_Test_Canonical PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_1}")

string(CONCAT EXPECTED_2
    "   / \\\\ / \\\\ \r?\n"
    "  \\| x \\| S \\| \r?\n"
    " / \\\\ / \\\\ / \\\\ \r?\n"
    "\\| x \\| # \\| # \\| \r?\n"
    " \\\\ / \\\\ / \\\\ / \r?\n"
    "  \\| E \\| \\. \\| \r?\n"
    "   \\\\ / \\\\ / "
)
add_test(NAME Lab3_Test_Left_Path COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST Lab3_Test_Left_Path PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_2}")

string(CONCAT EXPECTED_3
    "       / \\\\ / \\\\ / \\\\ / \\\\ \r?\n"
    "      \\| S \\| x \\| \\. \\| \\. \\| \r?\n"
    "     / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ \r?\n"
    "    \\| \\. \\| # \\| x \\| # \\| \\. \\| \r?\n"
    "   / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ \r?\n"
    "  \\| \\. \\| \\. \\| # \\| x \\| \\. \\| \\. \\| \r?\n"
    " / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ \r?\n"
    "\\| \\. \\| # \\| # \\| x \\| # \\| \\. \\| \\. \\| \r?\n"
    " \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \r?\n"
    "  \\| \\. \\| # \\| \\. \\| x \\| \\. \\| # \\| \\. \\| \r?\n"
    "   \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \r?\n"
    "    \\| \\. \\| \\. \\| # \\| x \\| # \\| \\. \\| \r?\n"
    "     \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \\\\ / \r?\n"
    "      \\| \\. \\| \\. \\| \\. \\| E \\| \r?\n"
    "       \\\\ / \\\\ / \\\\ / \\\\ / "
)
add_test(NAME Lab3_Test_Large_Fork COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST Lab3_Test_Large_Fork PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_3}")

string(CONCAT EXPECTED_4
    "   / \\\\ / \\\\ \r?\n"
    "  \\| S \\| \\. \\| \r?\n"
    " / \\\\ / \\\\ / \\\\ \r?\n"
    "\\| # \\| # \\| # \\| \r?\n"
    " \\\\ / \\\\ / \\\\ / \r?\n"
    "  \\| \\. \\| E \\| \r?\n"
    "   \\\\ / \\\\ / "
)
add_test(NAME Lab3_Test_No_Path COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input4.txt)
set_property(TEST Lab3_Test_No_Path PROPERTY PASS_REGULAR_EXPRESSION "${EXPECTED_4}")