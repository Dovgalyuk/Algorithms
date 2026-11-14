add_executable(Lab3 main.cpp)

target_link_libraries(Lab3 PRIVATE LibraryCPPClass)

add_test(
    NAME Lab3
    COMMAND Lab3 "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
)