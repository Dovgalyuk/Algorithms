add_executable(Lab3CPP
        helper.h
        helper.cpp
        main.cpp
)

target_include_directories(Lab3CPP PUBLIC ../LibraryCPP)
target_link_libraries(Lab3CPP LibraryCPP)

add_subdirectory(Tests)