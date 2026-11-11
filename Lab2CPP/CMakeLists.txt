add_executable(Lab2CPP main.cpp task.cpp task.h)

target_include_directories(Lab2CPP PUBLIC ../LibraryCPP)

target_link_libraries(Lab2CPP LibraryCPP)

add_subdirectory(Tests)