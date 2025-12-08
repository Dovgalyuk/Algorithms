# add_executable(TestList list.cpp)
# target_include_directories(TestList PUBLIC ../../LibraryCPPClass)
# target_link_libraries(TestList LibraryCPPClass)
# add_test(TestList TestList)

# add_executable(TestStack stack.cpp)
# target_include_directories(TestStack PUBLIC ../../LibraryCPPClass)
# target_link_libraries(TestStack LibraryCPPClass)
# add_test(TestStack TestStack)

# add_test(NAME ASBase COMMAND Lab2CPP -inter ${CMAKE_CURRENT_SOURCE_DIR}/testscript1.txt ${CMAKE_CURRENT_SOURCE_DIR}/emptyInput.txt)
# set_property(TEST ASBase PROPERTY PASS_REGULAR_EXPRESSION "Console output: \nC\nB\nA")