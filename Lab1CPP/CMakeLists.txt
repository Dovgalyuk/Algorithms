add_executable(Lab1CPP main.cpp lab1.cpp lab1.h)
target_include_directories(Lab1CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab1CPP LibraryCPP)
add_test(NAME TestLab1CPP COMMAND Lab1CPP ${CMAKE_CURRENT_SOURCE_DIR}/input.txt)


add_executable(MyTest ../LibraryCPP/Tests/MyArray.cpp lab1.cpp lab1.h)
target_include_directories(MyTest PUBLIC .)
target_include_directories(MyTest PUBLIC ..)
target_link_libraries(MyTest LibraryCPP)
add_test(NAME Mytest COMMAND MyTest ${CMAKE_CURRENT_SOURCE_DIR}/../LibraryCPP/Tests/TestInput.txt)