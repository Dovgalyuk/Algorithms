add_executable(Grades countGrades.cpp)
add_executable(Elements twiceElements.cpp)

target_include_directories(Grades PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Grades LibraryCPPTemplate)

target_include_directories(Elements PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Elements LibraryCPPTemplate)

add_test(NAME TestGrades COMMAND Grades ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestGrades PROPERTY PASS_REGULAR_EXPRESSION "Количество 2: 4.*Количество 3: 2.*Количество 4: 2.*Количество 5: 2")

add_test(NAME TestElements COMMAND Elements ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)

set_property(TEST TestElements PROPERTY PASS_REGULAR_EXPRESSION "Элементы, встречающиеся ровно дважды: 3 4 5")

add_test(NAME TestElementsNone COMMAND Elements ${CMAKE_CURRENT_SOURCE_DIR}/twice_none_input.txt)

set_property(TEST TestElementsNone PROPERTY PASS_REGULAR_EXPRESSION "Элементы, встречающиеся ровно дважды: нет")
