# Тесты списка
add_executable(TestListStack tests_list.cpp)

foreach(i RANGE 1 12)
    add_test(
        NAME List_Test${i}
        COMMAND TestListStack ${i}
    )
endforeach()

# Тесты стека
add_executable(TestStack tests_stack.cpp)

foreach(i RANGE 1 12)
    add_test(
        NAME Stack_Test${i}
        COMMAND TestStack ${i}
    )
endforeach()