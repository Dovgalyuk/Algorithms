set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2
    main.cpp, list_test.cpp, stack_test.cpp
 )

#target_include_directories(Lab2 PUBLIC ../LibraryCPPTemplate)
#target_link_libraries(Lab2 LibraryCPPTemplate)

target_include_directories(Lab2 PUBLIC ../LibraryCPPtemplate)

add_subdirectory("tests")

