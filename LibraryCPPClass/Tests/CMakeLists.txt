add_executable(TestSet SetTest.cpp)
target_include_directories(TestSet PUBLIC ..)
target_link_libraries(TestSet LibraryCPPClass)
add_test(TestSet TestSet)