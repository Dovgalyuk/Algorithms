set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2
    main.cpp
 )

#target_include_directories(Lab2 PUBLIC ../LibraryCPPTemplate)
#target_link_libraries(Lab2 LibraryCPPTemplate)

target_include_directories(Lab2 PUBLIC ../LibraryCPPtemplate)

add_executable(stack_test tests/stack_test.cpp)
add_executable(list_test tests/list_test.cpp)

target_include_directories(stack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPtemplate)
target_include_directories(list_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPPtemplate)

add_test(NAME StackTest COMMAND stack_test)
add_test(NAME ListTest COMMAND list_test)

add_subdirectory("tests")

