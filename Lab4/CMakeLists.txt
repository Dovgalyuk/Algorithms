set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4 main.cpp AStar.h)

target_include_directories(Lab4 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab4 LibraryCPPTemplate)

add_subdirectory("Test")