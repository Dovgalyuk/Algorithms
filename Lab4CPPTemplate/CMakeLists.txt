add_executable(Lab4CPP lab4.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME TestLab4CPP COMMAND $<TARGET_FILE:Lab4CPP> ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab4CPP PROPERTY PASS_REGULAR_EXPRESSION "A B 1")



