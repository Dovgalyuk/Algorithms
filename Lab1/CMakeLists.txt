set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab1 "Lab1.cpp")

target_include_directories(Lab1 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab1 LibraryCPPTemplate)

add_subdirectory("Test")