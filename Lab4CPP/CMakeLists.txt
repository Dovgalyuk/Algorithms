cmake_minimum_required(VERSION 3.10)
project(Lab4CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab4CPP main.cpp)
target_link_libraries(Lab4CPP PRIVATE LibraryCPPTemplate)

set(TEST_INPUTS
    test1.txt
    test2.txt
    test3.txt
    test4.txt
    test5.txt
)

foreach(t ${TEST_INPUTS})
    get_filename_component(name ${t} NAME_WE)
    add_test(
        NAME Lab4CPP_${name}
        COMMAND bash -c "$<TARGET_FILE:Lab4CPP> < ${CMAKE_CURRENT_SOURCE_DIR}/${t}"
    )
endforeach()
