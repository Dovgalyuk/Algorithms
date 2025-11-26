add_executable(Lab4CPPTemplate lab4.cpp)
target_include_directories(Lab4CPPTemplate PUBLIC ../LibraryCPPTemplate)

add_test(NAME KruskalTest COMMAND Lab4CPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)