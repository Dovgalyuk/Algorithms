add_executable(Lab5CPP lab5.cpp)
target_include_directories(Lab5CPP PUBLIC ../LibraryCPPClass)
target_link_libraries(Lab5CPP LibraryCPPClass)
add_test(NAME Test1Lab5CPP COMMAND Lab5CPP)

