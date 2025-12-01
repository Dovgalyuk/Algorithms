set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2
    main.cpp
 )

target_include_directories(Lab2 PUBLIC ../LibraryCPPTemplate)
target_link_libraries(Lab2 LibraryCPPTemplate)


add_subdirectory("tests")

