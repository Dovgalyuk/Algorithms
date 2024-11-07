add_executable(Lab3CPPTemplate lab3.cpp)
target_include_directories(Lab3CPPTemplate PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab3CPPTemplate LibraryCPPTemplate)

add_test(NAME TestLab3CPP COMMAND Lab3CPPTemplate ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)