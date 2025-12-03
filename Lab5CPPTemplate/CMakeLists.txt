add_executable(Lab5CPPTemplate main.cpp)
target_include_directories(Lab5CPPTemplate PUBLIC ../LibraryCPPTemplate)

#       Items (N) |      MyAVL Time (ms) |   std::set Time (ms)
# -------------------------------------------------------------
#           10000 |                   11 |                    9
#           50000 |                   53 |                   45
#          100000 |                  119 |                   99
#          200000 |                  280 |                  208
#          500000 |                  723 |                  603
#         1000000 |                 1623 |                 1316
#         2000000 |                 3871 |                 3194

add_test(NAME TestLab5CPPTemplate COMMAND Lab5CPPTemplate)
set_tests_properties(TestLab5CPPTemplate PROPERTIES
    PASS_REGULAR_EXPRESSION "Items \\(N\\)(.|\\n)+10000")
