add_library(Library array.h array.cpp)
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ArrayTest tests/array_test.cpp)
target_link_libraries(ArrayTest PRIVATE Library)

add_test(NAME ArrayTest COMMAND ArrayTest)
