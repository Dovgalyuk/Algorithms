set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CustomLibrary "CustomLibrary.h" "CustomLibrary.cpp" "Array.h" "Concepts.h" "Iterator.h")

add_subdirectory("Test")