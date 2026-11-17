add_executable(Lab3CPP main.cpp)

target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP PRIVATE LibraryCPP)

enable_testing()

# Пример из условия
add_test(
    NAME test_example
    COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
)

set_property(
    TEST test_example
    PROPERTY PASS_REGULAR_EXPRESSION
    "0[.]######"
)
