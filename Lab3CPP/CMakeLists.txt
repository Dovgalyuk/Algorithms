add_executable(Lab3CPP main.cpp task.cpp task.h
        Tests/unit_tests.cpp)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)

target_link_libraries(Lab3CPP LibraryCPP)

add_subdirectory(Tests)