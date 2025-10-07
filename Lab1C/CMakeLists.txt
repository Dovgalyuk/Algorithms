set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CustomLibrary INTERFACE)

target_sources(CustomLibrary PRIVATE "CustomLibrary.h" "Array.h" "Concepts.h" "Iterator.h")

add_executable(CustomLibraryApp "CustomLibrary.cpp")

target_include_directories(CustomLibraryApp PUBLIC)
target_link_libraries(CustomLibraryApp CustomLibrary)

add_subdirectory("Test")