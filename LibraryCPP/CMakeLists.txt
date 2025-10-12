add_library(LibraryCPP STATIC array.cpp
        #list.cpp queue.cpp stack.cpp vector.cpp
        task1.cpp
        task1.h
        task2.h
        Tests/TestTask1.cpp
        Tests/TestTask2.cpp)

add_subdirectory(Tests)
