set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3 "main.cpp"
        Lab3.cpp)

target_include_directories(Lab3 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab3 LibraryCPPTemplate)

add_subdirectory("Test")