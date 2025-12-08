add_executable(Lab4CPP main.cpp)
target_include_directories(Lab4CPP PUBLIC ../LibraryCPPTemplate)

add_test(NAME floyd_example
         COMMAND Lab4CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
