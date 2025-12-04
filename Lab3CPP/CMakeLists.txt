add_executable(Lab3CPP main.cpp)
target_include_directories(Lab3CPP PRIVATE ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)

enable_testing()

add_test(NAME TestLab3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)
set_property(TEST TestLab3 PROPERTY PASS_REGULAR_EXPRESSION "^6\nPath: \\(\\d+,\\d+\\)( -> \\(\\d+,\\d+\\))*$")  # Гибкий: 6 + путь с любым количеством -> (минимум 1 позиция)

add_test(NAME TestLab3_1 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt)
set_property(TEST TestLab3_1 PROPERTY PASS_REGULAR_EXPRESSION "^2\nPath: \\(\\d+,\\d+\\)( -> \\(\\d+,\\d+\\))*$")  # Гибкий для пути

add_test(NAME TestLab3_2 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input2.txt)
set_property(TEST TestLab3_2 PROPERTY PASS_REGULAR_EXPRESSION "^5\nPath: \\(\\d+,\\d+\\)( -> \\(\\d+,\\d+\\))*$")  # Гибкий для длинного пути

add_test(NAME TestLab3_3 COMMAND Lab3CPP ${CMAKE_CURRENT_SOURCE_DIR}/input3.txt)
set_property(TEST TestLab3_3 PROPERTY PASS_REGULAR_EXPRESSION "^-1\n?$")  # Учёт возможной новой строки