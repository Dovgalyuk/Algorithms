add_executable(TestArrayCPPTemplate main.cpp)
target_include_directories(TestArrayCPPTemplate PUBLIC ../LibraryCPPTemplate)

add_test(TestArrayCPPTemplate TestArrayCPPTemplate)
