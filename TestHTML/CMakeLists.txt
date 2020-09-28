project(TestHTML)

add_executable(TestHTML main.cpp input.txt output.txt)

target_include_directories(TestHTML PUBLIC ../LibraryCPP)

target_link_libraries(TestHTML LibraryCPP)